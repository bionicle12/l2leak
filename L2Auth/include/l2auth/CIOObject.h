#pragma once

#include <windows.h>

class CIOObject
{
public:
    virtual ~CIOObject();                                                                      // L2AuthD 0x00418081
    virtual void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped);  // L2AuthD 0x0041817D
    virtual void OnTimerCallback();                                                            // L2AuthD 0x0041818A
    virtual bool RegisterTimer(unsigned int delay, int id);                                    // L2AuthD 0x0041811C
    virtual void OnEventCallback();                                                            // L2AuthD 0x0041819D
    virtual bool RegisterEvent(HANDLE eventObject);                                            // L2AuthD 0x00418154

#if defined _WIN64
    LONGLONG AddRef();  // L2AuthD 0x00418095
#else
    LONG AddRef();  // L2AuthD 0x00418095
#endif

    void ReleaseRef();                                 // L2AuthD 0x004180B3
    BOOL PostObject(DWORD id, HANDLE completionPort);  // L2AuthD 0x004180FB

protected:
    CIOObject();  // L2AuthD 0x00418060

protected:
#if defined _WIN64
    LONGLONG m_nRefCount;
#else
    LONG m_nRefCount;
#endif
};
