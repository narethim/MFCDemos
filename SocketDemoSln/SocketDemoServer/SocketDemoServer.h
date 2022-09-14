
// SocketDemoServer.h : main header file for the SocketDemoServer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#include "ServerSocket.h"
#include "SocketDemoServerView.h"

// Forward declraration
//class CServerSocket;
class CSocketDemoServerView;

// CSocketDemoServerApp:
// See SocketDemoServer.cpp for the implementation of this class
//

class CSocketDemoServerApp : public CWinAppEx
{
public:
	CSocketDemoServerApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	CServerSocket   m_serverSocket;
	// CServer2Socket  m_server2Socket;

	CSocketDemoServerView* m_pServerView;
};

extern CSocketDemoServerApp theApp;
