#pragma once

#include "l2auth/CIOObject.h"

class CIOTopTimer : public CIOObject
{
public:
    CIOTopTimer();   // L2AuthD 0x0042C4D0
    ~CIOTopTimer();  // L2AuthD 0x0042C550

    void OnTimerCallback() override;                                                           // L2AuthD 0x0042ABFF
    void OnEventCallback() override;                                                           // L2AuthD 0x0042C500
    virtual void OnIOCallback(BOOL bSuccess, DWORD dwTransferred, LPOVERLAPPED lpOverlapped);  // L2AuthD 0x0042C510 miss-overriden in origin code
};
