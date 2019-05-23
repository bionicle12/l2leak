// WorldEmuDlg.cpp : implementation file
//

#include "petitiond/stdafx.h"
#include "petitiond/WorldEmu.h"
#include "petitiond/WorldEmuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
        // No message handlers
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Thread Procs

CWorldEmuDlg* g_MainDlg;

UINT ServiceAuthServerProc( void* pParam ) {
    g_MainDlg->ServiceAuthServer();
    return 0;
}

UINT AcceptClientProc( void* pParam ) {
    ((CWorldEmuDlg*)pParam)->AcceptClient();
    return 0;
}

UINT ServiceClientProc( void* pParam ) {
    g_MainDlg->ServiceClient( (ClientConn*)pParam );
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CWorldEmuDlg dialog

CWorldEmuDlg::CWorldEmuDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CWorldEmuDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CWorldEmuDlg)
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWorldEmuDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CWorldEmuDlg)
    DDX_Control(pDX, IDC_DISCONNECT_TO_AUTH, m_ctrlDisconnectToAuth);
    DDX_Control(pDX, IDC_CONNECT_TO_AUTH, m_ctrlConnectToAuth);
    DDX_Control(pDX, IDC_AUTH_SERVER_PORT, m_ctrlAuthServerPort);
    DDX_Control(pDX, IDC_AUTH_SERVER_ADDR, m_ctrlAuthServerAddr);
    DDX_Control(pDX, IDC_CLIENTS_NUM, m_ctrlNumOfClients);
    DDX_Control(pDX, IDC_WORLD_NAME, m_ctrlWorldName);
    DDX_Control(pDX, IDC_WORLD_ID, m_ctrlWorldId);
    DDX_Control(pDX, IDC_GAME_CODE, m_ctrlGameCode);
    DDX_Control(pDX, IDC_DISCONNECT, m_ctrlDisconnect);
    DDX_Control(pDX, IDC_PETITION_LIST, m_ctrlPetitionList);
    DDX_Control(pDX, IDC_COMMAND, m_ctrlCommand);
    DDX_Control(pDX, IDC_LOG, m_ctrlLog);
    DDX_Control(pDX, IDC_CONNECT, m_ctrlConnect);
    DDX_Control(pDX, IDC_PETITION_SERVER_PORT, m_ctrlPetitionServerPort);
    DDX_Control(pDX, IDC_PETITION_SERVER_ADDR, m_ctrlPetitionServerAddr);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWorldEmuDlg, CDialog)
    //{{AFX_MSG_MAP(CWorldEmuDlg)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_CONNECT, OnConnect)
    ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
    ON_BN_CLICKED(IDC_CONNECT_TO_AUTH, OnConnectToAuth)
    ON_BN_CLICKED(IDC_DISCONNECT_TO_AUTH, OnDisconnectToAuth)
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
    ON_MESSAGE(WM_USER_END_PETITION_SERVICE,OnEndPetitionService)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorldEmuDlg message handlers

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWorldEmuDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialog::OnPaint();
    }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWorldEmuDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}

void CWorldEmuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

BOOL CWorldEmuDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here

    // initialize member variables
    m_nPetitionTempId = 1;
    m_nOneTimePwd     = 1;
    m_connAuth        = NULL;
    m_nClients        = 0;
    m_pPetitionService = NULL;

    // make list control header
    CRect rect;
    m_ctrlPetitionList.GetClientRect( &rect );
    m_ctrlPetitionList.InsertColumn( 0, "status",    LVCFMT_LEFT, 100 );
    m_ctrlPetitionList.InsertColumn( 1, "id",        LVCFMT_LEFT, 50 );
    m_ctrlPetitionList.InsertColumn( 2, "category",  LVCFMT_LEFT, 50 );
    m_ctrlPetitionList.InsertColumn( 3, "char_id",   LVCFMT_LEFT, 100 );
    m_ctrlPetitionList.InsertColumn( 4, "gm_id",     LVCFMT_LEFT, 100 );
    m_ctrlPetitionList.InsertColumn( 5, "contents",  LVCFMT_LEFT, rect.Width()-400 );
    m_ctrlPetitionList.SetExtendedStyle( m_ctrlPetitionList.GetExtendedStyle() | LVS_EX_FULLROWSELECT );

    // load last values from registry
    CWinApp* pApp = AfxGetApp();
    m_ctrlGameCode.SetCurSel( pApp->GetProfileInt( "WorldEmu", "last_game_code", 0 ) );
    m_ctrlPetitionServerAddr.SetWindowText( pApp->GetProfileString( "WorldEmu", "petition_server_addr", NULL ) );
    m_ctrlPetitionServerPort.SetWindowText( pApp->GetProfileString( "WorldEmu", "petition_server_port", NULL ) );
    m_ctrlWorldId.SetWindowText( pApp->GetProfileString( "WorldEmu", "world_id", NULL ) );
    m_ctrlWorldName.SetWindowText( pApp->GetProfileString( "WorldEmu", "world_name", NULL ) );
    m_ctrlAuthServerAddr.SetWindowText( pApp->GetProfileString( "WorldEmu", "auth_server_addr", NULL ) );
    m_ctrlAuthServerPort.SetWindowText( pApp->GetProfileString( "WorldEmu", "auth_server_port", NULL ) );

    // initialize controls
    m_ctrlNumOfClients.SetWindowText( "0" );

    // get log object reference and attach list control
    m_pLog = Log::GetInstance();
    m_pLog->AttachEditCtrl( &m_ctrlLog );

    // load user database
    m_pLog->WriteLn( "Loading user database...(user.txt)" );
    int characters = m_UserDB.Load( "users.txt" );
    m_pLog->WriteLn( "Total %d characters loaded", characters );

    // must do this before launch any thread
    g_MainDlg = this;

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWorldEmuDlg::OnConnect()  // to petition server
{
    DisableAllControlAboutPetition();

    BYTE nWorldId, nGameCode;
    CString strWorldId, strWorldName;
    CString strPetitionServerAddr, strPetitionServerPort;
    m_ctrlPetitionServerAddr.GetWindowText( strPetitionServerAddr );
    m_ctrlPetitionServerPort.GetWindowText( strPetitionServerPort );
    m_ctrlWorldId.GetWindowText( strWorldId );
    m_ctrlWorldName.GetWindowText( strWorldName );
    nGameCode = (BYTE)m_ctrlGameCode.GetCurSel() + 1;
    nWorldId = (BYTE)atoi(strWorldId);

    CWinApp* pApp = AfxGetApp();
    pApp->WriteProfileString( "WorldEmu", "petition_server_addr", strPetitionServerAddr );
    pApp->WriteProfileString( "WorldEmu", "petition_server_port", strPetitionServerPort );
    pApp->WriteProfileInt( "WorldEmu", "last_game_code", nGameCode-1 );
    pApp->WriteProfileString( "WorldEmu", "world_id", strWorldId );
    pApp->WriteProfileString( "WorldEmu", "world_name", strWorldName );

    m_pPetitionService = new PetitionService( this );

    if( m_pPetitionService->Connect( strPetitionServerAddr, atoi( strPetitionServerPort ), nGameCode, nWorldId, strWorldName ) ) {
        EnableControlAtConnectToPetition();
        m_pPetitionService->StartService( WM_USER_END_PETITION_SERVICE );

    } else {
        EnableControlAtDisconnectToPetition();
        delete m_pPetitionService;
        m_pPetitionService = NULL;
    }
}

void CWorldEmuDlg::DisableAllControlAboutPetition()
{
    m_ctrlConnect.EnableWindow( FALSE );
    m_ctrlPetitionServerAddr.EnableWindow( FALSE );
    m_ctrlPetitionServerPort.EnableWindow( FALSE );
    m_ctrlWorldId.EnableWindow( FALSE );
    m_ctrlGameCode.EnableWindow( FALSE );
    m_ctrlWorldName.EnableWindow( FALSE );

    m_ctrlDisconnect.EnableWindow( FALSE );
    m_ctrlCommand.EnableWindow( FALSE );
}


void CWorldEmuDlg::EnableControlAtConnectToPetition()
{
    m_ctrlDisconnect.EnableWindow( TRUE );
    m_ctrlCommand.EnableWindow( TRUE );

    m_ctrlCommand.GetFocus();
}

void CWorldEmuDlg::EnableControlAtDisconnectToPetition()
{
    m_ctrlConnect.EnableWindow( TRUE );
    m_ctrlPetitionServerAddr.EnableWindow( TRUE );
    m_ctrlPetitionServerPort.EnableWindow( TRUE );
    m_ctrlWorldId.EnableWindow( TRUE );
    m_ctrlGameCode.EnableWindow( TRUE );
    m_ctrlWorldName.EnableWindow( TRUE );
}

void CWorldEmuDlg::OnDisconnect() // to petition server
{
    m_pLog->WriteLn( "Send : NOTIFY_WORLD_DISCONNECTION" );

    m_pPetitionService->StopService(); // -> asyncronous, cause WM_USER_END_PETITION_SERVICE
}

LRESULT CWorldEmuDlg::OnEndPetitionService( WPARAM wParam, LPARAM lParam )
{
    DisableAllControlAboutPetition();
    EnableControlAtDisconnectToPetition();
    m_ctrlPetitionList.DeleteAllItems();

    delete m_pPetitionService;
    m_pPetitionService = NULL;

    return TRUE;
}

void CWorldEmuDlg::OnConnectToAuth()
{
    m_ctrlConnectToAuth.EnableWindow( FALSE );
    m_ctrlAuthServerAddr.EnableWindow( FALSE );
    m_ctrlAuthServerPort.EnableWindow( FALSE );
    m_ctrlDisconnectToAuth.EnableWindow( TRUE );

    CString strAuthServerAddr, strAuthServerPort;
    m_ctrlAuthServerAddr.GetWindowText( strAuthServerAddr );
    m_ctrlAuthServerPort.GetWindowText( strAuthServerPort );

    CWinApp* pApp = AfxGetApp();
    pApp->WriteProfileString( "WorldEmu", "auth_server_addr", strAuthServerAddr );
    pApp->WriteProfileString( "WorldEmu", "auth_server_port", strAuthServerPort );

    m_connAuth = new AuthConn();
    AuthConn& conn = *m_connAuth;

    m_pLog->WriteLn( "Try to connect auth(%s:%d)...", strAuthServerAddr, atoi( strAuthServerPort ) );

    if( !conn.Connect( strAuthServerAddr, atoi( strAuthServerPort ) ) ) {
        m_pLog->WriteLn( "Connection fail" );

        m_ctrlDisconnectToAuth.EnableWindow( FALSE );
        m_ctrlConnectToAuth.EnableWindow( TRUE );
        m_ctrlAuthServerAddr.EnableWindow( TRUE );
        m_ctrlAuthServerPort.EnableWindow( TRUE );

        delete m_connAuth;
        m_connAuth = NULL;
    } else {
        m_pLog->WriteLn( "Connected" );

        m_AcceptClientThread = AfxBeginThread( AcceptClientProc, (void*)this );
        m_ServiceAuthServerThread = AfxBeginThread( ServiceAuthServerProc, (void*)this );
    }
}

void CWorldEmuDlg::OnDisconnectToAuth()
{
    m_connAuth->Close();
    WaitForSingleObject( m_ServiceAuthServerThread, INFINITE );
    m_ServiceAuthServerThread = NULL;

    m_ctrlConnectToAuth.EnableWindow( TRUE );
    m_ctrlDisconnectToAuth.EnableWindow( FALSE );
    m_ctrlAuthServerAddr.EnableWindow( TRUE );
    m_ctrlAuthServerPort.EnableWindow( TRUE );
}

void CWorldEmuDlg::ServiceAuthServer() // thread proc
{
    AuthConn& conn = *m_connAuth;

    int type;
    try {
        while( TRUE ) {
            type = conn.RecvPacked();
            switch( type ) {

            case SQ_ABOUT_TO_PLAY:
                {
                    m_pLog->WriteLn( "Recv : SQ_ABOUT_TO_PLAY" );
                    int uid;
                    conn.Unpack_SQ_ABOUT_TO_PLAY( &uid );
                    m_pLog->Write( "(%d)", uid );

                    m_UidPwdMap[uid] = ++m_nOneTimePwd;

                    // need setting time out for remove uid from map if client not connect

                    m_pLog->WriteLn( "Send : AS_PLAY_OK (%d,%d)", uid, m_UidPwdMap[uid] );
                    conn.Send_AS_PLAY_OK( uid, m_UidPwdMap[uid] );
                }
                break;

            case SQ_KICK_ACCOUNT:
                {
                    m_pLog->WriteLn( "Recv : SQ_KICK_ACCOUNT" );
                    int uid;
                    BYTE reason;
                    conn.Unpack_SQ_KICK_ACCOUNT( &uid, &reason );
                    m_pLog->Write( "(%d,%d)", uid, reason );

                    // send client to some notification

                    ClientConn* pConn = SAFE_RETRIEVE(m_ClientMap,uid);
                    if( pConn != NULL ) {
                        pConn->Close();
                        m_ClientMap.erase( uid );
                    }

                    // remove one time key if exist
                    m_UidPwdMap.erase( uid );
                }
                break;

            default:
                throw SocketExceptionIllegalTypePacket();
            }
        }
    } catch( SocketException ) {
        m_pLog->WriteLn( "SocketClose or Exception" );
    }

    m_connAuth->Close();
    delete m_connAuth;
    m_connAuth = NULL;

    // Terminate Accept Thread
    closesocket( m_listen_socket );
    WaitForSingleObject( m_AcceptClientThread->m_hThread, INFINITE );
    m_AcceptClientThread = NULL;
}

void CWorldEmuDlg::AcceptClient()  // thread proc
{
    m_listen_socket = socket( AF_INET, SOCK_STREAM, 0 ); /* do some error checking! */

    SOCKADDR_IN my_addr;
    memset( &my_addr, 0, sizeof(my_addr) );
    my_addr.sin_family      = AF_INET;
    my_addr.sin_port        = htons(CLIENT_LISTEN_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    /* don't forget your error checking for these calls: */
    bind( m_listen_socket, (struct sockaddr *)&my_addr, sizeof(struct sockaddr) );

    listen( m_listen_socket, CLIENT_LISTEN_BACKLOG );

    m_pLog->WriteLn( "Start waiting for client...(port: %d)", CLIENT_LISTEN_PORT );

    while( TRUE ) {
        SOCKADDR_IN their_addr;
        int sin_size = sizeof(struct sockaddr_in);
        SOCKET new_fd = accept( m_listen_socket, (SOCKADDR*)&their_addr, &sin_size );
        if( new_fd == INVALID_SOCKET ) break;

        ClientConn* pNewConn = new ClientConn();
        pNewConn->SetSocket( new_fd );

        // need setting time out for closing socket if client not send JOIN_GAME

        pNewConn->thread = AfxBeginThread( ServiceClientProc, (void*)pNewConn );
    }

    m_pLog->WriteLn( "Stop waiting for client..." );
}

void CWorldEmuDlg::ServiceClient( ClientConn* pConn ) // thread proc
{
    ClientConn& conn = *pConn;

    m_pLog->WriteLn( "Client connected." );
    InterlockedIncrement( &m_nClients );
    CString str;
    str.Format( "%d", m_nClients );
    m_ctrlNumOfClients.SetWindowText( str );

    int type;
    try {
        while( TRUE ) {
            type = conn.RecvPacked();
            switch( type ) {

            case CW_REQUEST_CHAR_LIST:
                {
                    m_pLog->WriteLn( "Recv : REQUEST_CHAR_LIST" );
                    int uid, one_time_pwd;
                    conn.Unpack_REQUEST_CHAR_LIST( &uid, &one_time_pwd );
                    m_pLog->Write( "(%d,%d)", uid, one_time_pwd );

                    OneTimePwdMap::iterator i = m_UidPwdMap.find( uid );
                    if( m_UidPwdMap.find( uid ) != m_UidPwdMap.end() ) {
                        if( one_time_pwd == m_UidPwdMap[uid] ) {
                            // OK
                            m_pLog->WriteLn( "Send : AS_PLAY_GAME(%d)", uid );
                            m_connAuth->Send_AS_PLAY_GAME( uid );
                            pConn->uid = uid;
                            pConn->begintime = time(NULL);
                            m_ClientMap[uid] = pConn;

                            int count = m_UserDB.GetCharCountOf( uid );

                            /* automatic add new user
                            if( count == 0 ) {
                                USER_INFO new_user = { max_char_int_id+1, uid, "default" };
                                m_UserMap[max_char_int_id+1] = new_user;
                                count++;
                            }*/

                            m_pLog->WriteLn( "Send : WC_CHAR_LIST (%d)", count );
                            conn.Send_USER_CHAR_LIST_1( count );
                            for( int i = 0; i < count; i++ ) {
                                conn.Send_USER_CHAR_LIST_2(
                                    m_UserDB.GetNthCharIdOf( uid, i ),
                                    m_UserDB.GetNthCharNameOf( uid, i )
                                );
                            }
                            conn.Send_USER_CHAR_LIST_3();
                        } else {
                            // Wrong One Time Password
                            m_pLog->WriteLn( "Close client: Wrong One Time Password" );
                            conn.Close();
                        }
                        m_UidPwdMap.erase( uid );
                    } else {
                        // Non-exist UID
                        m_pLog->WriteLn( "Close client: Non-exist UID" );
                        conn.Close();
                    }
                }
                break;

            case CW_JOIN_GAME:
                {
                    // do not check char_int_id in test version
                    m_pLog->WriteLn( "Recv : JOIN_GAME" );
                    conn.Unpack_JOIN_GAME( &conn.char_int_id );
                    m_pLog->Write( "(%d)", conn.char_int_id );
                }
                break;

            case CW_PETITION_COMMAND:
                {
                    m_pLog->WriteLn( "Recv : PETITION_COMMAND" );
                    char* petition_cmd;
                    conn.Unpack_PETITION_COMMAND( &petition_cmd );
                    m_pLog->Write( "(%s)", petition_cmd );

                    ProcessCommand( petition_cmd, conn.char_int_id );

                    delete [] petition_cmd;
                }
                break;

            case CW_QUIT_GAME:
                {
                    m_pLog->WriteLn( "Recv : QUIT_GAME" );

                    int current = time(NULL);
                    m_pLog->WriteLn( "Send : AS_QUIT_GAME(%d,%d,%d)", pConn->uid, 0, current - pConn->begintime );
                    m_connAuth->Send_AS_QUIT_GAME( pConn->uid, 0, current - pConn->begintime );
                    m_ClientMap.erase( pConn->uid );
                    pConn->uid = 0;
                }

            default:
                throw SocketExceptionIllegalTypePacket();
            }
        }
    } catch( SocketException ) {
        m_pLog->WriteLn( "SocketClose or Exception" );
    }

    if( pConn->uid != 0 ) {
        int current = time(NULL);
        m_pLog->WriteLn( "Send : AS_QUIT_GAME(%d,%d,%d)", pConn->uid, 1, current - pConn->begintime );
        m_connAuth->Send_AS_QUIT_GAME( pConn->uid, 1, current - pConn->begintime );
        m_ClientMap.erase( pConn->uid );
    }

    pConn->Close();
    delete pConn;
    pConn = NULL;

    InterlockedDecrement( &m_nClients );
    str.Format( "%d", m_nClients );
    m_ctrlNumOfClients.SetWindowText( str );
}

BOOL CWorldEmuDlg::PreTranslateMessage(MSG* pMsg)
{
    if( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE ) return TRUE;
    if( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN ) {
        if( m_ctrlCommand.m_hWnd == GetFocus()->m_hWnd ) {
            CString strCommand;
            m_ctrlCommand.GetWindowText( strCommand );
            ProcessCommand( strCommand );
            m_ctrlCommand.SetWindowText( "" );
        }
        return TRUE;
    }

    return CDialog::PreTranslateMessage(pMsg);
}

void CWorldEmuDlg::ProcessCommand( const char* szCommand, int char_int_id /* = 0 */ )
{
    // if char_int_id == 0 then command from console
    // if char_int_id != 0 then command from network client

    // char_id /진정 category contents
    m_pLog->WriteLn( "Command : %s", szCommand );

    if( m_pPetitionService == NULL ) {
        m_pLog->WriteLn( "Petition server is not connected currently. Ignore command." );
        return;
    }

    PetitionConn& conn = m_pPetitionService->m_conn;
    char szCmd[1024];
    strcpy( szCmd, szCommand );

    if( szCommand == NULL ) { ShowHelpMessage(); return; }

    const char* char_id;
    char* cmd ;
    if( char_int_id == 0 ) {
        char_id = strtok( szCmd, " " );
        if( char_id == NULL ) { ShowHelpMessage(); return; }

        char_int_id = m_UserDB.GetCharIntIdByName( char_id );
        if( char_int_id == 0 ) {
            m_pLog->WriteLn( "Non-exist char_id use default value(0)" );
        }

        cmd = strtok( NULL, " " );
    } else {
        char_id = m_UserDB.GetCharNameByIntId( char_int_id );

        cmd = strtok( szCmd, " " );
    }

    if( cmd == NULL ) { ShowHelpMessage(); return; }

    // 명령을 내린 캐릭터와 관련이 있는 진정이 있는지 찾아본다.
    UINT    petition_count = m_ctrlPetitionList.GetItemCount();
    /* 월드 서버는 제출 된 진정의 모든 목록을 알 수 없다.
       따라서 진정 제출 여부는 진정 서버에 의존해야 하기 때문에 아래 제약 조건을 주석처리
       확실히 막을 수 있는 상항이라도 테스트를 위해 보낼 수 있도록 완화
       */
    UINT    petition_exist = 0;
    CString petition_status;
    UINT    petition_id = 0;
    UINT    petition_index = 0;

    for( petition_index = 0; petition_index < petition_count; petition_index++ ) {
        if( !strcmp( char_id, m_ctrlPetitionList.GetItemText( petition_index, 3 ) ) ) { // check char_id
            petition_exist = 1;
            break;
        }
        if( !strcmp( char_id, m_ctrlPetitionList.GetItemText( petition_index, 4 ) ) ) { // check gm_id
            petition_exist = 2;
            break;
        }
    }
    if( petition_exist != 0 ) {
        petition_status = m_ctrlPetitionList.GetItemText( petition_index, 0 );
        petition_id = atoi( m_ctrlPetitionList.GetItemText( petition_index, 1 ) );
    }

    if( !strcmp( cmd, "/진정" ) || !strcmp( cmd, "/pet" ) ) {
        char* category_str = strtok( NULL, " " );
        if( category_str == NULL ) { ShowHelpMessage(); return; }
        BYTE category = atoi( category_str );

        char* contents = strtok( NULL, "\r\n" );
        if( contents == NULL ) { ShowHelpMessage(); return; }

        /* 진정 접수 허가 여부는 진정 서버가 판단한다.
        if( petition_exist == 1 ) {
            m_pLog->WriteLn( "이미 접수받은 진정이 있습니다." );
        } else if( petition_exist == 2 ) {
            m_pLog->WriteLn( "GM은 진정할 수 없습니다." );
        } else {
        */
            char buf[20] = "T";
            sprintf( buf, "T%d", m_nPetitionTempId );
            m_ctrlPetitionList.InsertItem( petition_count, "SUBMIT" );
            m_ctrlPetitionList.SetItemText( petition_count, 1, buf );
            m_ctrlPetitionList.SetItemText( petition_count, 2, itoa( category, buf ) );
            m_ctrlPetitionList.SetItemText( petition_count, 3, char_id );
            m_ctrlPetitionList.SetItemText( petition_count, 5, contents );

            m_pLog->WriteLn( "Send : SUBMIT_PETITION" );
            conn.Send_SUBMIT_PETITION( m_nPetitionTempId++, category, "account", char_id, char_int_id, contents );
        //}

    } else if( !strcmp( cmd, "/대화시작" ) || !strcmp( cmd, "/chatstart" ) ) {

        //if( petition_exist == 1 ) {
        //	m_pLog->WriteLn( "GM만이 대화 시작을 할 수 있습니다." );
        //} else if( petition_exist == 0 ) {
        //	m_pLog->WriteLn( "시작할 대화가 없습니다." );
        //} else {
        //	if( !strcmp( petition_status, "CHECKOUT" ) ) {
                m_ctrlPetitionList.SetItemText( petition_index, 0, "CHAT_START" );

                m_pLog->WriteLn( "Send : REQUEST_CHAT_START" );
                conn.Send_REQUEST_CHAT_START( petition_id );
        //	} else {
        //		m_pLog->WriteLn( "체크아웃 인 경우에만 대화시작을 요청할 수 있습니다." );
        //	}
        //}

    } else if( !strcmp( cmd, "/대화끝" ) || !strcmp( cmd, "/chatend" ) ) {

        //if( petition_exist && !strcmp( petition_status, "CHAT_START_OK" ) ) {
        //	if( petition_exist == 1 ) {
        //		m_pLog->WriteLn( "GM만이 대화를 끝낼 수 있습니다." );
        //	} else {
                m_ctrlPetitionList.SetItemText( petition_index, 0, "CHAT_END" );

                m_pLog->WriteLn( "Send : REQUEST_CHAT_END" );
                conn.Send_REQUEST_CHAT_END( petition_id );
        //	}
        //} else {
        //	m_pLog->WriteLn( "현재 대화 중이 아닙니다." );
        //}

    } else if( !strcmp( cmd, "/대화" ) || !strcmp( cmd, "/chat" ) ) { // 쥐엠이 멀티 상담을 하는 경우는 없다고 가정
        char* contents = strtok( NULL, "\r\n" );
        if( contents == NULL ) { ShowHelpMessage(); return; }

        //if( petition_exist && !strcmp( petition_status, "CHAT_START_OK" ) ) { // 대화중 인 경우
            if( petition_exist == 1 ) { // User
                m_pLog->WriteLn( "Send : NOTIFY_USER_CHAT" );
                conn.Send_NOTIFY_USER_CHAT( petition_id, contents );
            } else if( petition_exist == 2 ) { // GM
                m_pLog->WriteLn( "Send : NOTIFY_GM_CHAT" );
                conn.Send_NOTIFY_GM_CHAT( petition_id, contents );
            }
        //} else {
        //	m_pLog->WriteLn( "현재 대화 중이 아닙니다." );
        //}

    } else if( !strcmp( cmd, "/진정취소" ) || !strcmp( cmd, "/cancel" ) ) {
        //if( petition_exist && !strcmp( petition_status, "SUBMIT_OK" ) ) { // 진정 제출한 상태에서만 가능
            m_pLog->WriteLn( "Send : CANCEL_PETITION" );
            conn.Send_CANCEL_PETITION( char_id, char_int_id );
        //} else {
        //	m_pLog->WriteLn( "진정을 제출하고 GM이 처리하지 않은 경우에만 취소 가능합니다." );
        //}

    } else {
         ShowHelpMessage();
    }
}

void CWorldEmuDlg::ShowHelpMessage()
{
#ifdef COMPILE_KOREAN
    m_pLog->WriteLn( "Usage : <char_id> <cmd> <params> ..." );
    m_pLog->WriteLn( " : <char_id> /진정 <category> <contents>" );
    m_pLog->WriteLn( " : <char_id> /진정취소" );
    m_pLog->WriteLn( " : <char_id> /대화시작" );
    m_pLog->WriteLn( " : <char_id> /대화끝" );
    m_pLog->WriteLn( " : <char_id> /대화 <contents>" );
#endif
#ifdef COMPILE_ENGLISH
    m_pLog->WriteLn( "Usage : <char_id> <cmd> <params> ..." );
    m_pLog->WriteLn( " : <char_id> /pet <category> <contents>" );
    m_pLog->WriteLn( " : <char_id> /cancel" );
    m_pLog->WriteLn( " : <char_id> /chatstart" );
    m_pLog->WriteLn( " : <char_id> /chatend" );
    m_pLog->WriteLn( " : <char_id> /chat <contents>" );
#endif
}

BOOL CWorldEmuDlg::FindPetitionIndex( UINT petition_id, int* index )
{
    char buf[20];

    return FindPetitionIndex( itoa( petition_id, buf ), index );
}

BOOL CWorldEmuDlg::FindPetitionIndex( const char* petition_id, int* index )
{
    int petition_count = m_ctrlPetitionList.GetItemCount();
    int petition_index;

    for( petition_index = 0; petition_index < petition_count; petition_index++ )
        if( !m_ctrlPetitionList.GetItemText( petition_index, 1 ).Compare( petition_id ) )
            break;

    *index = petition_index;

    return ( petition_index != petition_count );
}

char* CWorldEmuDlg::itoa( int i, char* buf )
{
    sprintf( buf, "%d", i );
    return buf;
}

void CWorldEmuDlg::OnClose()
{
    m_pLog->Close();

    if( m_pPetitionService != NULL ) {
        m_pPetitionService->StopService();
    }

    if( m_connAuth != NULL ) {
        m_connAuth->Close();
        WaitForSingleObject( m_ServiceAuthServerThread->m_hThread, INFINITE );
    }

    CDialog::OnClose();
}

void CWorldEmuDlg::UpdatePetitionToCheckOut( UINT petition_id, LPCSTR gm_id, LPCSTR char_id )
{
    int petition_index;
    BOOL ret = FindPetitionIndex( petition_id, &petition_index );

    if( ret ) {
        m_ctrlPetitionList.SetItemText( petition_index, 0, "CHECKOUT" );
        m_ctrlPetitionList.SetItemText( petition_index, 4, gm_id );
    } else {
        char buf[20];
        m_ctrlPetitionList.InsertItem( 0, "CHECKOUT" );
        m_ctrlPetitionList.SetItemText( 0, 1, itoa( petition_id, buf ) );
        m_ctrlPetitionList.SetItemText( 0, 2, "??" );
        m_ctrlPetitionList.SetItemText( 0, 3, char_id );
        m_ctrlPetitionList.SetItemText( 0, 4, gm_id );
        m_ctrlPetitionList.SetItemText( 0, 5, "??" );
    }
}

void CWorldEmuDlg::UpdatePetitionState( UINT petition_id, LPCSTR state_label )
{
    int petition_index;
    FindPetitionIndex( petition_id, &petition_index );

    m_ctrlPetitionList.SetItemText( petition_index, 0, state_label );
}

void CWorldEmuDlg::UpdateTempPetition( UINT temp_id, UINT petition_id )
{
    char buf[20] = "T";
    sprintf( buf, "T%d", temp_id );
    int petition_index;
    FindPetitionIndex( buf, &petition_index );

    if( petition_id == 0 ) {
        m_ctrlPetitionList.SetItemText( petition_index, 0, "SUBMIT_FAIL" );
    } else {
        m_ctrlPetitionList.SetItemText( petition_index, 0, "SUBMIT_OK" );
        m_ctrlPetitionList.SetItemText( petition_index, 1, itoa( petition_id, buf ) );
    }
}

BOOL CWorldEmuDlg::IsCharOnline( int char_int_id )
{
    ClientMap::iterator pos;
    ITERATE_CONTAINER(m_ClientMap,pos) {
        if( pos->second->char_int_id == char_int_id )
            return TRUE;
    }

    return FALSE;
}
