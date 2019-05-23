#pragma once

#include "l2core/threads/ThreadIndices.h"

#include <windows.h>

#include <vector>
#include <l2core/utils/cstdint_support.h>

class CIOObject;

namespace Threads
{

// Main thread loop
void MessageLoop_common(HACCEL hAccTable);   // L2LogD 0x00403AE0, L2CacheD 0x00409D40, L2NPC 0x00429ED0
void MessageLoop_mailing(HACCEL hAccTable);  // L2LogD 0x00403B50, L2CacheD 0x00409DE0, L2NPC 0x00429F40

// CliLog thread
uint32_t __stdcall CliLogThread(void*);  // L2LogD 0x0040CEC0, L2CacheD 0x00484130, L2NPC 0x00485580
void CliLogThread_common();              // L2LogD 0x0040C4B0, L2CacheD 0x004836A0
void CliLogThread_mailing();             // L2LogD 0x0040C420, L2CacheD 0x00483610, L2NPC 0x004854E0

// Performance monitor
uint32_t __stdcall PerfMonitorThread(void*);  // L2LogD 0x00404270, L2CacheD 0x0040A6B0, L2NPC 0x0042A750
void PerfMonitorThread_mailing();             // L2LogD 0x004041D0, L2CacheD 0x0040A610
void PerfMonitorThread_common();              // L2LogD 0x00404260, L2CacheD 0x0040A6A0
extern HANDLE PerfMonitor_s_thread;           // L2LogD 0x00455C1C, L2CacheD 0x004F28B0

// IO thread
void CreateIOThread(uint32_t maxIOThread);       // L2LogD 0x0040AF40, L2CacheD 0x00481DF0, L2NPC 0x004779B0
void WaitThread();                               // L2LogD 0x0040ABB0, L2CacheD 0x004818E0, L2NPC 0x00478640
uint32_t __stdcall IOThread(void* threadIndex);  // L2LogD 0x0040AF00, L2CacheD 0x00481D30, L2NPC 0x00478BA0
void IOThread_common(ThreadIndices index);       // L2LogD 0x0040AD20, L2CacheD 0x00481AE0, L2NPC 0x00478840
void IOThread_mailing(ThreadIndices index);      // L2LogD 0x0040AE60, L2CacheD 0x00481C90, L2NPC 0x00478B00
void CloseIOThread();                            // L2NPC 0x00477ab0

extern HANDLE s_closedEvent;               // L2LogD 0x01BD3BB8, L2CacheD 0x02684630, L2NPC 0x013FB14C
extern bool g_bTerminating;                // L2LogD 0x01BD3BBC, L2CacheD 0x02684628, L2NPC 0x013FB150
extern std::vector<HANDLE> g_vHandle;      // L2LogD 0x01BD3D3C, L2CacheD 0x026846D4
extern std::vector<CIOObject*> g_vObject;  // L2LogD 0x01BD3D4C, L2CacheD 0x02684928

// SQL queue
uint32_t __stdcall SqlQueueThread(void*);  // L2LogD 0x00404340
void SqlQueueThread_mailing();             // L2LogD 0x004042A0
void SqlQueueThread_common();              // L2LogD 0x00404330

// BCP
uint32_t __stdcall BCPThread(void* bcpSlot);  // L2LogD 0x00404420
void BCPThread_mailing(int bcpSlot);          // L2LogD 0x00404370
void BCPThread_common(int bcpSlot);           // L2LogD 0x00404410
extern HANDLE BCPThread_s_threads[10];        // L2LogD 0x00455C70

}  // namespace Threads
