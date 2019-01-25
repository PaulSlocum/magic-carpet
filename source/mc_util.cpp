// mc_util.cpp
///////////////////////////////////////////

#include "mc_util.hpp"

#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <memory>
#include <string.h>
#include <stdarg.h>
#include <algorithm>



#pragma mark -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- ~ -- 

//==========================================================================
float convergeValue( const float currentValue, const float targetValue, const float rate )
{
    float returnValue = currentValue;
    if( returnValue < targetValue )
    {
        returnValue += rate;
        if( returnValue > targetValue )
            returnValue = targetValue;
    }
    if( returnValue > targetValue )
    {
        returnValue -= rate;
        if( returnValue < targetValue )
            returnValue = targetValue;
    }
    return returnValue;
}



//==========================================================================
std::string stdprintf( const std::string fmt_str, ... ) 
{
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::string str;
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}



//==========================================================================
long long getCurrentTimeMSec()
{
	// GOOD VERSION...
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long long mslong = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000; //get current timestamp in milliseconds

	return( (long long) mslong );
}

