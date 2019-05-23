#pragma once

#include "l2core/Orts.h"
#include "l2core/threads/CRWLock.h"
#include "l2core/threads/CSPointer.h"

#include <map>
#include <l2core/utils/cstdint_support.h>

template <typename T>
class CSPointer;

// In original code it also has second argument for map/lock arity
// But since it's a template, I've decided to prepare separate
// implementation for sake of readability. See CShardingObjectMap

template <typename T>
class CObjectMap
{
public:
    // if returns true, ForEach exits from loop and returns curr object
    // In original L2 code ForEach is probably a macro
    typedef bool (*Predicate)(T* object);

public:
    CObjectMap();   // L2CacheD T=CItem, 0x0040CC40
    ~CObjectMap();  // L2CacheD T=CItem, 0x0040CCE0

    int GetSize() const;                                                             // L2CacheD T=CUser, 0x00402200
    CSPointer<T> FindObject(uint32_t objectId) const;                                // L2CacheD T=CItem, 0x00425640
    void Insert(uint32_t id, T* object, const char* caller = NULL, int line = -1);   // L2CacheD T=CItem, 0x00425A30
    void DeleteObject(uint32_t objectId, const char* caller = NULL, int line = -1);  // L2CacheD T=CItem, 0x00425B10; T=CUser, 0x004035B0

    template <typename Func>
    void DeleteAll(Func& predicate);  // L2CacheD always inlined, probably a macro

    template <typename Func>
    CSPointer<T> ForEach(Func& predicate) const;  // L2CacheD always inlined, probably a macro

private:
    typedef std::map<int, T*> ObjMap;

    ObjMap m_objects;
    mutable CRWLock m_lock;
    uint32_t m_size;
};

#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD T=CItem, 0x0040CC40
template <typename T>
CObjectMap<T>::CObjectMap()
    : m_objects()
    , m_lock()
    , m_size(1)
{
    guard(L"CObjectMap()");
    unguard();
}

// L2CacheD T=CItem, 0x0040CCE0
template <typename T>
CObjectMap<T>::~CObjectMap()
{
    guard(L"~CObjectMap()");

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

// L2CacheD T=CUser, 0x00402200
template <typename T>
int CObjectMap<T>::GetSize() const
{
    guard(L"int GetSize()");

    m_lock.ReadLock();

    int result = static_cast<int>(m_objects.size());

    m_lock.ReadUnlock();

    unguard();

    return result;
}

// L2CacheD T=CItem, 0x00425640
template <typename T>
CSPointer<T> CObjectMap<T>::FindObject(uint32_t objectId) const
{
    guard(L"CSPointer<T> FindObject(uint32_t id)");

    m_lock.ReadLock();

    CSPointer<T> result;
    ObjMap::const_iterator it = m_objects.find(objectId);
    if (it != m_objects.end())
    {
        result.SetObject(it->second, ORT_OBJECT_MAP);
    }
    m_lock.ReadUnlock();

    unguard();

    return result;
}

// L2CacheD T=CItem, 0x00425A30
template <typename T>
void CObjectMap<T>::Insert(uint32_t objectId, T* object, const char* caller, int line)
{
    guard(L"void Insert(uint32_t objectId, T* p, char *caller = NULL, int line = -1)");

    m_lock.WriteLock();

    ObjMap::iterator it = m_objects.find(objectId);
    if (it == m_objects.end())
    {
        object->AddRef((caller == NULL) ? __FILE__ : caller, (line == -1) ? __LINE__ : line, ORT_OBJECT_MAP);
        m_objects[objectId] = object;
    }

    m_lock.WriteUnlock();

    unguard();
}

// L2CacheD T=CItem, 0x00425B10
template <typename T>
void CObjectMap<T>::DeleteObject(uint32_t objectId, const char* caller, int line)
{
    guard(L"void DeleteObject(uint32_t id, char *caller=NULL, int line=-1)");

    m_lock.WriteLock();

    ObjMap::iterator it = m_objects.find(objectId);
    if (it != m_objects.end())
    {
        ObjMap::value_type& pair = *it;
        T* object = pair.second;
        object->Release((caller == NULL) ? __FILE__ : caller, (line == -1) ? __LINE__ : line, ORT_OBJECT_MAP, false);

        // m_objects.erase(objectId);  FIXED
        m_objects.erase(it);
    }

    m_lock.WriteUnlock();

    unguard();
}

// L2CacheD always inlined, probably a macro
template <typename T>
template <typename Func>
CSPointer<T> CObjectMap<T>::ForEach(Func& predicate) const
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
            m_lock.ReadUnlock();
            unguard();
            return CSPointer<T>(object, ORT_FUNCTION_CHAIN);
        }
    }

    m_lock.ReadUnlock();

    unguard();
    return CSPointer<T>();
}

// L2CacheD always inlined, probably a macro
template <typename T>
template <typename Func>
void CObjectMap<T>::DeleteAll(Func& predicate)
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
