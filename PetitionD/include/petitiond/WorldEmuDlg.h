// WorldEmuDlg.h : header file
//

#if !defined(AFX_WORLDEMUDLG_H__E2870140_30E6_4C63_ABA1_EC9DA927DC8C__INCLUDED_)
#define AFX_WORLDEMUDLG_H__E2870140_30E6_4C63_ABA1_EC9DA927DC8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWorldEmuDlg dialog

// Disable warning 'too long name' for standard c++ library
#include <map>
#include <vector>

#include "petitiond/ClientConn.h"
#include "petitiond/AuthConn.h"
#include "petitiond/UserDB.h"

#include "petitiond/PetitionService.h"
#include "petitiond/Log.h"

#define WORLD_SERVER_BUILD_NUMBER          10000

#define WM_USER_END_PETITION_SERVICE       (WM_USER+1000)

typedef std::map<int,int> OneTimePwdMap;
typedef std::map<int,ClientConn*> ClientMap;

class CWorldEmuDlg : public CDialog
{
// Construction
public:
    CWorldEmuDlg(CWnd* pParent = NULL);	// standard constructor

    // Thead Procs
    void ServiceAuthServer();
    void ServiceClient( ClientConn* pConn );
    void AcceptClient();

    // control status
    void DisableAllControlAboutPetition();
    void EnableControlAtConnectToPetition();
    void EnableControlAtDisconnectToPetition();

    // data management function // foreign method??
    void UpdatePetitionToCheckOut( UINT petition_id, LPCSTR gm_id, LPCSTR char_id );
    void UpdatePetitionState( UINT petition_id, LPCSTR state_label );
    void UpdateTempPetition( UINT temp_id, UINT petition_id );

    BOOL IsCharOnline( int char_int_id );


// Dialog Data
    //{{AFX_DATA(CWorldEmuDlg)
    enum { IDD = IDD_WORLDEMU_DIALOG };
    CButton	m_ctrlDisconnectToAuth;
    CButton	m_ctrlConnectToAuth;
    CEdit	m_ctrlAuthServerPort;
    CEdit	m_ctrlAuthServerAddr;
    CEdit	m_ctrlNumOfClients;
    CEdit	m_ctrlWorldName;
    CEdit	m_ctrlWorldId;
    CComboBox	m_ctrlGameCode;
    CButton	m_ctrlDisconnect;
    CListCtrl	m_ctrlPetitionList;
    CEdit	m_ctrlCommand;
    CEdit	m_ctrlLog;
    CButton	m_ctrlConnect;
    CEdit	m_ctrlPetitionServerPort;
    CEdit	m_ctrlPetitionServerAddr;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWorldEmuDlg)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;
    AuthConn* m_connAuth;
    UINT m_nPetitionTempId;
    LONG m_nClients;
    SOCKET m_listen_socket;
    UINT m_nOneTimePwd;

    OneTimePwdMap m_UidPwdMap;
    ClientMap m_ClientMap;
    UserDB m_UserDB;

    Log* m_pLog;

    CWinThread* m_AcceptClientThread;
    CWinThread* m_ServiceAuthServerThread;
    PetitionService* m_pPetitionService;

    void ProcessCommand( const char* szCommand, int char_int_id = 0 );
    void ShowHelpMessage();
    BOOL FindPetitionIndex( UINT petition_id, int* index );
    BOOL FindPetitionIndex( const char* petition_id, int* index );
    char* itoa( int i, char* buf );

    // Generated message map functions
    //{{AFX_MSG(CWorldEmuDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnConnect();
    afx_msg void OnDisconnect();
    afx_msg void OnConnectToAuth();
    afx_msg void OnDisconnectToAuth();
    afx_msg void OnClose();
    //}}AFX_MSG
    afx_msg LRESULT OnEndPetitionService( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORLDEMUDLG_H__E2870140_30E6_4C63_ABA1_EC9DA927DC8C__INCLUDED_)
