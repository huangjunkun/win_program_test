#ifndef UDP_SOCKET_TEST_H_INCLUDED
#define UDP_SOCKET_TEST_H_INCLUDED



#include <stdio.h>
#include "winsock2.h"

#pragma comment(lib, "Ws2_32.lib");

namespace socket_test
{

void recvfrom_test()
{

    WSADATA wsaData;
    SOCKET RecvSocket;
    sockaddr_in RecvAddr;
    int Port = 27015;
    char RecvBuf[1024];
    int  BufLen = 1024;
    sockaddr_in SenderAddr;
    int SenderAddrSize = sizeof(SenderAddr);

    //-----------------------------------------------
    // Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsaData);

    //-----------------------------------------------
    // Create a receiver socket to receive datagrams
    RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (RecvSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError() );
        WSACleanup();
        return;
    }

    //-----------------------------------------------
    // Bind the socket to any address and the specified port.
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);


//////////////////////////////////////////////////////////////////////////
    bind(RecvSocket, (SOCKADDR *) &RecvAddr, sizeof(RecvAddr));

    //-----------------------------------------------
    // Call the recvfrom function to receive datagrams
    // on the bound socket.
    printf("Receiving datagrams...\n");
    recvfrom(RecvSocket,
             RecvBuf,
             BufLen,
             0,
             (SOCKADDR *)&SenderAddr,
             &SenderAddrSize);

    //-----------------------------------------------
    // Close the socket when finished receiving datagrams
    printf("Finished receiving. Closing socket.\n");
    closesocket(RecvSocket);

    //-----------------------------------------------
    // Clean up and exit.
    printf("Exiting.\n");
    WSACleanup();
    return;
}


void sendto_test()
{
    WSADATA wsaData;
    SOCKET SendSocket;
    sockaddr_in RecvAddr;
    int Port = 27015;
    char SendBuf[1024];
    int BufLen = 1024;

    //---------------------------------------------
    // Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsaData);

    //---------------------------------------------
    // Create a socket for sending data
    SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (SendSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError() );
        WSACleanup();
        return;
    }
    //---------------------------------------------
    // Set up the RecvAddr structure with the IP address of
    // the receiver (in this example case "127.0.0.1")
    // and the specified port number.
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //---------------------------------------------
    // Send a datagram to the receiver
    printf("Sending a datagram to the receiver...\n");
    sendto(SendSocket,
           SendBuf,
           BufLen,
           0,
           (SOCKADDR *) &RecvAddr,
           sizeof(RecvAddr));

    //---------------------------------------------
    // When the application is finished sending, close the socket.
    printf("Finished sending. Closing socket.\n");
    closesocket(SendSocket);

    //---------------------------------------------
    // Clean up and quit.
    printf("Exiting.\n");
    WSACleanup();
    return;
}

//////////////////////////////////////////////////////////////////////////
} /// namespace socket_test

#endif // UDP_SOCKET_TEST_H_INCLUDED
