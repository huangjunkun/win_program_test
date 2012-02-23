#ifndef __IOCP_SOCKET_H_
#define __IOCP_SOCKET_H_


#include <iostream>
#include <cstdio>
using namespace std;

//#include <Windows.h>
#include <WinSock2.h>
//#pragma comment(lib,"Ws2_32.lib")//???



namespace test_namespace
{
void TestFunc()
{

}

class sock_initializer
{
public:
    sock_initializer()
    {
        //if(!pInstance)
        //	pInstance = create_instance();
        if(!s_count_ref)
            init();
        ++s_count_ref;
    }
    ~sock_initializer()
    {
        --s_count_ref;
        if (!s_count_ref)
            uninit();
    }
private:
    void init();//initialize socket
    void uninit();//uninitialize socket
    //static sock_initializer*	_pInstance;
    static size_t	s_count_ref;
};

size_t	sock_initializer::s_count_ref = 0;

void sock_initializer::init()
{
    ///��ʼ��Socket������
    WORD wVersion;
    WSADATA WSAData;
    wVersion=MAKEWORD(2,0);
    int err = ::WSAStartup(wVersion,&WSAData);
    if(err!=0)
    {
        std::cerr << "�޷�װ��Socket��.\n";
    }
    if(LOBYTE( WSAData.wVersion ) != 2)
    {
        std::cerr << "�޷��ҵ����ʵ�Socket 2.0��.\n";
        WSACleanup();
    }
}

/////////////////////////////////////////////////////////////////////////////

void sock_initializer::uninit()
{
    ///���Socket��
    WSACleanup();
}

// ��ʼ��Winsock��
sock_initializer s_initializer;

#define BUFFER_SIZE 1024

typedef struct _PER_HANDLE_DATA  // per-handle����
{
    SOCKET		_socket; // ��Ӧ���׽��־��
    sockaddr_in _addr; // �ͻ�����ַ
} PER_HANDLE_DATA, *PPER_HANDLE_DATA;

typedef struct _PER_IO_DATA // per-I/O����
{
    OVERLAPPED	_overlapped;  // �ص��ṹ
    char	_buffer[BUFFER_SIZE];// ���ݻ�����
    int		_operation_type;// ��������
} PER_IO_DATA, *PPER_IO_DATA;

enum
{
    OP_READ		= 1,
    OP_WRITE	= 2,
    OP_ACCEPT	= 3
};

DWORD WINAPI ServerThreadProc(LPVOID lpParam)
{
    // �õ���ɶ˿ڶ�����
    HANDLE hCompletion = (HANDLE)lpParam;
    DWORD dwTrans;
    PPER_HANDLE_DATA pPerHandle;
    PPER_IO_DATA pPerIO;
    while(TRUE)
    {
        // �ڹ���������ɶ˿ڵ������׽����ϵȴ�I/O���
        BOOL bOK = ::GetQueuedCompletionStatus(hCompletion, &dwTrans,
                                               (LPDWORD)&pPerHandle, (LPOVERLAPPED*)&pPerIO, WSA_INFINITE);

        if(!bOK)// �ڴ��׽������д�����
        {
            printf ("close a socket.\n");
            ::closesocket(pPerHandle->_socket);
            ::GlobalFree(pPerHandle);
            ::GlobalFree(pPerIO);
            continue;
        }
        if(dwTrans == 0 && // �׽��ֱ��Է��ر�
                (pPerIO->_operation_type == OP_READ || pPerIO->_operation_type == OP_WRITE))
        {

            printf ("close a socket.\n");
            ::closesocket(pPerHandle->_socket);
            ::GlobalFree(pPerHandle);
            ::GlobalFree(pPerIO);
            continue;
        }
        switch(pPerIO->_operation_type)  // ͨ��per-I/O�����е�nOperationType��鿴ʲôI/O���������
        {
        case OP_READ: // ���һ����������
        {
            pPerIO->_buffer[dwTrans] = '\0';
            printf("recv from a socket .buffer: %s.\n", pPerIO -> _buffer);
            // ����Ͷ�ݽ���I/O����
            WSABUF buf;
            buf.buf = pPerIO->_buffer ;
            buf.len = BUFFER_SIZE;
            pPerIO->_operation_type = OP_READ;
            DWORD nFlags = 0;
            ::WSARecv(pPerHandle->_socket, &buf, 1, &dwTrans, &nFlags, &pPerIO->_overlapped, NULL);
        }
        break;
        case OP_WRITE: //������û��Ͷ����Щ���͵�I/O����
        case OP_ACCEPT:
            break;
        }
    }
    return 0;
}
//DWORD WINAPI ClientThreadProc(LPVOID lpParam)
//{
//    // �õ���ɶ˿ڶ�����
//    HANDLE hCompletion = (HANDLE)lpParam;
//    DWORD dwTrans;
//    PPER_HANDLE_DATA pPerHandle;
//    PPER_IO_DATA pPerIO;
//    while(TRUE)
//    {
//
//    }
//}

}//namespace test_namespace

#endif //__IOCP_SOCKET_H_
