#pragma once

#include "l2core/Orts.h"
#include "l2core/threads/CRWLock.h"
#include "l2core/threads/CSPointer.h"

#include <map>

#include <l2core/utils/cstdint_support.h>

template <typename T>
class CSPointer;

// In original code it also has second argument for lock arity
// I hard-coded it for 1023, since in L2CacheD it's the only used size
template <typename T>
class CObjectStorage
{
public:
    CObjectStorage();   // L2CacheD 0x
    ~CObjectStorage();  // L2CacheD 0x

    CSPointer<T> GetObjct() const;  // L2CacheD, T=CWareHouse 0x0040C010
    void SetObject(T* object);      // L2CacheD, T=CWareHouse 0x0040BEC0

private:
    typedef std::map<int, T*> ObjMap;

    static const int LOCK_NUMBER = 1023;
    static CRWLock s_locks[LOCK_NUMBER];  // L2CacheD, T=CWareHouse 0x021E6FA8

    T* m_object;
};

#include "l2core/logger/CLog.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD, T=CWareHouse 0x0049D3B0
template <typename T>
CRWLock CObjectStorage<T>::s_locks[LOCK_NUMBER];  // L2CacheD, T=CWareHouse 0x021E6FA8

// L2CacheD
template <typename T>
CObjectStorage<T>::CObjectStorage()
    : m_object(NULL)
{
    guard(L"CObjectStorage<T>::CObjectStorage()");
    unguard();
}

// L2CacheD
template <typename T>
CObjectStorage<T>::~CObjectStorage()
{
    guard(L"CObjectStorage<T>::~CObjectStorage()");

    unguard();
}

// L2CacheD, T=CWareHouse 0x0040C010
template <typename T>
CSPointer<T> CObjectStorage<T>::GetObjct() const
{
    guard(L"CSPointer<T> CObjectStorage<T>::GetObjct()");

    uint64_t base = reinterpret_cast<uint64_t>(m_object) >> 3;
    int index = base % LOCK_NUMBER;
    if (index < 0)
    {
        index = 0;
        g_winlog.Add(LOG_ERROR, L"object storage key[%d] (address[%d]) < 0", index, m_object);
    }
    else if (LOCK_NUMBER <= index)
    {
        index = 0;
        g_winlog.Add(LOG_ERROR, L"object storage key[%d] (address[%d]) > MAX(%d)", index, m_object, LOCK_NUMBER);
    }

    CRWLock& lock = s_locks[index];
    lock.ReadLock();
    CSPointer<T> result(m_object, ORT_OBJECT_STORAGE);
    lock.ReadUnlock();

    unguard();

    return result;
}

// L2CacheD, T=CWareHouse 0x0040BEC0
template <typename T>
void CObjectStorage<T>::SetObject(T* obj)
{
    guard(L"void CObjectStorage<T>::SetObject(T* obj)");

    uint64_t base = reinterpret_cast<uint64_t>(m_object) >> 3;
    int index = base % LOCK_NUMBER;
    if (index < 0)
    {
        index = 0;
        g_winlog.Add(LOG_ERROR, L"object storage key[%d] (address[%d]) < 0", index, m_object);
    }
    else if (LOCK_NUMBER <= index)
    {
        index = 0;
        g_winlog.Add(LOG_ERROR, L"object storage key[%d] (address[%d]) > MAX(%d)", index, m_object, LOCK_NUMBER);
    }

    CRWLock& lock = s_locks[index];
    lock.WriteLock();

    if (m_object != NULL)
    {
        m_object->Release(__FILE__, __LINE__, ORT_OBJECT_STORAGE, false);
    }

    m_object = obj;
    if (m_object != NULL)
    {
        m_object->AddRef(__FILE__, __LINE__, ORT_OBJECT_STORAGE);
    }

    lock.WriteUnlock();

    unguard();
}
