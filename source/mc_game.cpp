// mc_game.cpp
////////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include <math.h>
#include "mc_game.hpp"
#include "mc_application.hpp"
#include "mc_sequence_data.hpp"
#include "mc_util.hpp"
#include "mc_input.hpp"
#include "mc_audio.hpp"
#include "mc_menu_screen.hpp"
#include "mc_game_screen.hpp"




//////////////////////////////////////////////////////////////////////////////////////
MCGame::MCGame( MCApplication* newApp )
{
    app = newApp;
    inputHandler = new MCInput( this );
    audioController = new MCAudio( this );
    menuScreen = new MCMenuScreen( this );
    gameScreen = new MCGameScreen( this );
}



//////////////////////////////////////////////////////////////////////////////////////
MCGame::~MCGame()
{
    delete menuScreen;
    delete gameScreen;
    delete audioController;
    delete inputHandler;
}


//////////////////////////////////////////////////////////////////////////////////////
void MCGame::start()
{
    mode = AppMode::MENU;
    menuFadeIn = 0.0;
    
    menuWheelPosition = rand() % NUMBER_OF_PRESETS + 0.5;
    
    timeOfLastInputMSec = getCurrentTimeMSec();

    background.active = true;
    background.type = SpriteType::BACKGROUND;
    
    // RANDOMLY CHOOSE BETWEEN THE TWO BACKGROUND TEXTURES...
    if( rand()%2 == 0 )
        background.texture = 200;
    else
        background.texture = 201;

    audioController->start();
}



//////////////////////////////////////////////////////////////////////////////////////
void MCGame::stop()
{
    //audioController->stop(); // TBI?
    mode = AppMode::STOPPED;
}



/////////////////////////////////////////////////////////////////////////////////////
void MCGame::processEvent( SDL_Event event )
{
    switch( event.type )
    {
        case SDL_FINGERDOWN: 
        case SDL_FINGERUP:
        case SDL_FINGERMOTION:
            inputHandler->processTouchEvent( event.tfinger );
            break;
            
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            inputHandler->processKeyboardEvent( event.key );
            break;
    }
}



//////////////////////////////////////////////////////////////////////////////////////
void MCGame::updateFrame()
{
    frameCount++;
    totalFrameCount++;
    
    // DEBUG -- KEEP UNTIL AUDIO SYSTEM IS IMPLEMENTED 
    audioLoopPosition += 22000;
    
    // HANDLE FADE INS
    menuFadeIn = convergeValue( menuFadeIn, 1.0, 0.012 );
    runningFadeIn = convergeValue( runningFadeIn, 1.5, 0.006 );
    
    audioController->updateFrame();
    
    // IF STARTING MENU MODE...
    if( mode == AppMode::MENU  &&  previousMode != AppMode::MENU )
    {
        menuScreen->init();
    }
    
    // MENU MODE FRAME UPDATE...
    if( mode == AppMode::MENU )
    {
        menuScreen->updateFrame();
    }
    
    // IF STARTING RUNNING MODE...
    if( mode == AppMode::RUNNING  &&  previousMode != AppMode::RUNNING )
    {
        gameScreen->init();
    }
    
    // RUNNING MODE FRAME UPDATE...
    if( mode == AppMode::RUNNING )
    {
        gameScreen->updateFrame();
    }
    
    previousMode = mode;

    // SET APPLICATION BACKGROUND COLOR AND ADD ALL SPRITES TO SPRITE RENDER LIST
    app->backgroundColor = backgroundColor;
    app->spriteRenderList.clear();
    app->spriteRenderList[0] = background;
    app->spriteRenderList[1] = normalButton;
    app->spriteRenderList[2] = muteButton;
    app->spriteRenderList[3] = instrumentButton;
    for( int spinnerNumber=0; spinnerNumber<MAX_ACTIVE_SPINNERS; spinnerNumber++ )
        app->spriteRenderList[ spinnerNumber+4 ] = spinnerArray[ spinnerNumber ];
    
    // DEBUG!!!  SHOW FPS AND OTHER DEBUG INFO...
    if( startTimeMSec == 0 )
        startTimeMSec = getCurrentTimeMSec();
    else
    {
        if( totalFrameCount % 60 == 0 )
        {
            printf( "FPS: %f\n",  totalFrameCount * 1000.0 / ( getCurrentTimeMSec() - startTimeMSec )  );
            printf( "\n" );
        }
    }

}






///////////////////////////////////////////////////////////////////////////////////////
void MCGame::loadPreset( const int presetNumber )
{
    printf( "LOAD PRESET ---- %d \n", presetNumber );
    
    //===============================================================
    // VISUAL SETTINGS
    
    //visualPreset = ROMVisualPresetOrder[ presetNumber ];
    
    spinnerModeAdvanceRate = ROMSpinModeAdvRate[ visualPreset ];
    
    spinnerSizeOffset = ROMSpinnerSizeOffset[ visualPreset ];
    spinnerScaleX = ROMSpinnerScaleX[ visualPreset ];
    spinnerScaleY = ROMSpinnerScaleY[ visualPreset ];
    
    // set up correct textures based on menu selection
    const int* ROMPattern;
    switch( visualPreset )
    {
        case 0: ROMPattern = ROMPatternA1; break;
        case 1: ROMPattern = ROMPatternA2; break;
        case 2: ROMPattern = ROMPatternA3; break;
        case 3: ROMPattern = ROMPatternA4; break;
        case 4: ROMPattern = ROMPatternA5; break;
        case 5: ROMPattern = ROMPatternA6; break;
        case 6: ROMPattern = ROMPatternA7; break;
        default: ROMPattern = ROMPatternA1;
    }
    for( int spinner=0; spinner<=7; spinner++ )
        spinnerArray[spinner].texture = ROMPattern[spinner];
    
    // turn off all spinners and set rotation rates
    for( int i=0; i<MAX_MAIN_SPINNERS; i++ )
    {
        spinnerArray[i].rotationRate = 45.0+i*5;
        spinnerArray[i].active = false;
        spinnerArray[i].scaleFactor = ROMSpinnerSize[ visualPreset * MAX_MAIN_SPINNERS + i ];
    }
    
    // then turn on a few spinners
    for( int i=0; i<4; i++ )
        spinnerArray[i].active = true;
    
    // reset the frame count so spinner sequence starts in the same place
    frameCount = 0;
    //*/
}











