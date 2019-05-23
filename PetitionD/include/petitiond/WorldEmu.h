// WorldEmu.h : main header file for the WORLDEMU application
//

#if !defined(AFX_WORLDEMU_H__7C820E77_1827_479B_933C_3DFDFF1B644E__INCLUDED_)
#define AFX_WORLDEMU_H__7C820E77_1827_479B_933C_3DFDFF1B644E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "petitiond/resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWorldEmuApp:
// See WorldEmu.cpp for the implementation of this class
//

class CWorldEmuApp : public CWinApp
{
public:
    CWorldEmuApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWorldEmuApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CWorldEmuApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORLDEMU_H__7C820E77_1827_479B_933C_3DFDFF1B644E__INCLUDED_)
