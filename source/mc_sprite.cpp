// mc_spinner.cpp
///////////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "math.h"
#include "mc_sprite.hpp"



bool MCSprite::isTouching( const float testXCoord, const float testYCoord )
{
    float centerDistance = sqrt( pow(testXCoord - xPosition, 2) + pow(testYCoord - yPosition, 2) );
    
    if( centerDistance < size )
        return( true );
    else
        return( false );
}
