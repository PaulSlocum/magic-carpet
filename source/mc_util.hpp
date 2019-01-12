// mpUtil.h
////////////////////////////////////////////

#include <iostream>
#include <string>
#include <stdarg.h>  // For va_start, etc.
//#include <SDL2/SDL.h> 


//#define COMMENT_CHARACTER '#'

long long getCurrentTimeMSec();
long long timeSinceEventMSec( long long eventTimeMSec );

void sleepFloatSeconds( float delaySeconds );

std::string logf(const std::string fmt_str, ...);

std::string stdprintf(const std::string fmt_str, ...);
std::string stdpopen(const std::string fmt_str, ...);

std::string shortenedString( std::string inputString, unsigned maxWidth );

bool CompareNoCase( const std::string& s1, const std::string& s2 );

std::string lowercase( std::string incomingString );
bool stringEndsWith(std::string const & value, std::string const & ending);
bool stringEndsWithNoCase(std::string const & value, std::string const & ending);
std::string trimFromPosition( std::string inputString, unsigned maxLength );
std::string trimToPosition( std::string inputString, unsigned maxLength );

std::string removeFilenamePath( std::string filename );

