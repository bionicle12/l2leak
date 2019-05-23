#pragma once

#include "l2core/MemoryObject.h"
#include "l2core/logger/CLog.h"
#include "l2core/threads/ThreadLocalStorage.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

class CIOSocket;

class CExecutionSerializerFast
{
public:
    CExecutionSerializerFast();  // L2NPC inlined in CIOSocket c.tor

    template <typename TParam>
    void AddExecutable(TParam parameter, CIOSocket* object, void (CIOSocket::*executable)(TParam));  // L2NPC 0x004177C0

private:
    template <typename T, typename P>
    static void* void_cast(void (T::*f)(P));

    template <typename T, typename P>
    static void (T::*pf_cast(void* ptr))(P);

    int m_consumeIndex;
    long m_writeIndex;
    long m_size;
    int m_threadIndex;
    int field_24;
    intptr_t* m_parameters[5000];
    void* m_executors[5000];
};

// L2NPC 0x004177C0
template <typename TParam>
void CExecutionSerializerFast::AddExecutable(TParam parameter, CIOSocket* object, void (CIOSocket::*executable)(TParam))
{
    if (m_threadIndex == tls::GetCurrentThreadIndex())
    {
        (object->*(executable))(parameter);
        return;
    }

    long writeIndex = ::InterlockedIncrement(&m_writeIndex) % 5000u;
    m_parameters[writeIndex] = reinterpret_cast<intptr_t*>(parameter);
    void* address = void_cast(executable);
    m_executors[writeIndex] = address;
    long queueSize = ::InterlockedIncrement(&m_size);
    if (queueSize >= 5000)
    {
        g_winlog.Add(LOG_ERROR, L"[%s][%d] Asynchronous Execution Overflow.", __WFILE__, __LINE__);
        CallStack::ReportCallStack();
        return;
    }

    // Only first thread "starts" execution queue, all other just add
    if (queueSize != 1)
    {
        return;
    }

    while (queueSize != 0)
    {
        m_threadIndex = tls::GetCurrentThreadIndex();
        long consumeIndex = ++m_consumeIndex % 5000u;
        while (m_executors[consumeIndex] == NULL)  // FIXME! looks like busy-loop
        {
            ::Sleep(0);
        }

        TParam param = reinterpret_cast<TParam>(m_parameters[consumeIndex]);
        void* address = m_executors[consumeIndex];
        void (CIOSocket::*exec)(TParam) = pf_cast<CIOSocket, TParam>(address);
        (object->*(exec))(param);
        m_executors[consumeIndex] = NULL;
        m_threadIndex = -1;

        queueSize = ::InterlockedDecrement(&m_size);
    }
}

template <typename T, typename P>
void* CExecutionSerializerFast::void_cast(void (T::*f)(P))
{
    union
    {
        void (T::*pf)(P);
        void* p;
    };
    pf = f;
    return p;
}

template <typename T, typename P>
static void (T::*CExecutionSerializerFast::pf_cast(void* ptr))(P)
{
    union
    {
        void (T::*pf)(P);
        void* p;
    };
    p = ptr;
    return pf;
}
