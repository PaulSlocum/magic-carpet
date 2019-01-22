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
    // MOVE THE MENU WHEEL WITH FINGER DRAGS...
    if( fingerEvent.type == SDL_FINGERMOTION )
    {
        state->menuWheelPosition += fingerEvent.dx;
    }

    // START RUNNING IF TOUCHING MAIN SPINNER IN MENU...
    if( state->mode == AppMode::MENU  &&  state->spinnerArray[0].isTouching( fingerEvent.x, fingerEvent.y ) == true )
    {
        state->mode = AppMode::RUNNING;
    }
}


/////////////////////////////////////////////////////////////////////////////////////
void MCInput::processKeyboardEvent( const SDL_KeyboardEvent keyEvent )
{
    // KEY TRACKING...
    if( keyEvent.type == SDL_KEYDOWN )
        keysDown.insert( keyEvent.keysym.scancode );
    if( keyEvent.type == SDL_KEYUP )
        keysDown.erase( keyEvent.keysym.scancode );
    
    // ENTER/ESC TO START/EXIT FROM MENU...
    if( keyEvent.keysym.scancode == SDL_SCANCODE_RETURN  &&  state->mode == AppMode::MENU )
        state->mode = AppMode::RUNNING;
    if( keyEvent.keysym.scancode == SDL_SCANCODE_ESCAPE  &&  state->mode == AppMode::RUNNING )
        state->mode = AppMode::MENU;

    // MOVE THE MENU WHEEL WITH LEFT/RIGHT CURSOR KEYS...
    if( keysDown.count( SDL_SCANCODE_LEFT ) )
        state->wheelPan = WheelPanMode::LEFT;
    else
    {
        if( keysDown.count( SDL_SCANCODE_RIGHT ) )
            state->wheelPan = WheelPanMode::RIGHT;
        else
            state->wheelPan = WheelPanMode::STOPPED;
    }//*/
}
