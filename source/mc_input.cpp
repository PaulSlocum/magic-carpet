// mc_input.cpp
////////////////////////////////////////////////////////////////////

#include "SDL.h"

#include "mc_input.hpp"
#include "mc_application.hpp"



//////////////////////////////////////////////////////////////////////////////////////
MCInput::MCInput( MCAppState* newState )
{
    state = newState;
}



//////////////////////////////////////////////////////////////////////////////////////
MCInput::~MCInput()
{
}



/////////////////////////////////////////////////////////////////////////////////////
void MCInput::processTouchEvent( const SDL_TouchFingerEvent fingerEvent )
{
    if( fingerEvent.type == SDL_FINGERMOTION )
    {
        state->menuWheelPosition += fingerEvent.dx;
    }
}


/////////////////////////////////////////////////////////////////////////////////////
void MCInput::processKeyboardEvent( const SDL_KeyboardEvent keyEvent )
{
    if( keyEvent.type == SDL_KEYDOWN )
        keyState.insert( keyEvent.keysym.scancode );
    if( keyEvent.type == SDL_KEYUP )
        keyState.erase( keyEvent.keysym.scancode );
    
    if( keyState.count( SDL_SCANCODE_LEFT ) )
        state->menuWheelPosition -= 0.08;
    if( keyState.count( SDL_SCANCODE_RIGHT ) )
        state->menuWheelPosition -= 0.08;
}
