// mc_spinner.cpp
///////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "math.h"
#include "mc_spinner.hpp"

// EXAMPLE 1
// 0.25 x 
// 0.75 y
// 0.25 size

// EXAMPLE 2
// 0.0 x 
// 0.0 y
// 0.25 size

// TEST 0.0, 0.0  ->  No   No   
// TEST 1.0, 1.0      No   No
// TEST 0.0, 1.0      Yes  No
// TEST 1.0, 0.0      No   No
// TEST 0.5, 0.5      Yes  Yes



bool MCSpinner::isTouching( float testXCoord, float testYCoord )
{
    float centerDistance = sqrt( pow(testXCoord - xPosition, 2) + pow(testYCoord - yPosition, 2) );
    printf( "TOUCH DISTANCE: %f \n", centerDistance );
    
    if( centerDistance < size )
        return( true );
    else
        return( false );
}
