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
        keysDown.insert( keyEvent.keysym.scancode );
    if( keyEvent.type == SDL_KEYUP )
        keysDown.erase( keyEvent.keysym.scancode );

    if( keysDown.count( SDL_SCANCODE_LEFT ) )
        state->wheelPan = WheelPanMode::LEFT;
    else
    {
        if( keysDown.count( SDL_SCANCODE_RIGHT ) )
            state->wheelPan = WheelPanMode::RIGHT;
        else
            state->wheelPan = WheelPanMode::STOPPED;
    }
}
