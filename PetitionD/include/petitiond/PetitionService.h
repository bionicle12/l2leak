// PetitionService.h: interface for the PetitionService class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PETITIONSERVICE_H__BA429A6D_FF8E_4D6E_AAE7_029F7C218852__INCLUDED_)
#define AFX_PETITIONSERVICE_H__BA429A6D_FF8E_4D6E_AAE7_029F7C218852__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "petitiond/PetitionConn.h"
#include "petitiond/log.h"

class CWorldEmuDlg;

class PetitionService
{
protected:
    CWorldEmuDlg* m_pDlg;
    Log* m_pLog;
    CWinThread* m_ServicePetitionServerThread;
    UINT m_end_msg;
public:
    PetitionConn m_conn;
    PetitionService( CWorldEmuDlg* pDlg );
    virtual ~PetitionService();

    BOOL Connect( LPCSTR addr, WORD port, BYTE game_code, BYTE world_id, LPCSTR world_name );
    void StartService( UINT end_msg );
    void StopService();
    void Service();
};

#endif // !defined(AFX_PETITIONSERVICE_H__BA429A6D_FF8E_4D6E_AAE7_029F7C218852__INCLUDED_)
