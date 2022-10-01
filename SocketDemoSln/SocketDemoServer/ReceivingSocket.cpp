#include "pch.h"

#include "MainFrm.h"
#include "SocketDemoServer.h"
#include "ReceivingSocket.h"

#include "SimpleCommand.h"
#include "ComplexCommand.h"
#include "ScpiCommand.h"
#include "Invoker.h"


// Default ctor
CReceivingSocket::CReceivingSocket() :
	m_strSockName("Device"), m_bConnection(false), m_strID("DeviceID")
{

}

// ctor with 1 argument
CReceivingSocket::CReceivingSocket(CString strName) :
	m_strSockName(strName), m_bConnection(false), m_strID("DeviceID")
{

}

// Copy ctor
CReceivingSocket::CReceivingSocket(const CReceivingSocket& obj) :
	m_bConnection(obj.m_bConnection), m_strSockName(obj.m_strSockName), m_strID(obj.m_strID)
{
	// m_strSockName = obj.m_strSockName;
}

// Default dtor
CReceivingSocket::~CReceivingSocket()
{
}


void CReceivingSocket::OnReceive(int nErrorCode)
{
	TRACE(_T("CReceivingSocket::OnReceive() - Data Received\n"));

	static size_t nStaticCount = 0;
	char strRec[256] = "";
	// TCHAR strRec[256] = L"";

	int nCount = CSocket::Receive(strRec, 256);
	if (nCount > 0) {
//		TRACE(L"\t 0 strRec=%s\n", strRec);
//		TRACE(L"\t 1 strRec=%s", CString(strRec) );
		TRACE(_T("\t 2 [%s] strRec=%s"), GetName().GetBuffer(), CString(strRec));

		CString strData(strRec);
		CString strScpiData(strRec);

//		strData.Format(_T("%s, %s"), GetName().GetBuffer(), strRec);
		strData.Format(_T("%s, %s"), GetName().GetBuffer(), CString(strRec) );

		// ((CMFCServerApp*)AfxGetApp())->m_pServerView->AddMsg( (CString)strRec );

		if (GetName() == _T("DIO")) {
			//if (nStaticCount % 60 == 0) {
				((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddMsgDebug(strData);
			//}
			nStaticCount++;
		}
		else {

			((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddMsg(strData);
		}

		//
		// Experiment with Command
		//

		//m_CInvoker.SetOnStart(new CSimpleCommand("Say Hi!") );
		//m_CInvoker.SetOnFinish(new CSimpleCommand("Say Hi Again!"));
		// m_CInvoker.SetOnFinish(new CComplexCommand(&m_CReceiver, "Send email", "Save report") );
		// m_CInvoker.SetOnFinish(new CScpiCommand(&m_CSocketReceiver, this, _T("*IDN?") ));

		m_CInvoker.SetOnFinish(new CScpiCommand(&m_CSocketReceiver, this, strScpiData) );

		m_CInvoker.DoSomethingImportant();

	}
	CSocket::OnReceive(nErrorCode);
}


void CReceivingSocket::OnClose(int nErrorCode)
{
	// TRACE("CReceivingSocket::OnClose() - \n");

	TRACE(_T("\t Call CSocket::Detach() to detach %s from ServerSocket\n"), GetName());
	SOCKET retSocket = CSocket::Detach();

	//---
	//
	// The following is to update 'pDoc->m_bSocketConnect' and tell other views to update the UI with this info
	//  
	CSocketDemoServerDoc* pDoc = nullptr;
	CSocketDemoServerApp* pApp = (CSocketDemoServerApp*)AfxGetApp();
	pDoc = pApp->m_pServerView->GetDocument();

	std::vector<CServerSocket>::iterator pos;
	for (pos = pDoc->m_vectServerSocket.begin(); pos != pDoc->m_vectServerSocket.end(); ++pos)
	{
		// TRACE(_T("\t pos->GetName()=%s == GetName()=%s\n"), pos->GetName(), GetName());
		if (pos->GetName() == GetName()) {
			pos->SetConnection(false);	// Indicated that this socket is disconnected
		}
	}

	pDoc->UpdateAllViews(pApp->m_pServerView);	// tell other views to update the UI

	//---
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	COutputWnd * pWndOutput = pFrame->GetOutputWnd();

	if (pWndOutput != nullptr) {
		CTime startTime = CTime::GetCurrentTime();		// NIM
		CString strOutput;
		CString strDateTime  = startTime.Format("%D %H:%M:%S");

		strOutput.Format(_T("%s, %s, Socket closed - disconnected"), strDateTime.GetBuffer(), GetName().GetBuffer());
		
		pWndOutput->OutputBuildWindow(strOutput);   // Build message window
	}
	//---

	CSocket::OnClose(nErrorCode);
}
