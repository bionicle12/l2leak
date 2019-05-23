#include "l2auth/network/CIOBuffer.h"

#include "l2auth/network/CIOBufferPool.h"

#include <windows.h>

// L2AuthD 0x00417D00
CIOBuffer::CIOBuffer()
{
}

// L2AuthD 0x00417D17
CIOBuffer::~CIOBuffer()
{
}

// L2AuthD 0x004116D0
void CIOBuffer::AddRef()
{
    ::InterlockedIncrement(&m_nRefCount);
}

// L2AuthD 0x0041E170
void CIOBuffer::Release()
{
    if (::InterlockedDecrement(&m_nRefCount) == 0)
    {
        Free();
    }
}

// L2AuthD 0x00417DD3
CIOBuffer* CIOBuffer::Alloc()
{
    CIOBufferSlot* slot = &CIOBufferPool::g_slot[::InterlockedIncrement(&CIOBufferPool::g_nAlloc) & 0xF];
    slot->m_lock.Enter();

    CIOBuffer* newBuffer = slot->m_pBuffer;
    if (slot->m_pBuffer)
    {
        slot->m_pBuffer = newBuffer->m_pNext;
        slot->m_lock.Leave();
    }
    else
    {
        slot->m_lock.Leave();
        newBuffer = new CIOBuffer();
    }

    newBuffer->m_dwSize = 0;
    newBuffer->m_nRefCount = 1;
    newBuffer->m_pNext = NULL;

    return newBuffer;
}

// L2AuthD 0x00417EC2
void CIOBuffer::Free()
{
    CIOBufferSlot* slot = &CIOBufferPool::g_slot[InterlockedDecrement(&CIOBufferPool::g_nFree) & 0xF];

    slot->m_lock.Enter();
    m_pNext = slot->m_pBuffer;
    slot->m_pBuffer = this;
    slot->m_lock.Leave();
}

// L2AuthD 0x00417F14
void CIOBuffer::FreeAll()
{
    for (int i = 0; i < 16; ++i)
    {
        CIOBufferSlot* slot = &CIOBufferPool::g_slot[i];
        slot->m_lock.Enter();
        while (true)
        {
            CIOBuffer* pBuffer = slot->m_pBuffer;
            if (slot->m_pBuffer == NULL)
            {
                break;
            }

            slot->m_pBuffer = pBuffer->m_pNext;
            delete pBuffer;
        }
        slot->m_lock.Leave();
    }
}
