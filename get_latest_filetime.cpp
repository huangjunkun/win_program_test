// vc2003_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <tchar.h>
#include <Windows.h>
#include ".\ConnectInfo.h"

using namespace std;

#ifdef _UNICODE
	#define info(msg) do { std::wcout << msg << "\n"; } while(0)
	#define debug(msg) do { std::wcout << msg << "\n"; } while(0)
#else
	#define info(msg) do { std::cout << msg << "\n"; } while(0)
	#define debug(msg) do { std::cout << msg << "\n"; } while(0)
#endif


FILETIME get_latest_filetime(TCHAR path[],bool is_dir )
{
	FILETIME res = {0};

	if (path[0]==_T('%') && _tcsnicmp(path,_T("%SystemRoot%"),12)==0)  //路径中包含%SystemRoot%,则替换为实际路径
	{
		TCHAR tmp_path[MAX_PATH];
		_tcsncpy(tmp_path,path+12,MAX_PATH);
// 		if ( (get_systemroot_path(path) ) <= 0 )
// 		{
// 			info("Can't find SystemRoot");
// 			return res;
// 		}
		_tcscpy(path, _T("d:\\Windows"));
		_tcsncat(path,tmp_path,MAX_PATH);
	}
	if (is_dir)		//如果是目录，则取所有子文件
	{
		_tcsncat(path,_T("\\*.*"),MAX_PATH);
	}

	info("crash_finder::get_latest_filename : crash path= "<<path);

	WIN32_FIND_DATA data;

	HANDLE handle = ::FindFirstFile( path, &data );
	if( handle == INVALID_HANDLE_VALUE )
	{
		debug("No Dump File");
		return res;
	}

	if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//是目录
	{
		while (::FindNextFile(handle,&data))
		{
			if (data.cFileName[0] ==_T('.')) // "."  or ".."
				continue;
			if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				continue;
			if ( data.ftCreationTime.dwHighDateTime > res.dwHighDateTime ||
				(data.ftCreationTime.dwHighDateTime == res.dwHighDateTime 
				&& data.ftCreationTime.dwLowDateTime > res.dwLowDateTime ) )
			{
				debug("file name = "<<data.cFileName);
				res = data.ftCreationTime;
			}
		}
	}
	else			//文件
	{
		res = data.ftCreationTime;
	}

	::FindClose(handle);
	return res;

}

#define TOTALBYTES    8192
#define BYTEINCREMENT 4096

void test_RegQueryValueEx()
{
// 	If lpData is NULL, and lpcbData is non-NULL, the function returns ERROR_SUCCESS and stores the size of the data, in bytes, 
// 		in the variable pointed to by lpcbData. This enables an application to determine the best way to allocate a buffer for the value's data.
// 
// 	If hKey specifies HKEY_PERFORMANCE_DATA and the lpData buffer is not large enough to contain all of the returned data, 
// 	RegQueryValueEx returns ERROR_MORE_DATA and the value returned through the lpcbData parameter is undefined. 
// 	This is because the size of the performance data can change from one call to the next. 
// 	In this case, you must increase the buffer size and call RegQueryValueEx again passing the updated buffer size in the lpcbData parameter. 
// 	Repeat this until the function succeeds. You need to maintain a separate variable to keep track of the buffer size, 
// 	because the value returned by lpcbData is unpredictable.

    DWORD BufferSize = TOTALBYTES;
    PPERF_DATA_BLOCK PerfData = NULL;

    printf("Allocating memory...\n");
    while( RegQueryValueEx( HKEY_PERFORMANCE_DATA,
                            TEXT("Global"),
                            NULL,
                            NULL,
                            (LPBYTE) PerfData,
                            &BufferSize ) == ERROR_MORE_DATA )
    {
		// Get a buffer that is big enough.
        BufferSize += BYTEINCREMENT;
		PerfData = (PPERF_DATA_BLOCK) realloc( PerfData, BufferSize );
		printf("Allocating +BYTEINCREMENT(4096), %d.\n", BufferSize);
    }
    printf("\nFinal buffer size is %d.\n", BufferSize);
}

int test()
{
// 	// test crash ...
// 	const unsigned BUFFER_SIZE = 2 * 1024 * 1024;
// 	char *buffer = new char[BUFFER_SIZE];
// 	buffer[BUFFER_SIZE+10] = '\0';
// 	delete[] buffer;
// 	char buf[100];
// 	buf[100] = '\0';
	info ( "sizeof(TCHAR) " << sizeof(TCHAR));
	const unsigned PATH_MAX = 256;
	TCHAR path1[PATH_MAX] = _T("%SystemRoot%\\MEMORY.DMP");
	TCHAR path2[PATH_MAX] = _T("%SystemRoot%\\Minidump");
	info ( "get_latest_filetime " << (long long&)get_latest_filetime(path1, false));
	info ( "get_latest_filetime " << (long long&)get_latest_filetime(path2, true));
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	test();
	test_RegQueryValueEx();
	/**     */
	cout << "\n Input any char to end.\n" << endl;
	getch();
	return 0;
}

