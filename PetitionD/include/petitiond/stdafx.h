// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__4AA3C63C_6FED_410D_ADC4_01A9CCFA7D2C__INCLUDED_)
#define AFX_STDAFX_H__4AA3C63C_6FED_410D_ADC4_01A9CCFA7D2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxsock.h>

#pragma warning(disable: 4786)

#define ITERATE_CONTAINER(container,iterator) for( iterator = container.begin(); iterator != container.end(); iterator++ )
#define SAFE_RETRIEVE(M,K) (( M.find(K) == M.end() ) ? NULL : M[K])


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__4AA3C63C_6FED_410D_ADC4_01A9CCFA7D2C__INCLUDED_)
