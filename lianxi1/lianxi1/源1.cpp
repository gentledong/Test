#include <iostream>
#include <windows.h>
#include <assert.h>
//#include <afx.h>

using namespace std;

int main(){
	HANDLE COMFile = CreateFile("//./COM1", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,
		NULL);
	if (INVALID_HANDLE_VALUE == COMFile) {
		return (FALSE);
	}//if
	SetupComm(COMFile, 6000, 6000);
	SetCommMask(COMFile, EV_RXCHAR);
	
	COMMTIMEOUTS CommTimeOuts;
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 1000;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 2 * CBR_9600 / 9600;
	CommTimeOuts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts(COMFile, &CommTimeOuts);
	
	DCB dcb;
	dcb.DCBlength = sizeof(DCB);
	GetCommState(COMFile, &dcb);
	dcb.BaudRate = CBR_9600;
	dcb.StopBits = ONESTOPBIT;
	dcb.Parity = NOPARITY;
	dcb.ByteSize = 8;
	dcb.fBinary = TRUE;
	dcb.fOutxDsrFlow = 0;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fOutxCtsFlow = 0;
	dcb.fRtsControl = RTS_CONTROL_ENABLE;
	dcb.fInX = dcb.fOutX = 1;
	dcb.XonChar = 0X11;
	dcb.XoffChar = 0X13;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;
	dcb.fParity = TRUE;
	BOOL fRetVal;
	fRetVal = SetCommState(COMFile, &dcb);
	if (!fRetVal) return FALSE;

	PurgeComm(COMFile, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	EscapeCommFunction(COMFile, SETDTR);

	
	//OVERLAPPED wrOverlapped;
	//ZeroMemory(&wrOverlapped, sizeof(wrOverlapped));
	//if (wrOverlapped.hEvent != NULL) {
	//	ResetEvent(wrOverlapped.hEvent);
	//	wrOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	//}//if
	//DWORD dwError;
	//DWORD dwRealSend = 0;
	//char *pSendBuffer = new char[100]{ "hello" };
	//if (!WriteFile(COMFile, pSendBuffer, sizeof(pSendBuffer), &dwRealSend, &wrOverlapped)) {
	//	if (GetLastError() == ERROR_IO_PENDING) {
	//		while (!GetOverlappedResult(COMFile, &wrOverlapped, &dwRealSend, FALSE)) {
	//			if (GetLastError() == ERROR_IO_INCOMPLETE) {
	//				cout << "дδ��ɣ�����!" << endl;
	//				continue;
	//			}
	//			else {
	//				cout << "�������󣬳��Իָ���" << endl;
	//				ClearCommError(COMFile, &dwError, NULL);
	//				break;
	//			}//if else
	//		}//while
	//	}//if
	//}//if
	//cout << "Write:" << pSendBuffer << endl;

	//DWORD dwWantRead = 100;
	//DWORD dwRealRead = 0;
	//char* pReadBuf = new char[100];

	//if (!ReadFile(COMFile, pReadBuf, strlen(pSendBuffer), &dwRealRead, &wrOverlapped)) {
	//	if (dwError = GetLastError() == ERROR_IO_PENDING) {
	//		while (GetOverlappedResult(COMFile, &wrOverlapped, &dwRealRead, FALSE)) {
	//			//�Խ��յ������ݽ������ݽ���������
	//			cout << "dwRealRead = " << endl;
	//		}//while
	//	}//if
	//}//if
	//cout << "Read:" << pReadBuf << endl;



	char lpInBuffer[1024]{"love you"};
	DWORD dwBytesRead = 1024;
	BOOL bReadStatus;
	DWORD dwErrorFlags;
	COMSTAT ComStat;
	OVERLAPPED m_osRead;
	ClearCommError(COMFile, &dwErrorFlags, &ComStat);
	if (!ComStat.cbInQue) {
		//return 0;
	}
	dwBytesRead = min(dwBytesRead, (DWORD)ComStat.cbInQue);
	bReadStatus = ReadFile(COMFile, lpInBuffer, dwBytesRead,&dwBytesRead, &m_osRead);
	if (!bReadStatus){ //���ReadFile��������FALSE 
		if (GetLastError() == ERROR_IO_PENDING){
			GetOverlappedResult(COMFile, &m_osRead, &dwBytesRead, TRUE);
			// GetOverlappedResult���������һ��������ΪTRUE�� 
			//������һֱ�ȴ���ֱ����������ɻ����ڴ�������ء� 
			return dwBytesRead;
		}//if
		//return 0;
	}//if
	cout << "Write:" << lpInBuffer << endl;

	char buffer[1024];
	DWORD dwBytesWritten = 1024;
	OVERLAPPED m_osWrite;
	BOOL bWriteStat;
	bWriteStat = WriteFile(COMFile, buffer, dwBytesWritten, &dwBytesWritten, &m_osWrite);

	if (!bWriteStat){
		if (GetLastError() == ERROR_IO_PENDING){
			WaitForSingleObject(m_osWrite.hEvent, 1000);
			return dwBytesWritten;
		}//if
		//return 0;
	}//if
	cout << "Read:" << buffer << endl;
	

	
	//��ֹ���ж˿������¼� 
	SetCommMask(COMFile, 0);
	//��������ն˾����ź� 
	EscapeCommFunction(COMFile, CLRDTR);
	//����ͨ����Դ����������뻺�����ַ�����ֹ��ͨ����Դ�Ϲ���Ķ���д�ٲ��� 
	PurgeComm(COMFile, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	CloseHandle(COMFile);
	COMFile = NULL;
	return 0;
}
