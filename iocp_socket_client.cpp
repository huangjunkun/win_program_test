
#include "iocp_socket.h"
#include <cstdlib>
#include <cstring>
#include <conio.h>
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
   // /*****
    string strIp = "127.0.0.1"; //default.
    int port = 10000;
    char buffer[64];
    std::cout << " Input remote IP:";
    do {
        cin.getline(buffer, sizeof(buffer));
        strIp.assign(buffer);
        size_t count = 0;
        size_t index = 0, next_index = 0;
        while (true)
        {
            (next_index = strIp.find('.', index));
            int value = atoi(strIp.substr(index, next_index-index).c_str());
//            std::cout << value << "\n";
//            getch();
            if (value >= 0 && value < 256)
            {
                 ++count;
                index = next_index+1;
                if (next_index == string::npos)
                    break;
            }
            else
                break;
        }
        if (4 == count)
            break;
        else
            std::cout << " Again input remote IP:";
    } while (true);

    std::cout << " Input remote PORT:";
    do {
        cin.getline(buffer, sizeof(buffer));
        int value = atoi(buffer);
        if (!(EINVAL  == errno || 0 == value ))
        {
            port = value;
            cout << "port:" << port << "\n";
            break;
        }
    } while (true);
    //******/
    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port of the server to be connected to.
    clientService.sin_family = AF_INET;
//    clientService.sin_addr.s_addr = inet_addr( "183.16.49.174" );//127.0.0.1
//    clientService.sin_port = htons( 10000 );
    clientService.sin_addr.s_addr = inet_addr(strIp.c_str());
    clientService.sin_port = htons( port );

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

