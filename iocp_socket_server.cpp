
#include "iocp_socket.h"

using namespace std;
using namespace test_namespace;

int main()
{

	// 创建完成端口对象，创建工作线程处理完成端口对象中事件
	HANDLE hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	HANDLE hServerThread = ::CreateThread(NULL, 0, ServerThreadProc, (LPVOID)hCompletion, 0, 0);
	// 创建监听套接字，绑定到本地地址，开始监听
	SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN si;
	si.sin_family = AF_INET;
	int nPort = 10000;
	si.sin_port = ::ntohs(nPort);
	si.sin_addr.S_un.S_addr = INADDR_ANY;
	::bind(sListen, (sockaddr*)&si, sizeof(si));
	::listen(sListen, 5);
	// 循环处理到来的连接
	while (TRUE)
	{   // 等待接受未决的连接请求
		SOCKADDR_IN saRemote;
		int nRemoteLen = sizeof(saRemote);
		SOCKET sNew = ::accept(sListen, (sockaddr*)&saRemote, &nRemoteLen);
		printf ("accept a socket.\n");

		// 接受到新连接之后，为它创建一个per-handle数据，并将它们关联到完成端口对象。
		PPER_HANDLE_DATA pPerHandle = (PPER_HANDLE_DATA)::GlobalAlloc(GPTR, sizeof(PER_HANDLE_DATA));
		pPerHandle->_socket = sNew;
		memcpy(&pPerHandle->_addr, &saRemote, nRemoteLen);
		::CreateIoCompletionPort((HANDLE)pPerHandle->_socket, hCompletion, (DWORD)pPerHandle, 0);
		// 投递一个接收请求
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

