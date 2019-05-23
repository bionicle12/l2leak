#include "l2auth/network/CAuthOverlappedPool.h"

#include "l2auth/network/CAuthOverlapped.h"

CAuthOverlappedSlot CAuthOverlappedPool::g_slot[16];
long CAuthOverlappedPool::g_nAlloc = -1;
long CAuthOverlappedPool::g_nFree = 0;

CAuthOverlappedPool theAuthPool;

CAuthOverlappedPool::~CAuthOverlappedPool()
{
    CAuthOverlapped::FreeAll();
}
