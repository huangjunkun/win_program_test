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
    ///初始化Socket函数库
    WORD wVersion;
    WSADATA WSAData;
    wVersion=MAKEWORD(2,0);
    int err = ::WSAStartup(wVersion,&WSAData);
    if(err!=0)
    {
        std::cerr << "无法装载Socket库.\n";
    }
    if(LOBYTE( WSAData.wVersion ) != 2)
    {
        std::cerr << "无法找到合适的Socket 2.0库.\n";
        WSACleanup();
    }
}

/////////////////////////////////////////////////////////////////////////////

void sock_initializer::uninit()
{
    ///清除Socket库
    WSACleanup();
}

// 初始化Winsock库
sock_initializer s_initializer;

#define BUFFER_SIZE 1024

typedef struct _PER_HANDLE_DATA  // per-handle数据
{
    SOCKET		_socket; // 对应的套接字句柄
    sockaddr_in _addr; // 客户方地址
} PER_HANDLE_DATA, *PPER_HANDLE_DATA;

typedef struct _PER_IO_DATA // per-I/O数据
{
    OVERLAPPED	_overlapped;  // 重叠结构
    char	_buffer[BUFFER_SIZE];// 数据缓冲区
    int		_operation_type;// 操作类型
} PER_IO_DATA, *PPER_IO_DATA;

enum
{
    OP_READ		= 1,
    OP_WRITE	= 2,
    OP_ACCEPT	= 3
};

DWORD WINAPI ServerThreadProc(LPVOID lpParam)
{
    // 得到完成端口对象句柄
    HANDLE hCompletion = (HANDLE)lpParam;
    DWORD dwTrans;
    PPER_HANDLE_DATA pPerHandle;
    PPER_IO_DATA pPerIO;
    while(TRUE)
    {
        // 在关联到此完成端口的所有套接字上等待I/O完成
        BOOL bOK = ::GetQueuedCompletionStatus(hCompletion, &dwTrans,
                                               (LPDWORD)&pPerHandle, (LPOVERLAPPED*)&pPerIO, WSA_INFINITE);

        if(!bOK)// 在此套接字上有错误发生
        {
            printf ("close a socket.\n");
            ::closesocket(pPerHandle->_socket);
            ::GlobalFree(pPerHandle);
            ::GlobalFree(pPerIO);
            continue;
        }
        if(dwTrans == 0 && // 套接字被对方关闭
                (pPerIO->_operation_type == OP_READ || pPerIO->_operation_type == OP_WRITE))
        {

            printf ("close a socket.\n");
            ::closesocket(pPerHandle->_socket);
            ::GlobalFree(pPerHandle);
            ::GlobalFree(pPerIO);
            continue;
        }
        switch(pPerIO->_operation_type)  // 通过per-I/O数据中的nOperationType域查看什么I/O请求完成了
        {
        case OP_READ: // 完成一个接收请求
        {
            pPerIO->_buffer[dwTrans] = '\0';
            printf("recv from a socket .buffer: %s.\n", pPerIO -> _buffer);
            // 继续投递接收I/O请求
            WSABUF buf;
            buf.buf = pPerIO->_buffer ;
            buf.len = BUFFER_SIZE;
            pPerIO->_operation_type = OP_READ;
            DWORD nFlags = 0;
            ::WSARecv(pPerHandle->_socket, &buf, 1, &dwTrans, &nFlags, &pPerIO->_overlapped, NULL);
        }
        break;
        case OP_WRITE: //本例中没有投递这些类型的I/O请求
        case OP_ACCEPT:
            break;
        }
    }
    return 0;
}
//DWORD WINAPI ClientThreadProc(LPVOID lpParam)
//{
//    // 得到完成端口对象句柄
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
