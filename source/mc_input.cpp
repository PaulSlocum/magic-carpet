// mc_input.cpp
////////////////////////////////////////////////////////////////////

#include "SDL.h"

#include "mc_input.hpp"
#include "mc_application.hpp"
#include "mc_touch.hpp"
#include "mc_game.hpp"



//////////////////////////////////////////////////////////////////////////////////////
MCInput::MCInput( MCGame* newGame )
{
    game = newGame;
}



//////////////////////////////////////////////////////////////////////////////////////
MCInput::~MCInput()
{
}



/////////////////////////////////////////////////////////////////////////////////////
void MCInput::processTouchEvent( const SDL_TouchFingerEvent fingerEvent )
{
    if( fingerEvent.type == SDL_FINGERDOWN )
    {
        game->touchArray[ (int)fingerEvent.touchId ].x = fingerEvent.x;
        game->touchArray[ (int)fingerEvent.touchId ].y = fingerEvent.y;
        game->touchArray[ (int)fingerEvent.touchId ].xStart = fingerEvent.x;
        game->touchArray[ (int)fingerEvent.touchId ].yStart = fingerEvent.y;
    }

    // MOVE THE MENU WHEEL WITH FINGER DRAGS...
    if( fingerEvent.type == SDL_FINGERMOTION )
    {
        if( game->mode == AppMode::MENU )
            game->menuWheelPosition += fingerEvent.dx;
        
        game->touchArray[ (int)fingerEvent.touchId ].x = fingerEvent.x;
        game->touchArray[ (int)fingerEvent.touchId ].y = fingerEvent.y;
        game->touchArray[ (int)fingerEvent.touchId ].totalMoveDistance += sqrt( pow( fingerEvent.dx, 2 ) + pow( fingerEvent.dy, 2 ) );
    }

    if( fingerEvent.type == SDL_FINGERUP )
    {
        if( game->mode == AppMode::MENU  &&  
           game->touchArray[ (int)fingerEvent.touchId ].totalMoveDistance < 0.01  &&  game->spinnerArray[0].isTouching( fingerEvent.x, fingerEvent.y ) == true )  
            game->mode = AppMode::RUNNING;
        game->touchArray.erase( (int)fingerEvent.touchId );
    }
}




/////////////////////////////////////////////////////////////////////////////////////
void MCInput::processKeyboardEvent( const SDL_KeyboardEvent keyEvent )
{
    if( keyEvent.repeat == false )
    {
        // KEY TRACKING...
        if( keyEvent.type == SDL_KEYDOWN )
            keysDown.insert( keyEvent.keysym.scancode );
        if( keyEvent.type == SDL_KEYUP )
            keysDown.erase( keyEvent.keysym.scancode );
        
        // ENTER/ESC TO START/EXIT FROM MENU...
        if( keyEvent.keysym.scancode == SDL_SCANCODE_RETURN  &&  game->mode == AppMode::MENU )
            game->mode = AppMode::RUNNING;
        if( keyEvent.keysym.scancode == SDL_SCANCODE_ESCAPE  &&  game->mode == AppMode::RUNNING )
            game->mode = AppMode::MENU;

        // MOVE THE MENU WHEEL WITH LEFT/RIGHT CURSOR KEYS...
        if( keysDown.count( SDL_SCANCODE_LEFT ) )
            game->wheelPan = WheelPanMode::LEFT;
        else
        {
            if( keysDown.count( SDL_SCANCODE_RIGHT ) )
                game->wheelPan = WheelPanMode::RIGHT;
            else
                game->wheelPan = WheelPanMode::STOPPED;
        }//*/
    }
}
