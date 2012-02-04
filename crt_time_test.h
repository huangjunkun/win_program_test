#ifndef CRT_TIME_TEST_H_INCLUDED
#define CRT_TIME_TEST_H_INCLUDED

// crt_times.c
// compile with: /W3
// This program demonstrates these time and date functions:
//      time         _ftime    ctime_s     asctime_s
//      _localtime64_s    _gmtime64_s    mktime    _tzset
//      _strtime_s     _strdate_s  strftime
//
// Also the global variable:
//      _tzname
//

#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>


namespace socket_test
{
int crt_time_test()
{
    char tmpbuf[128], timebuf[26], ampm[] = "AM";
    time_t ltime;
    struct _timeb tstruct;
    struct tm today, gmt, xmas = { 0, 0, 12, 25, 11, 93 };
    errno_t err;

    // Set time zone from TZ environment variable. If TZ is not set,
    // the operating system is queried to obtain the default value
    // for the variable.
    //
    _tzset();

    // Display operating system-style date and time.
    _strtime_s( tmpbuf, 128 );
    printf( "OS time:\t\t\t\t%s\n", tmpbuf );
    _strdate_s( tmpbuf, 128 );
    printf( "OS date:\t\t\t\t%s\n", tmpbuf );

    // Get UNIX-style time and display as number and string.
    time( &ltime );
    printf( "Time in seconds since UTC 1/1/70:\t%ld\n", ltime );
    err = ctime_s(timebuf, 26, &ltime);
    if (err)
    {
        printf("ctime_s failed due to an invalid argument.");
        exit(1);
    }
    printf( "UNIX time and date:\t\t\t%s", timebuf );

    // Display UTC.
    err = _gmtime64_s( &gmt, &ltime );
    if (err)
    {
        printf("_gmtime64_s failed due to an invalid argument.");
    }
    err = asctime_s(timebuf, 26, &gmt);
    if (err)
    {
        printf("asctime_s failed due to an invalid argument.");
        exit(1);
    }
    printf( "Coordinated universal time:\t\t%s", timebuf );

    // Convert to time structure and adjust for PM if necessary.
    err = _localtime64_s( &today, &ltime );
    if (err)
    {
        printf("_localtime64_s failed due to an invalid argument.");
        exit(1);
    }
    if( today.tm_hour >= 12 )
    {
        strcpy_s( ampm, sizeof(ampm), "PM" );
        today.tm_hour -= 12;
    }
    if( today.tm_hour == 0 )  // Adjust if midnight hour.
        today.tm_hour = 12;

    // Convert today into an ASCII string
    err = asctime_s(timebuf, 26, &today);
    if (err)
    {
        printf("asctime_s failed due to an invalid argument.");
        exit(1);
    }

    // Note how pointer addition is used to skip the first 11
    // characters and printf is used to trim off terminating
    // characters.
    //
    printf( "12-hour time:\t\t\t\t%.8s %s\n",
            timebuf + 11, ampm );

    // Print additional time information.
    _ftime( &tstruct ); // C4996
    // Note: _ftime is deprecated; consider using _ftime_s instead
    printf( "Plus milliseconds:\t\t\t%u\n", tstruct.millitm );
    printf( "Zone difference in hours from UTC:\t%u\n",
            tstruct.timezone/60 );
    printf( "Time zone name:\t\t\t\t%s\n", _tzname[0] ); //C4996
    // Note: _tzname is deprecated; consider using _get_tzname
    printf( "Daylight savings:\t\t\t%s\n",
            tstruct.dstflag ? "YES" : "NO" );

    // Make time for noon on Christmas, 1993.
    if( mktime( &xmas ) != (time_t)-1 )
    {
        err = asctime_s(timebuf, 26, &xmas);
        if (err)
        {
            printf("asctime_s failed due to an invalid argument.");
            exit(1);
        }
        printf( "Christmas\t\t\t\t%s\n", timebuf );
    }

    // Use time structure to build a customized time string.
    err = _localtime64_s( &today, &ltime );
    if (err)
    {
        printf(" _localtime64_s failed due to invalid arguments.");
        exit(1);
    }

    // Use strftime to build a customized time string.
    strftime( tmpbuf, 128,
              "Today is %A, day %d of %B in the year %Y.\n", &today );
    printf( tmpbuf );
}
}/// namespace socket_test

#endif // CRT_TIME_TEST_H_INCLUDED
