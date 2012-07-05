
//#include <windows.h>
#include <iostream>
#include "udp_socket_test.h"
#include "tcp_socket_test.h"
#include "using_mutex_objects.h"
#include "using_event_objects.h"


using namespace std;

int main()
{

///**
    {
    using namespace test_namespace;
    //test_using_mutex_objects();
    test_using_event_objects();
    }
/**
    {
    using namespace socket_test;
//    for (;;)
//    {
//        recvfrom_test();
//    }
    for (;;)
    {
        sendto_test();
        ::Sleep(2000);
    }

    }
    /**
    {
    using namespace socket_test;
//    client_test();
     server_test();
    }
    /** .....*/
    system("pause");
    cout << "Hello world!" << endl;
    return 0;
}
