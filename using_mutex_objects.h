#ifndef USING_MUTEX_OBJECTS_H_INCLUDED
#define USING_MUTEX_OBJECTS_H_INCLUDED

#include <windows.h>
#include <stdio.h>

namespace test_namespace
{

#define THREADCOUNT 2

HANDLE ghMutex;

DWORD WINAPI WriteToDatabase( LPVOID );

void test_using_mutex_objects()
{
    HANDLE aThread[THREADCOUNT];
    DWORD ThreadID;
    int i;

    // Create a mutex with no initial owner

    ghMutex = CreateMutex(
                  NULL,              // default security attributes
                  FALSE,             // initially not owned
                  NULL);             // unnamed mutex

    if (ghMutex == NULL)
    {
        printf("CreateMutex error: %d\n", GetLastError());
        return;
    }

    // Create worker threads

    for( i=0; i < THREADCOUNT; i++ )
    {
        aThread[i] = CreateThread(
                         NULL,       // default security attributes
                         0,          // default stack size
                         (LPTHREAD_START_ROUTINE) WriteToDatabase,
                         NULL,       // no thread function arguments
                         0,          // default creation flags
                         &ThreadID); // receive thread identifier

        if( aThread[i] == NULL )
        {
            printf("CreateThread error: %d\n", GetLastError());
            return;
        }
    }

    // Wait for all threads to terminate

    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

    // Close thread and mutex handles

    for( i=0; i < THREADCOUNT; i++ )
        CloseHandle(aThread[i]);

    CloseHandle(ghMutex);
}

DWORD WINAPI WriteToDatabase( LPVOID lpParam )
{
    DWORD dwCount=0, dwWaitResult;

    // Request ownership of mutex.

    while( dwCount < 20 )
    {
        dwWaitResult = WaitForSingleObject(
                           ghMutex,    // handle to mutex
                           INFINITE);  // no time-out interval

        switch (dwWaitResult)
        {
            // The thread got ownership of the mutex
        case WAIT_OBJECT_0:
            //__try
            {
                // TODO: Write to the database
                printf("Thread %d writing to database...\n",
                GetCurrentThreadId());
                dwCount++;
            }

            //__finally
            {
                // Release ownership of the mutex object
                if (! ReleaseMutex(ghMutex))
                {
                    // Deal with error.
                }
            }
            break;

            // The thread got ownership of an abandoned mutex
        case WAIT_ABANDONED:
            return FALSE;
        default:
            return FALSE;
        }
    }
    return TRUE;
}

}//namespace test_namespace

#endif // USING_MUTEX_OBJECTS_H_INCLUDED
