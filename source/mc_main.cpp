////////////////////////////////////////////////////////////////////////////////////////
// mc_main.cpp
////////////////////////////////////////////////////////////////////////////////////////


#include "mc_application.hpp"
#include "SDL.h"




//=======================================================================
int main(int argc, char *argv[])
{
    printf( "-----------------------\n" );
    printf( "M A G I C   C A R P E T \n" );
    printf( "-----------------------\n" );
    
    MCApplication magicCarpetApp;
    magicCarpetApp.start();

    return 0;
}
