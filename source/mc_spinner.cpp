// mc_spinner.cpp
///////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "math.h"
#include "mc_spinner.hpp"



bool MCSpinner::isTouching( float testXCoord, float testYCoord )
{
    float centerDistance = sqrt( pow(testXCoord - xPosition, 2) + pow(testYCoord - yPosition, 2) );
    printf( "TOUCH DISTANCE: %f \n", centerDistance );
    
    if( centerDistance < size )
        return( true );
    else
        return( false );
}
