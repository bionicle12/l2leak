#pragma once

#include "l2core/Orts.h"
#include "l2core/threads/CRWLock.h"
#include "l2core/threads/CSPointer.h"

#include <map>
#include <l2core/utils/cstdint_support.h>

template <typename T>
class CSPointer;

// In original code it also has second argument for map/lock arity
// I hard-coded it for 0x7FFF, since in L2CacheD it's the only used size
template <typename T>
class CShardingObjectMap
{
public:
    // if returns true, ForEach exits from loop and returns curr object
    // In original L2 code ForEach is probably a macro
    typedef bool (*Predicate)(T* object);

public:
    CShardingObjectMap();   // L2CacheD 0x004634E0, T=CUser
    ~CShardingObjectMap();  // L2CacheD 0x00463590, T=CUser

    CSPointer<T> FindObject(uint32_t objectId) const;                                // L2CacheD 0x00461910, T=CUser
    void Insert(uint32_t id, T* object, const char* caller = NULL, int line = -1);   // L2CacheD 0x00462ED0, T=CUser
    void DeleteObject(uint32_t objectId, const char* caller = NULL, int line = -1);  // L2CacheD 0x00462FD0, T=CUser

    template <typename Func>
    void DeleteAll(Func& predicate);  // L2CacheD always inlined, probably a macro

    template <typename Func>
    CSPointer<T> ForEach(Func& predicate) const;

private:
    typedef std::map<int, T*> ObjMap;

    static const int MAP_NUMBER = 0x7FFF;
    ObjMap m_objectMaps[MAP_NUMBER];
    mutable CRWLock m_locks[MAP_NUMBER];
    uint32_t m_size;
};

#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x004634E0, T=CUser
template <typename T>
CShardingObjectMap<T>::CShardingObjectMap()
    : m_size(MAP_NUMBER)
{
    guard(L"CShardingObjectMap()");
    unguard();
}

// L2CacheD 0x00463590, T=CUser
template <typename T>
CShardingObjectMap<T>::~CShardingObjectMap()
{
    guard(L"CShardingObjectMap<T>::~CShardingObjectMap()");

    for (int i = 0; i < MAP_NUMBER; ++i)
    {
        CRWLock& lock = m_locks[i];
        lock.WriteLock();

        ObjMap& objMap = m_objectMaps[i];
        for (ObjMap::iterator it = objMap.begin(); it != objMap.end(); ++it)
        {
            ObjMap::value_type& pair = *it;
            T* object = pair.second;
            object->Release(__FILE__, __LINE__, ORT_OBJECT_MAP, false);
        }

        lock.WriteUnlock();
    }

    unguard();
}

// L2CacheD 0x00461910, T=CUser
template <typename T>
CSPointer<T> CShardingObjectMap<T>::FindObject(uint32_t objectId) const
{
    guard(L"CSPointer<T> FindObject(uint32_t id)");

    // const uint32_t index = abs(objectId) % MAP_NUMBER; FIXED: already unsigned
    const uint32_t index = objectId % MAP_NUMBER;
    CRWLock& lock = m_locks[index];
    lock.ReadLock();

    CSPointer<T> result;
    const ObjMap& objMap = m_objectMaps[index];
    ObjMap::const_iterator it = objMap.find(objectId);
    if (it != objMap.end())
    {
        result.SetObject(it->second, ORT_OBJECT_MAP);
    }

    lock.ReadUnlock();

    unguard();

    return result;
}

// L2CacheD 0x00462ED0, T=CUser
template <typename T>
void CShardingObjectMap<T>::Insert(uint32_t objectId, T* object, const char* caller, int line)
{
    guard(L"void Insert(uint32_t objectId, T* p, char *caller = NULL, int line = -1)");

    // const uint32_t index = abs(objectId) % MAP_NUMBER; // FIXED: already unsigned
    const uint32_t index = objectId % MAP_NUMBER;
    CRWLock& lock = m_locks[index];
    lock.WriteLock();

    ObjMap& objMap = m_objectMaps[index];

    ObjMap::iterator it = objMap.find(objectId);
    if (it == objMap.end())
    {
        object->AddRef((caller == NULL) ? __FILE__ : caller, (line == -1) ? __LINE__ : line, ORT_OBJECT_MAP);
        objMap[objectId] = object;
    }

    lock.WriteUnlock();

    unguard();
}

// L2CacheD 0x00462FD0, T=CUser
template <typename T>
void CShardingObjectMap<T>::DeleteObject(uint32_t objectId, const char* caller, int line)
{
    guard(L"void DeleteObject(uint32_t id, char *caller=NULL, int line=-1)");

    // const uint32_t index = abs(objectId) % MAP_NUMBER; // FIXED: already unsigned
    const uint32_t index = objectId % MAP_NUMBER;
    CRWLock& lock = m_locks[index];
    lock.WriteLock();

    ObjMap& objMap = m_objectMaps[index];
    ObjMap::iterator it = objMap.find(objectId);
    if (it != objMap.end())
    {
        ObjMap::value_type& pair = *it;
        T* object = pair.second;
        object->Release((caller == NULL) ? __FILE__ : caller, (line == -1) ? __LINE__ : line, ORT_OBJECT_MAP, false);

        // objMap.erase(objectId);  FIXED
        objMap.erase(it);
    }

    lock.WriteUnlock();

    unguard();
}

// L2CacheD always inlined, probably a macro
template <typename T>
template <typename Func>
void CShardingObjectMap<T>::DeleteAll(Func& predicate)
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
CSPointer<T> CShardingObjectMap<T>::ForEach(Func& predicate) const
{
    guard(L"FOR ALL OBJECT IN OBJECT MAP");

    for (int i = 0; i < MAP_NUMBER; ++i)
    {
        CRWLock& lock = m_locks[i];
        lock.ReadLock();

        const ObjMap& objMap = m_objectMaps[i];
        for (ObjMap::const_iterator it = objMap.begin(); it != objMap.end(); ++it)
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

        lock.ReadUnlock();
    }

    unguard();
    return CSPointer<T>();
}
