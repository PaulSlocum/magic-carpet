// mc_menu_screen.cpp
////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "mc_menu_screen.hpp"
#include "mc_game.hpp"
#include "mc_util.hpp"
#include "mc_sequence_data.hpp"



//////////////////////////////////////////////////////////////////////////////////////
MCMenuScreen::MCMenuScreen( MCGame* newGame )
{
    game = newGame;
}



//////////////////////////////////////////////////////////////////////////////////////
MCMenuScreen::~MCMenuScreen()
{
}



//////////////////////////////////////////////////////////////////////////////////////
void MCMenuScreen::init()
{
    for( int i=0; i<MAX_ACTIVE_SPINNERS; i++ )
    {
        game->spinnerArray[i].active = false;
        game->spinnerArray[i].rotationRate = 0.0;
    }
}



//////////////////////////////////////////////////////////////////////////////////////
void MCMenuScreen::updateFrame()
{
    const long long MENU_TIMEOUT_MSEC = 17000;
    if( getCurrentTimeMSec() - game->timeOfLastInputMSec > MENU_TIMEOUT_MSEC )
        game->mode = AppMode::RUNNING;
    
    int rawPresetNumber = (int)game->menuWheelPosition % NUMBER_OF_PRESETS;
    game->visualPreset = ROMVisualPresetOrder[ rawPresetNumber ];
    game->audioPreset = ROMSoundPresetOrder[ rawPresetNumber ];
    
    game->backgroundColor = {0.2, 0.1, 0.1};
    
    // PAN WHEEL AND KEEP MENU WHEEL IN RANGE
    if( game->wheelPan == WheelPanMode::LEFT )
        game->menuWheelPosition -= 0.01;
    if( game->wheelPan == WheelPanMode::RIGHT )
        game->menuWheelPosition += 0.01; //*/
    if( game->menuWheelPosition>=NUMBER_OF_PRESETS )
        game->menuWheelPosition -= NUMBER_OF_PRESETS;
    if( game->menuWheelPosition<0.0 )
        game->menuWheelPosition += NUMBER_OF_PRESETS;
    
    game->spinnerArray[0].rotationRate = convergeValue( game->spinnerArray[0].rotationRate, 30.1, 0.15 );
    
    game->spinnerArray[0].active = true;
    game->spinnerArray[0].rotationPosition += game->spinnerArray[0].rotationRate;
    game->spinnerArray[0].texture = ROMPreviewTrack0[ ROMVisualPresetOrder[ game->visualPreset ] ];
    game->spinnerArray[0].size = 0.3 * game->menuFadeIn;
    game->spinnerArray[0].yPosition = 0.4;
    game->spinnerArray[0].xPosition = game->menuWheelPosition - floor( game->menuWheelPosition);
    
    game->spinnerArray[1] = game->spinnerArray[0];
    game->spinnerArray[1].size = 0.22 * game->menuFadeIn;
    game->spinnerArray[1].rotationPosition = 360 - game->spinnerArray[1].rotationPosition;
    game->spinnerArray[1].texture = ROMPreviewTrack1[ ROMVisualPresetOrder[game->visualPreset ] ];
    
    game->normalButton.active = true;
    game->normalButton.texture = 300;
    game->normalButton.rotationPosition = game->frameCount * 25.1 * game->menuFadeIn;
    game->normalButton.size = 0.15 * game->menuFadeIn;
    game->normalButton.yPosition = 0.65;
    game->normalButton.type = SpriteType::BUTTON;
    
    game->muteButton = game->normalButton;
    game->muteButton.texture = 301;
    game->muteButton.xPosition = 0.38;
    
    game->instrumentButton = game->normalButton;
    game->instrumentButton.texture = 302;
    game->instrumentButton.xPosition = 0.62;
    
    game->background.rotationPosition = sin( game->totalFrameCount*2.78 )*1.6;
    game->background.size = game->menuFadeIn;
}



