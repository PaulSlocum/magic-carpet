// mpUtil.h
////////////////////////////////////////////

#include <string>


std::string stdprintf( const std::string fmt_str, ... );

long long getCurrentTimeMSec();

float convergeValue( const float currentValue, const float targetValue, const float rate );


void logerr( const char *format, ... );
void logmsg( const char *format, ... );
