#include "pch.h"

#include "MainFrm.h"
#include "SocketDemoServer.h"

#include "SocketReceiver.h"
#include "ReceivingSocket.h"

#include <cstdlib>
#include <iostream>
#include <ctime>

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
	char databuffer[128];
	char * pData = "None";

	if (psocket->GetName() == _T("Vss")) {
		HandleVssMessage(psocket, a);
		return;
	}
	else if (psocket->GetName() == _T("Vp")) {
		HandleVpMessage(psocket, a);
		return;
	}
	else if (psocket->GetName() == _T("Vdd")) {
		HandleVddMessage(psocket, a);
		return;
	}
	else if (psocket->GetName() == _T("DIO")) {
		HandleDIOMessage(psocket, a);
		return;
	}

	int nIndex = a.Find(_T("?"), 0);
	if (nIndex > 0)
	{
		// Yes, it requires a reply
		int nIdx;

		CString strMsgReply(_T("None"));

		if ((nIdx = a.Find(_T("*CLS;*RST\n*IDN"), 0)) >= 0)
		{
			strMsgReply = psocket->GetID();
			int nlen = std::wcstombs(databuffer, strMsgReply.GetBuffer(), sizeof(databuffer));
			if (nlen > 0) {
				TRACE("databuffer(%s) nlen=%d\n", databuffer, nlen);
				pData = databuffer;
			}
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
		}
		else if ((nIdx = a.Find(_T(":OUTPut:STATe"), 0)) >= 0)
		{
			if (psocket->GetID() == _T("Vp")) {
				pData = "1";
			}
			else if (psocket->GetID() == _T("Vss"))
			{
				pData = "1";
			}
			else if (psocket->GetID() == _T("Vdd"))
			{
				pData = "1";
			}
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


void CSocketReceiver::HandleDIOMessage(CReceivingSocket* psocket, const CString& a)
{
	int nIdx;
	char* pData = "10";
	char databuffer[128];
	CString strMsgReply;
	static size_t nStaticCount = 0;
	bool bLogFlag = true;

	int nIndex = a.Find(_T("?"), 0);
	if (nIndex > 0)
	{
		// Yes, it requires a reply

		if ((nIdx = a.Find(_T("*CLS;*RST\n*IDN"), 0)) >= 0)
		{
			strMsgReply = psocket->GetID();
			int nlen = std::wcstombs(databuffer, strMsgReply.GetBuffer(), sizeof(databuffer));
			if (nlen > 0) {
				TRACE("databuffer(%s) nlen=%d\n", databuffer, nlen);
				pData = databuffer;
				bLogFlag = true;
			}
		}
		else if ((nIdx = a.Find(_T("SYST:COMM:TCPIP:CONTROL"), 0)) >= 0)
		{
			pData = "6682";
			bLogFlag = true;
		}
		else if ((nIdx = a.Find(_T("SENS:DIG:DATA:BIT"), 0)) >= 0)
		{
			nIdx = a.Find(_T("SENS:DIG:DATA:BIT? 4, (@1102)"), 0);
			if (nIdx >= 0)
			{
				pData = "0";		// 0
			}
			else if ((nIdx = a.Find(_T("SENS:DIG:DATA:BIT? 0, (@1102)"), 0)) >= 0)
			{
				pData = "1";		// 1
			}
			else {
				pData = "3";  // Not used
			}
			bLogFlag = false;
		}

		int len = strlen(pData);
		int nCount = psocket->Send(pData, len + 1);
		if (nCount > 0) {
			TRACE("Send(%s) %d bytes OK\n", pData, nCount);

			CString strData;
			strData.Format(_T("%s, %s"), psocket->GetName().GetBuffer(), CString(pData));

			if (bLogFlag) {
				((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddSendMsgDebug(strData);
			}
			else {
				//if (nStaticCount % 60 == 0) {
					((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddSendMsgDebug(strData);
				//}
				nStaticCount++;
			}
		}
		else {
			TRACE(_T("ERROR: Send()\n"));
		}
	}
	else {
		// No, it requires NO reply
	}
	return;
}


void CSocketReceiver::HandleVssMessage(CReceivingSocket* psocket, const CString& a)
{
	int nIdx;
	char* pData = "10";
	char databuffer[128];
	CString strMsgReply;
	static size_t nStaticCount = 0;
	bool bLogFlag = true;

	int nIndex = a.Find(_T("?"), 0);
	if (nIndex > 0)
	{
		// Yes, it requires a reply

		if ((nIdx = a.Find(_T("*CLS;*RST\n*IDN"), 0)) >= 0)
		{
			strMsgReply = psocket->GetID();
			int nlen = std::wcstombs(databuffer, strMsgReply.GetBuffer(), sizeof(databuffer));
			if (nlen > 0) {
				TRACE("databuffer(%s) nlen=%d\n", databuffer, nlen);
				pData = databuffer;
				bLogFlag = true;
			}
		}
		else if ((nIdx = a.Find(_T("SYST:COMM:TCPIP:CONTROL"), 0)) >= 0)
		{
			pData = "6682";
			bLogFlag = true;
		}
		else if ((nIdx = a.Find(_T("SOURce:VOLTage:LEVel:IMMediate:AMPLitude"), 0)) >= 0)
		{
			pData = "7.5";
		}
		else if ((nIdx = a.Find(_T("SOURce:VOLTage:PROTection:LEVel"), 0)) >= 0)
		{
			pData = "8.25";
		}
		else if ((nIdx = a.Find(_T("SOUR:CURR:LEV:IMM"), 0)) >= 0)
		{
			pData = "140.00";
		}
		else if ((nIdx = a.Find(_T("SOURce:CURRent:PROTection:STATe"), 0)) >= 0 || (nIdx = a.Find(_T("SOUR:CURR:PROT:STATe"), 0)) >= 0)
		{
			pData = "1";
		}
		else if ((nIdx = a.Find(_T("SOURce:CURRent:LEVel:IMMediate:AMPLitude"), 0)) >= 0)
		{
			pData = "140.00";
		}
		else if ((nIdx = a.Find(_T("MEAS:SCAL:CURR"), 0)) >= 0)
		{
			std::srand(std::time(nullptr)); // use current time as seed for random generator
			int random_variable = std::rand();

			float delta = (random_variable % 100) / 100.00;
			float base = 34.00;

			sprintf(databuffer, "%f", base + delta);

			// pData = "34.00";
			pData = databuffer;
		}
		else if ((nIdx = a.Find(_T("MEAS:SCAL:VOLT"), 0)) >= 0)
		{
			std::srand(std::time(nullptr)); // use current time as seed for random generator
			int random_variable = std::rand();

			float delta = (random_variable % 100) / 100.00;
			float base = 8.00;

			sprintf(databuffer, "%f", base + delta);

			// pData = "8.00";
			pData = databuffer;
		}
		else if ((nIdx = a.Find(_T(":OUTPut:STATe"), 0)) >= 0)
		{
			pData = "1";
		}

		int len = strlen(pData);
		int nCount = psocket->Send(pData, len + 1);
		if (nCount > 0) {
			TRACE("Send(%s) %d bytes OK\n", pData, nCount);

			CString strData;
			strData.Format(_T("%s, %s"), psocket->GetName().GetBuffer(), CString(pData));

			// if (bLogFlag) {
				((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddSendMsg(strData);
			//}
			//else {
			//	//if (nStaticCount % 60 == 0) {
			//	((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddSendMsg(strData);
			//	//}
			//	nStaticCount++;
			//}
		}
		else {
			TRACE(_T("ERROR: Send()\n"));
		}
	}
	else {
		// No, it requires NO reply

	}

	return;
}


void CSocketReceiver::HandleVpMessage(CReceivingSocket* psocket, const CString& a)
{
	int nIdx;
	char* pData = "10";
	char databuffer[128];
	CString strMsgReply;
	static size_t nStaticCount = 0;
	bool bLogFlag = true;

	int nIndex = a.Find(_T("?"), 0);
	if (nIndex > 0)
	{
		// Yes, it requires a reply

		if ((nIdx = a.Find(_T("*CLS;*RST\n*IDN"), 0)) >= 0)
		{
			strMsgReply = psocket->GetID();
			int nlen = std::wcstombs(databuffer, strMsgReply.GetBuffer(), sizeof(databuffer));
			if (nlen > 0) {
				TRACE("databuffer(%s) nlen=%d\n", databuffer, nlen);
				pData = databuffer;
				bLogFlag = true;
			}
		}
		else if ((nIdx = a.Find(_T("SENS:DIG:DATA:BIT"), 0)) >= 0)
		{
			nIdx = a.Find(_T("SENS:DIG:DATA:BIT? 4, (@1102)"), 0);
			if (nIdx >= 0)
			{
				pData = "0";
			}
			else if ((nIdx = a.Find(_T("SENS:DIG:DATA:BIT? 0, (@1102)"), 0)) >= 0)
			{
				pData = "1";
			}
			else 
			{
				pData = "3";
			}
			bLogFlag = false;
		}
		else if ((nIdx = a.Find(_T("SYST:COMM:TCPIP:CONTROL"), 0)) >= 0)
		{
			pData = "6682";
			bLogFlag = true;
		}
		else if ((nIdx = a.Find(_T("SOURce:VOLTage:LEVel:IMMediate:AMPLitude"), 0)) >= 0)
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
		else if ((nIdx = a.Find(_T("SOURce:CURRent:PROTection:STATe"), 0)) >= 0 || (nIdx = a.Find(_T("SOUR:CURR:PROT:STATe"), 0)) >= 0)
		{
			strMsgReply = _T("1");
			pData = "1";
		}
		else if ((nIdx = a.Find(_T("SOUR:CURR:LEV:IMM"), 0)) >= 0)
		{
			pData = "250.00";
		}
		else if ((nIdx = a.Find(_T("MEAS:SCAL:CURR"), 0)) >= 0)
		{
			std::srand(std::time(nullptr)); // use current time as seed for random generator
			int random_variable = std::rand();

			float delta = (random_variable % 100) / 100.00;
			float base = 63.00;

			sprintf(databuffer, "%f", base + delta);

			//pData = "63.00";
			pData = databuffer;
		}
		else if ((nIdx = a.Find(_T("MEAS:SCAL:VOLT"), 0)) >= 0)
		{
			std::srand(std::time(nullptr)); // use current time as seed for random generator
			int random_variable = std::rand();

			float delta = (random_variable % 100) / 100.00;
			float base = 7.00;

			sprintf(databuffer, "%f", base + delta);

			//pData = "7.00";
			pData = databuffer;
		}
		else if ((nIdx = a.Find(_T(":OUTPut:STATe"), 0)) >= 0)
		{
			pData = "1";
		}

		int len = strlen(pData);
		int nCount = psocket->Send(pData, len + 1);
		if (nCount > 0) {
			// TRACE("Send(%s) %d bytes OK\n", pData, nCount);

			CString strData;
			strData.Format(_T("%s, %s"), psocket->GetName().GetBuffer(), CString(pData));
			((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddSendMsg(strData);
		}
		else {
			TRACE(_T("ERROR: Send()\n"));
		}
	}
	else {
		// No, it requires NO reply
	}
	return;
}



void CSocketReceiver::HandleVddMessage(CReceivingSocket* psocket, const CString& a)
{
	int nIdx;
	char* pData = "10";
	char databuffer[128];
	CString strMsgReply;
	static size_t nStaticCount = 0;
	bool bLogFlag = true;

	int nIndex = a.Find(_T("?"), 0);
	if (nIndex > 0)
	{
		// Yes, it requires a reply

		if ((nIdx = a.Find(_T("*CLS;*RST\n*IDN"), 0)) >= 0)
		{
			strMsgReply = psocket->GetID();
			int nlen = std::wcstombs(databuffer, strMsgReply.GetBuffer(), sizeof(databuffer));
			if (nlen > 0) {
				TRACE("databuffer(%s) nlen=%d\n", databuffer, nlen);
				pData = databuffer;
				bLogFlag = true;
			}
		}
		else if ((nIdx = a.Find(_T("SYST:COMM:TCPIP:CONTROL"), 0)) >= 0)
		{
			pData = "6682";
			bLogFlag = true;
		}
		else if ((nIdx = a.Find(_T("SOURce:VOLTage:LEVel:IMMediate:AMPLitude"), 0)) >= 0)
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
		else if ((nIdx = a.Find(_T("SOURce:CURRent:PROTection:STATe"), 0)) >= 0 || (nIdx = a.Find(_T("SOUR:CURR:PROT:STATe"), 0)) >= 0)
		{
			strMsgReply = _T("1");
			pData = "1";
		}
		else if ((nIdx = a.Find(_T("SOUR:CURR:LEV:IMM"), 0)) >= 0)
		{
			pData = "10.00";
		}
		else if ((nIdx = a.Find(_T("MEAS:SCAL:CURR"), 0)) >= 0)
		{
			std::srand(std::time(nullptr)); // use current time as seed for random generator
			int random_variable = std::rand();

			float delta = (random_variable % 100) / 100.00;
			float base = 9.00;

			sprintf(databuffer, "%f", base + delta);

			//pData = "9.00";
			pData = databuffer;
		}
		else if ((nIdx = a.Find(_T("MEAS:SCAL:VOLT"), 0)) >= 0)
		{
			std::srand(std::time(nullptr)); // use current time as seed for random generator
			int random_variable = std::rand();

			float delta = (random_variable % 100) / 100.00;
			float base = 9.00;

			sprintf(databuffer, "%f", base + delta);

			//pData = "9.00";
			pData = databuffer;
		}
		else if ((nIdx = a.Find(_T(":OUTPut:STATe"), 0)) >= 0)
		{
			pData = "1";
		}

		int len = strlen(pData);
		int nCount = psocket->Send(pData, len + 1);
		if (nCount > 0) {
			TRACE("Send(%s) %d bytes OK\n", pData, nCount);

			CString strData;
			strData.Format(_T("%s, %s"), psocket->GetName().GetBuffer(), CString(pData));

			//if (bLogFlag) {
				((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddSendMsg(strData);
			//}
			//else {
			//	//if (nStaticCount % 60 == 0) {
			//	((CSocketDemoServerApp*)AfxGetApp())->m_pServerView->AddSendMsg(strData);
			//	//}
			//	nStaticCount++;
			//}
		}
		else {
			TRACE(_T("ERROR: Send()\n"));
		}
	}
	else {
		// No, it requires NO reply
	}
	return;
}
