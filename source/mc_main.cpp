////////////////////////////////////////////////////////////////////////////////////////
// mc_main.cpp
////////////////////////////////////////////////////////////////////////////////////////


#include "mc_application.hpp"
#include "SDL.h"




//=======================================================================
int main( int argc __attribute__ ((unused)), char *argv[] __attribute__ ((unused)) )
{
    printf( "----------------------- \nM A G I C   C A R P E T \n----------------------- \n" );
    
    MCApplication magicCarpetApp;
    magicCarpetApp.start();

    return 0;
}

