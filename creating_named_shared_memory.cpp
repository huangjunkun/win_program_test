#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <cstring>

namespace test_namespace
{
// 	Creating Named Shared Memory
// 		To share data, multiple processes can use memory-mapped files that the system paging file stores.
//
// 		First Process

const size_t BUF_SIZE = 256;
TCHAR szName[]=TEXT("Global\\MyFileMappingObject");/// Local or Global
TCHAR szMsg[]=TEXT("Message from first process");

int the_first_process_main()
{
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = CreateFileMapping(
                   INVALID_HANDLE_VALUE,    // use paging file
                   NULL,                    // default security
                   PAGE_READWRITE,          // read/write access
                   0,                       // max. object size
                   BUF_SIZE,                // buffer size
                   szName);                 // name of mapping object

    if (hMapFile == NULL)
    {
        printf("Could not create file mapping object (%d).\n",
               GetLastError());
        return 1;
    }
	printf("Do create file mapping object.\n");
    pBuf = (LPTSTR) MapViewOfFile(hMapFile,   // handle to map object
                                  FILE_MAP_ALL_ACCESS, // read/write permission
                                  0,
                                  0,
                                  BUF_SIZE);

    if (pBuf == NULL)
    {
        printf("Could not map view of file (%d).\n",
               GetLastError());
        return 2;
    }
	else
		printf("Do map view of file.\n");


    CopyMemory((PVOID)pBuf, szMsg, strlen((const char*)szMsg));
    _getch();

    UnmapViewOfFile((void*)pBuf);

    CloseHandle(hMapFile);

    return 0;
}


// 		Second Process
int the_second_process_main()
{
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = OpenFileMapping(
                   FILE_MAP_ALL_ACCESS,   // read/write access
                   FALSE,                 // do not inherit the name
                   szName);               // name of mapping object

    if (hMapFile == NULL)
    {
        printf("Could not open file mapping object (%d).\n",
               GetLastError());
        return 1;
    }

    pBuf = (LPTSTR) MapViewOfFile(hMapFile, // handle to map object
                                  FILE_MAP_ALL_ACCESS,  // read/write permission
                                  0,
                                  0,
                                  BUF_SIZE);

    if (pBuf == NULL)
    {
        printf("Could not map view of file (%d).\n",
               GetLastError());
        return 2;
    }

    MessageBox(NULL, pBuf, TEXT("Process2"), MB_OK);

    UnmapViewOfFile((void*)pBuf);

    CloseHandle(hMapFile);

    return 0;
}

}/// namespace test_namespace

int main()
{
///*
	{
	using namespace test_namespace;
	//test_using_mutex_objects();
	the_first_process_main();
	the_second_process_main();
	}

    /** .....*/
    system("pause");
    printf("Hello world!\n");
    return 0;
}

