#pragma once

#include "l2core/Orts.h"
#include "l2core/logger/CLog.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

template <typename T>
class CSPointer
{
public:
    CSPointer()
        : m_object(NULL)
        , m_workType()
    {
        guard(L"CSPointer()");
        unguard();
    }

    // L2CacheD 0x0040B7D0
    CSPointer(const CSPointer& other)
        : m_object(other.m_object)
        , m_workType(other.m_workType)
    {
        guard(L"CSPointer(const CSPointer& other)");

        if (m_object != NULL)
        {
            m_object->AddRef(__FILE__, __LINE__, ORT_OBJECT_MAP);
        }

        unguard();
    }

    CSPointer(T* object, ORTs orts)
        : m_object(NULL)
        , m_workType()
    {
        guard(L"CSPointer(T* object, ORTs orts)");

        if (object != NULL)
        {
            object->AddRef(__FILE__, __LINE__, orts);
        }

        if (m_object != NULL)
        {
            m_object->Release(__FILE__, __LINE__, m_workType, false);
        }

        m_object = object;
        m_workType = orts;

        unguard();
    }

    CSPointer& operator=(const CSPointer& other)
    {
        guard(L"CSPointer(const CSPointer& other)");
        if (this == &other)
        {
            unguard();
            return *this;
        }

        SetObject(other.m_object, other.m_workType);
        unguard();
        return *this;
    }

    // FIXED: this is dangerous, but is present in original L2 code.
    // operator T*()
    T* get()
    {
        guard(L"operator T*()");
        T* object = m_object;
        unguard();
        return object;
    }

    // L2CacheD T=CUser 0x004151F0, T=CAlliance/CPledge 0x00405300
    T* operator->() const
    {
        guard(L"T* operator->() const");

        if (m_object == NULL)
        {
            g_winlog.Add(LOG_ERROR, "[%s][%d] referencing NULL object.", __FILE__, __LINE__);
            CallStack::ReportCallStack();
        }

        T* object = m_object;
        unguard();
        return object;
    }

    // FIXME: port me after c++11
    bool operator==(void* null) const
    {
        return m_object == null;
    }

    bool operator!=(void* null) const
    {
        return m_object != null;
    }

    void SetObject(T* object, ORTs orts)
    {
        guard(L"void SetObject(const T* p, ORTs orts)");

        if (object != NULL)
        {
            object->AddRef(__FILE__, __LINE__, orts);
        }

        if (m_object != NULL)
        {
            m_object->Release(__FILE__, __LINE__, m_workType, false);
        }

        m_object = object;
        m_workType = orts;

        unguard();
    }

    ~CSPointer()
    {
        if (m_object != NULL)
        {
            m_object->Release(__FILE__, __LINE__, ORT_OBJECT_MAP, false);
        }
    }

private:
    T* m_object;
    ORTs m_workType;
};
