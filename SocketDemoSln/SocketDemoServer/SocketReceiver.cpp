#include "pch.h"

#include "MainFrm.h"
#include "SocketDemoServer.h"

#include "SocketReceiver.h"
#include "ReceivingSocket.h"

void CSocketReceiver::ProcessCommand(const CString& a) 
{
	// std::cout << "Receiver: Working on (" << a << ".)\n";
	TRACE(_T("CSocketReceiver::ProcessCommand() - Receiver: Working on (%s)\n"), a);
}


void CSocketReceiver::ProcessCommand2(CReceivingSocket* psocket, const CString& a) 
{
	// std::cout << "Receiver: Working on (" << a << ".)\n";
	// TRACE(_T("CSocketReceiver::ProcessCommand2() - %s, Receiver: Working on (%s)"), psocket->GetName() , a);
	static int nCount = 0;

	int nIndex = a.Find(_T("?"), 0);
	if (nIndex > 0)
	{
		// Yes, it requires a reply
		int nIdx;

		CString strMsgReply(_T("None"));
		char * pData = "None";

		if (a == _T("*IDN?"))
		{
			strMsgReply = psocket->GetID();

			// Send reply
			int len = strMsgReply.GetLength();
			TCHAR* pTData = strMsgReply.GetBuffer(len);

			int nCount = psocket->Send(pTData, len * 2);
			if (nCount > 0) {
				TRACE(_T("Send(%s) %d bytes OK\n"), pTData, nCount);
			}
			else {
				TRACE(_T("ERROR: Send()\n"));
			}
			return;

		}
		else if ((nIdx = a.Find(_T("*CLS;*RST\n*IDN"), 0)) >= 0)
		{
			strMsgReply = psocket->GetID();

			// Send reply
			int len = strMsgReply.GetLength();
			TCHAR* pTData = strMsgReply.GetBuffer(len);

			int nCount = psocket->Send(pTData, len * 2);
			if (nCount > 0) {
				TRACE(_T("Send(%s) %d bytes OK\n"), pTData, nCount);
			}
			else {
				TRACE(_T("ERROR: Send()\n"));
			}
			return;
		}
		else if ( (nIdx = a.Find(_T("SYST:COMM:TCPIP:CONTROL"), 0)) >= 0)
		{
			strMsgReply = _T("6681");
			pData = "6681";
		}
		else if ( (nIdx = a.Find(_T("SOURce:VOLTage:LEVel:IMMediate:AMPLitude"), 0)) >= 0)
		{
			strMsgReply = _T("7.5");
			pData = "7.5";
		}
		else if ((nIdx = a.Find(_T("SOURce:VOLTage:PROTection:LEVel"), 0)) >= 0)
		{
			strMsgReply = _T("8.25");
			pData = "8.25";
		}
		else if ((nIdx = a.Find(_T("SOURce:CURRent:LEVel:IMMediate:AMPLitude"), 0)) >= 0)
		{
			strMsgReply = _T("140.00");
			pData = "140.00";
		}
		else if ((nIdx = a.Find(_T("SOURce:CURRent:PROTection:STATe"), 0)) >= 0 || (nIdx = a.Find(_T("SOUR:CURR:PROT:STATe"), 0)) >= 0 )
		{
			strMsgReply = _T("1");
			pData = "1";
		}
		else if ((nIdx = a.Find(_T("SOUR:CURR:LEV:IMM"), 0)) >= 0)
		{
			if (nCount%3 == 0) {
				strMsgReply = _T("140.00");
				pData = "140.00";

			}
			else if (nCount%3 == 1)
			{
				pData = "250.00";
			}
			else if (nCount%3 == 2)
			{
				pData = "10.00";
			}
			nCount++;
		}
		else if ((nIdx = a.Find(_T("MEAS:SCAL:CURR"), 0)) >= 0)
		{
			if (psocket->GetID() == _T("Vp") ) {
				pData = "63.00";
			}
			else if (psocket->GetID() == _T("Vss"))
			{
				pData = "34.00";
			}
			else if (psocket->GetID() == _T("Vdd"))
			{
				pData = "9.00";
			}
		}
		else if ((nIdx = a.Find(_T("MEAS:SCAL:VOLT"), 0)) >= 0)
		{
			if (psocket->GetID() == _T("Vp")) {
				pData = "7.00";
			}
			else if (psocket->GetID() == _T("Vss"))
			{
				pData = "8.00";
			}
			else if (psocket->GetID() == _T("Vdd"))
			{
				pData = "9.00";
			}

			//int len = strlen(pData);
			//int nCount = psocket->Send(pData, len + 1);
			//if (nCount > 0) {
			//	//TRACE("Send(%s) %d bytes OK\n", pData, nCount);
			//}
			//else {
			//	TRACE(_T("ERROR: Send()\n"));
			//}
			//return;
		}
		else if ((nIdx = a.Find(_T(":OUTPut:STATe"), 0)) >= 0)
		{
			if (psocket->GetID() == _T("Vp")) {
				pData = "ON";
			}
			else if (psocket->GetID() == _T("Vss"))
			{
				pData = "ON";
			}
			else if (psocket->GetID() == _T("Vdd"))
			{
				pData = "ON";
			}

			//int len = strlen(pData);
			//int nCount = psocket->Send(pData, len + 1);
			//if (nCount > 0) {
			//	//TRACE("Send(%s) %d bytes OK\n", pData, nCount);
			//}
			//else {
			//	TRACE(_T("ERROR: Send()\n"));
			//}
			//return;
		}

		int len = strlen(pData);
		int nCount = psocket->Send(pData, len + 1);
		if (nCount > 0) {
			TRACE("Send(%s) %d bytes OK\n", pData, nCount);

			CString strData;
			strData.Format(_T("%s, %s"), psocket->GetName().GetBuffer(), CString(pData));
			if (psocket->GetName() == _T("DIO")) {
				((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddSendMsgDebug(strData);
			}
			else {

				((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddSendMsg(strData);
			}
		}
		else {
			TRACE(_T("ERROR: Send()\n"));
		}
	}
	else
	{
		// No, it requires NO reply
	}

}