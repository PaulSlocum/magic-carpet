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
long long getCurrentTimeMSec()
{
	// GOOD VERSION...
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long long mslong = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000; //get current timestamp in milliseconds

	return( (long long) mslong );
}

//=============================================================================
long long timeSinceEventMSec( const long long eventTimeMSec )
{
  return( getCurrentTimeMSec() - eventTimeMSec );
}


//========================================================================
bool ciCharLess( char c1, char c2 )
{
    return (std::tolower( static_cast<unsigned char>( c1 ) ) < std::tolower( static_cast<unsigned char>( c2 ) ));
}
//=========================================================================
bool CompareNoCase( const std::string& s1, const std::string& s2 )
{
    return std::lexicographical_compare( s1.begin(), s1.end(), s2.begin(), s2.end(), ciCharLess );
}


//==========================================================================
void sleepFloatSeconds( const float delaySeconds )
{
	usleep(1000000*delaySeconds); 
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


//=================================================================================
std::string shortenedString( std::string inputString, unsigned maxWidth )
{
  std::string returnString;
  if( inputString.length() <= maxWidth )
  {
    returnString = inputString;
  }
  else
  {
    returnString = stdprintf( "%s..%s", trimFromPosition( inputString, maxWidth-5 ).c_str(), trimToPosition( inputString, (int)inputString.length()-5 ).c_str() );
  }
  //printf( "(SHORTENED STRING) input: %s  output: %s  maxWidth: %d \n", inputString.c_str(), returnString.c_str(), maxWidth );
  return returnString;  
} //*/


//=============================================================================
std::string lowercase( std::string incomingString )
{
  std::string outputString = incomingString;
  std::transform( outputString.begin(), outputString.end(), outputString.begin(), ::tolower);
  return( outputString );
}


//=================================================================================
bool stringEndsWith(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}


//=================================================================================
bool stringEndsWithNoCase(std::string const & value, std::string const & ending)
{
  return stringEndsWith( lowercase( value ), lowercase( ending ) );
}


//====================================================================================
std::string trimFromPosition( std::string inputString, unsigned maxLength )
{
  std::string outputString;
  if( inputString.length() <= maxLength )
    outputString = inputString;
  else
    outputString = inputString.substr( 0, maxLength );
    
  return outputString;
}

//====================================================================================
std::string trimToPosition( std::string inputString, unsigned startingIndex )
{
  std::string outputString;
  if( inputString.length() <= startingIndex )
    outputString = inputString;
  else
    outputString = inputString.substr( startingIndex, inputString.length() );
    
  return outputString;
}

