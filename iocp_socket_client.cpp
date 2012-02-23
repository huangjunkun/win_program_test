
#include "iocp_socket.h"

using namespace std;
using namespace test_namespace;


const unsigned DEFAULT_BUFLEN = 512;

int client_test()
{

    //----------------------
    // Declare and initialize variables.
    WSADATA wsaData;
    int iResult;

    SOCKET ConnectSocket;
    struct sockaddr_in clientService;
    //----------------------
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    //----------------------
    // Create a SOCKET for connecting to server
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %d\n", WSAGetLastError() );
        WSACleanup();
        return 1;
    }

    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port of the server to be connected to.
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    clientService.sin_port = htons( 10000 );

    //----------------------
    // Connect to server.
    iResult = connect( ConnectSocket, (SOCKADDR*) &clientService, sizeof(clientService) );
    if ( iResult == SOCKET_ERROR)
    {
        closesocket (ConnectSocket);
        printf("Unable to connect to server: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    for(;;)
    {
        std::string sendStr;
        std::cout << " Input sending string: ";
        std::cin >> sendStr;
        if ("exit" == sendStr)
            break;

        iResult = send( ConnectSocket, sendStr.c_str(), sendStr.size(), 0 );
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanup();
            return 1;
        }

        printf("Bytes Sent: %d\n", iResult);
    }
    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}


int main()
{
//    // 创建完成端口对象，创建工作线程处理完成端口对象中事件
//    HANDLE hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
//    ::CreateThread(NULL, 0, ClientThreadProc, (LPVOID)hCompletion, 0, 0);

    client_test();

    /* ======================== */
    cout << " Hello world!\n";
    return 0;
}

