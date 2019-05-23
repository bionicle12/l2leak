#pragma once

#include "l2core/Orts.h"
#include "l2core/threads/CRWLock.h"
#include "l2core/threads/CSPointer.h"

#include <map>
#include <string>

template <typename T>
class CSPointer;

template <typename T>
class CStringObjectMap
{
public:
    // if returns true, ForEach exits from loop and returns curr object
    // In original L2 code ForEach is probably a macro
    typedef bool (*Predicate)(T* object);

public:
    CStringObjectMap();
    ~CStringObjectMap();

    int GetSize() const;
    CSPointer<T> FindObject(const std::wstring& name) const;
    void Insert(const std::wstring& name, T* object, const char* caller = NULL, int line = -1);
    void DeleteObject(const std::wstring& name, const char* caller = NULL, int line = -1);

    template <typename Func>
    void DeleteAll(Func& predicate);  // L2CacheD always inlined, probably a macro

    template <typename Func>
    CSPointer<T> ForEach(Func& predicate) const;

private:
    typedef std::map<std::wstring, T*> ObjMap;

    ObjMap m_objects;
    mutable CRWLock m_lock;
};

#include "l2core/utils/dbg/StackGuard.h"

template <typename T>
CStringObjectMap<T>::CStringObjectMap()
    : m_objects()
    , m_lock()
{
    guard(L"CStringObjectMap()");
    unguard();
}

template <typename T>
CStringObjectMap<T>::~CStringObjectMap()
{
    guard(L"~CStringObjectMap()");

    m_lock.WriteLock();

    for (ObjMap::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
    {
        ObjMap::value_type& pair = *it;
        T* object = pair.second;
        object->Release(__FILE__, __LINE__, ORT_OBJECT_MAP, false);
    }

    m_objects.clear();
    m_lock.WriteUnlock();

    unguard();
}

template <typename T>
int CStringObjectMap<T>::GetSize() const
{
    guard(L"int GetSize()");

    m_lock.ReadLock();

    int result = static_cast<int>(m_objects.size());

    m_lock.ReadUnlock();

    unguard();

    return result;
}

template <typename T>
CSPointer<T> CStringObjectMap<T>::FindObject(const std::wstring& name) const
{
    guard(L"CSPointer<T> FindObject(const std::wstring& name)");

    m_lock.ReadLock();

    CSPointer<T> result;
    ObjMap::const_iterator it = m_objects.find(name);
    if (it != m_objects.end())
    {
        result.SetObject(it->second, ORT_OBJECT_MAP);
    }
    m_lock.ReadUnlock();

    unguard();

    return result;
}

template <typename T>
void CStringObjectMap<T>::Insert(const std::wstring& name, T* object, const char* caller, int line)
{
    guard(L"void Insert(const std::wstring& name, T* p, char *caller = NULL, int line = -1)");

    m_lock.WriteLock();

    ObjMap::iterator it = m_objects.find(name);
    if (it == m_objects.end())
    {
        object->AddRef((caller == NULL) ? __FILE__ : caller, (line == -1) ? __LINE__ : line, ORT_OBJECT_MAP);
        m_objects[name] = object;
    }

    m_lock.WriteUnlock();

    unguard();
}

template <typename T>
void CStringObjectMap<T>::DeleteObject(const std::wstring& name, const char* caller, signed int line)
{
    guard(L"void DeleteObject(const std::wstring& name, char *caller=NULL, int line=-1)");

    m_lock.WriteLock();

    ObjMap::iterator it = m_objects.find(name);
    if (it != m_objects.end())
    {
        ObjMap::value_type& pair = *it;
        T* object = pair.second;
        object->Release((caller == NULL) ? __FILE__ : caller, (line == -1) ? __LINE__ : line, ORT_OBJECT_MAP, false);

        // m_objects.erase(name);  FIXED
        m_objects.erase(it);
    }

    m_lock.WriteUnlock();

    unguard();
}

// L2CacheD always inlined, probably a macro
template <typename T>
template <typename Func>
void CStringObjectMap<T>::DeleteAll(Func& predicate)
{
    guard(L"FOR ALL OBJECT IN OBJECT MAP BEFORE DELETE ALL");

    m_lock.WriteLock();

    for (ObjMap::iterator it = m_objects.begin(); it != m_objects.end(); ++it)
    {
        T* object = it->second;

        guard(L"in_code");  // FIXED: added

        predicate(object);
        object->Release(__FILE__, __LINE__, ORT_OBJECT_MAP, false);

        unguard();
    }

    m_lock.WriteUnlock();

    unguard();
}

// L2CacheD always inlined, probably a macro
template <typename T>
template <typename Func>
CSPointer<T> CStringObjectMap<T>::ForEach(Func& predicate) const
{
    guard(L"FOR ALL OBJECT IN OBJECT MAP");

    m_lock.ReadLock();

    for (ObjMap::const_iterator it = m_objects.begin(); it != m_objects.end(); ++it)
    {
        T* object = it->second;

        guard(L"in_code");
        bool stop = predicate(object);
        unguard();

        if (stop)
        {
            lock.ReadUnlock();
            unguard();
            return CSPointer<T>(object, ORT_FUNCTION_CHAIN);
        }
    }

    m_lock.ReadUnlock();

    unguard();
    return CSPointer<T>();
}
