
#include "iocp_socket.h"

using namespace std;
using namespace test_namespace;

int main()
{

	// ������ɶ˿ڶ��󣬴��������̴߳�����ɶ˿ڶ������¼�
	HANDLE hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	HANDLE hServerThread = ::CreateThread(NULL, 0, ServerThreadProc, (LPVOID)hCompletion, 0, 0);
	// ���������׽��֣��󶨵����ص�ַ����ʼ����
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN si;
	si.sin_family = AF_INET;
	int nPort = 10000;
	si.sin_port = ::ntohs(nPort);
	si.sin_addr.S_un.S_addr = INADDR_ANY;
	::bind(sListen, (sockaddr*)&si, sizeof(si));
	::listen(sListen, 5);
	// ѭ��������������
	while (TRUE)
	{   // �ȴ�����δ������������
		SOCKADDR_IN saRemote;
		int nRemoteLen = sizeof(saRemote);
		SOCKET sNew = ::accept(sListen, (sockaddr*)&saRemote, &nRemoteLen);
		printf ("accept a socket.\n");

		// ���ܵ�������֮��Ϊ������һ��per-handle���ݣ��������ǹ�������ɶ˿ڶ���
		PPER_HANDLE_DATA pPerHandle = (PPER_HANDLE_DATA)::GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
		pPerHandle->_socket = sNew;
		memcpy(&pPerHandle->_addr, &saRemote, nRemoteLen);
		::CreateIoCompletionPort((HANDLE)pPerHandle->_socket, hCompletion, (DWORD)pPerHandle, 0);
		// Ͷ��һ����������
		PPER_IO_DATA pPerIO = (PPER_IO_DATA)::GlobalAlloc(GPTR, sizeof(PER_IO_DATA));
		pPerIO->_operation_type = OP_READ;
		WSABUF buf;
		buf.buf = pPerIO->_buffer;
		buf.len = BUFFER_SIZE;
		DWORD dwRecv;
		DWORD dwFlags = 0;
		::WSARecv(pPerHandle->_socket, &buf, 1, &dwRecv, &dwFlags, &pPerIO->_overlapped, NULL);
	}

	CloseHandle(hServerThread);
	/* ======================== */
	cout << " Hello world!\n";
	return 0;
}

