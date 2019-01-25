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


// TODO: MOVE SOMEWHERE ELSE AND RENAME
const float kFadeInStartPoint = 0.7; // 0.5



//////////////////////////////////////////////////////////////////////////////////////
MCGame::MCGame( MCApplication* newApp )
{
    app = newApp;
    inputHandler = new MCInput( this );
    audioController = new MCAudio( this );
}



//////////////////////////////////////////////////////////////////////////////////////
MCGame::~MCGame()
{
    delete audioController;
    delete inputHandler;
}



//////////////////////////////////////////////////////////////////////////////////////
void MCGame::start()
{
    mode = AppMode::MENU;
    menuFadeIn = 0.0;

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
    
    // DEBUG -- KEEP UNTIL AUDIO SYSTEM IS IMPLEMENTED 
    audioLoopPosition += 22000;
    
    // HANDLE FADE INS
    menuFadeIn = convergeValue( menuFadeIn, 1.0, 0.012 );
    runningFadeIn = convergeValue( runningFadeIn, 1.5, 0.006 );
    
    // IF STARTING MENU MODE...
    if( mode == AppMode::MENU  &&  previousMode != AppMode::MENU )
    {
        initMenuMode();
    }
    
    // MENU MODE FRAME UPDATE...
    if( mode == AppMode::MENU )
    {
        updateMenuModeFrame();
    }
    
    // IF STARTING RUNNING MODE...
    if( mode == AppMode::RUNNING  &&  previousMode != AppMode::RUNNING )
    {
        initRunningMode();
    }
    
    // RUNNING MODE FRAME UPDATE...
    if( mode == AppMode::RUNNING )
    {
        updateRunningModeFrame();
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
        if( frameCount % 60 == 0 )
        {
            printf( "FPS: %f\n",  frameCount * 1000.0 / ( getCurrentTimeMSec() - startTimeMSec )  );
            /*for( int i=0; i<MAX_ACTIVE_SPINNERS; i++ )
             {
             printf( "(%d:%d:s%.2f:t%d) ", i, spinnerArray[i].active, spinnerArray[i].size,  spinnerArray[i].texture );
             }//*/
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
    
    selectedPreset = ROMVisualPresetOrder[ presetIndex ];
    
    spinnerModeAdvanceRate = ROMSpinModeAdvRate[ selectedPreset ];
    
    spinnerSizeOffset = ROMSpinnerSizeOffset[ selectedPreset ];
    spinnerScaleX = ROMSpinnerScaleX[ selectedPreset ];
    spinnerScaleY = ROMSpinnerScaleY[ selectedPreset ];
    
    // set up correct textures based on menu selection
    const int* ROMPattern;
    switch( selectedPreset )
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
        spinnerArray[i].scaleFactor = ROMSpinnerSize[ selectedPreset * MAX_MAIN_SPINNERS + i ];
    }
    
    // then turn on a few spinners
    for( int i=0; i<4; i++ )
        spinnerArray[i].active = true;
    
    // reset the frame count so spinner sequence starts in the same place
    frameCount = 0;
    //*/
}


// DEBUG -- KEEP UNTIL RUNNING MODE IS FULLY WORKING TO MAKE SURE IT DOESN'T HAVE SOME DIFFERENCE FROM FRAMECOUNT
#define buttonJiggler frameCount



//////////////////////////////////////////////////////////////////////////////////////
void MCGame::initMenuMode()
{
    for( int i=0; i<MAX_ACTIVE_SPINNERS; i++ )
    {
        spinnerArray[i].active = false;
        spinnerArray[i].rotationRate = 0.0;
    }
}



//////////////////////////////////////////////////////////////////////////////////////
void MCGame::updateMenuModeFrame()
{
    backgroundColor = {0.2, 0.1, 0.1};
    
    // PAN WHEEL AND KEEP MENU WHEEL IN RANGE
    if( wheelPan == WheelPanMode::LEFT )
        menuWheelPosition -= 0.01;
    if( wheelPan == WheelPanMode::RIGHT )
        menuWheelPosition += 0.01; //*/
    if( menuWheelPosition>=NUMBER_OF_PRESETS )
        menuWheelPosition -= NUMBER_OF_PRESETS;
    if( menuWheelPosition<0.0 )
        menuWheelPosition += NUMBER_OF_PRESETS;
    
    spinnerArray[0].rotationRate = convergeValue( spinnerArray[0].rotationRate, 30.1, 0.15 );
    
    spinnerArray[0].active = true;
    spinnerArray[0].rotationPosition += spinnerArray[0].rotationRate;
    //spinnerArray[0].rotationPosition = frameCount * 30.1 * menuFadeIn;
    spinnerArray[0].texture = ROMPreviewTrack0[ ROMVisualPresetOrder[ (int)menuWheelPosition ] ];
    spinnerArray[0].size = 0.3;
    spinnerArray[0].yPosition = 0.4;
    spinnerArray[0].xPosition = menuWheelPosition - floor( menuWheelPosition);
    
    spinnerArray[1] = spinnerArray[0];
    spinnerArray[1].size = 0.22;
    spinnerArray[1].rotationPosition = 360 - spinnerArray[1].rotationPosition;
    spinnerArray[1].texture = ROMPreviewTrack1[ ROMVisualPresetOrder[ (int)menuWheelPosition ] ];
    
    normalButton.active = true;
    normalButton.texture = 300;
    normalButton.rotationPosition = frameCount * 25.1 * menuFadeIn;
    normalButton.size = 0.15;
    normalButton.yPosition = 0.65;
    normalButton.type = SpriteType::BUTTON;
    
    muteButton = normalButton;
    muteButton.texture = 301;
    muteButton.xPosition = 0.38;
    
    instrumentButton = normalButton;
    instrumentButton.texture = 302;
    instrumentButton.xPosition = 0.62;
    
    background.rotationPosition = sin(buttonJiggler*2.78)*1.6;
}



//////////////////////////////////////////////////////////////////////////////////////
void MCGame::initRunningMode()
{
    presetIndex = (int) menuWheelPosition;
    //manualTextureSelection = false; // <-- FROM ORIGINAL CODE -- IS THIS A DEBUG VARIABLE?
    runningFadeIn = 0.4;
    loadPreset( presetIndex );
    normalButton.active = false;
    muteButton.active = false;
    instrumentButton.active = false;
}



////////////////////////////////////////////////////////////////////////////////////////
void MCGame::updateSpinnerMode()
{
    //spinnerPhase = (frameCount%(spinnerModeAdvanceRate*2))/((spinnerModeAdvanceRate*2)/8);
    
    //---------------------------
    // CYCLE SPINNER MODES
    if( (frameCount%(spinnerModeAdvanceRate/4)==0) && (mode == AppMode::RUNNING) )
    {
        // THINGS TO DO HERE
        // - load different spinners every two complete cycles
        // - change audio samples every two or three complete cycles
        
        if( soundMode != SoundMode::INSTRUMENT )
        {
            switch( (frameCount%spinnerModeAdvanceRate)/(spinnerModeAdvanceRate/4) )
            {
                case 0: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) spinnerArray[i].active=false;
                    for(int i=0; i<2; i++ ) spinnerArray[i].active=true;  
                    //[looper creepJump]; // TODO: IMPLEMENT THIS 
                    break;
                case 1: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) spinnerArray[i].active=false;
                    for(int i=0; i<4; i++ ) spinnerArray[i].active=true;  
                    //[looper creepJump]; // TODO: IMPLEMENT THIS  
                    break;
                case 2: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) spinnerArray[i].active=false;
                    for(int i=2; i<6; i++ ) spinnerArray[i].active=true;  
                    spinnerArray[0].active=true;  
                    //[looper creepJump];  // TODO: IMPLEMENT THIS 
                    break;
                case 3: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) spinnerArray[i].active=false;
                    for(int i=4; i<8; i++ ) spinnerArray[i].active=true;  
                    spinnerArray[0].active=true;  
                    //[looper creepJump];  // TODO: IMPLEMENT THIS 
                    break;
            }
        }

        // TODO: THIS SECTION OF AUDIO CONTROL ADJUSTMENTS SHOULD PROBABLY BE DONE IN THE AUDIO CLASS
        /*looper.tremoloRate = ROMTromoloRate[soundPreset][(frameCount/(spinnerModeAdvanceRate/4))%8];
        
        if( appSoundMode != kAppSoundModeBinaural )
            looper.tremoloLevel = (ROMTromoloLevel[soundPreset][(frameCount/(spinnerModeAdvanceRate/4))%8]) * kMasterTremoloLevel;
        else 
            looper.tremoloLevel = 1.0; //*/
        
        
        if( manualTextureSelection == false )
        {
            // ALTERNATE SECONDARY SPINNER PATTERNS EVERY 8 CYCLES
            const int* ROMPattern;
            if( (frameCount%(spinnerModeAdvanceRate*4))/(spinnerModeAdvanceRate*2) == 0 )
            {
                switch( selectedPreset)
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
            }
            else 
            {
                switch( selectedPreset )
                {
                    case 0: ROMPattern = ROMPatternB1; break;
                    case 1: ROMPattern = ROMPatternB2; break;
                    case 2: ROMPattern = ROMPatternB3; break;
                    case 3: ROMPattern = ROMPatternB4; break;
                    case 4: ROMPattern = ROMPatternB5; break;
                    case 5: ROMPattern = ROMPatternB6; break;
                    case 6: ROMPattern = ROMPatternB7; break;
                    default: ROMPattern = ROMPatternB1;
                }
            }
            
            for( int spinner=0; spinner<=7; spinner++ )
                spinnerArray[spinner].texture = ROMPattern[spinner]; 
        }
        
        menuFadeIn = 0.4; 
        
        // TODO: IMPLEMENT THIS IS SOUND CLASS
        //if( (appSoundMode==kAppSoundModeInstrumentA) || (appSoundMode==kAppSoundModeiPod) )
        //    looper.voiceArrayPtr[frameCount%3].loopOffset = frameCount*(frameCount%3);
    }
    /* */
    
}




//////////////////////////////////////////////////////////////////////////////////////
void MCGame::updateRunningModeFrame()
{
    // DEBUG! - bloomCycleCounter SHOULD EITHER BE MOVED TO CLASS OR USE FRAMECOUNTER INSTEAD
    static long bloomCycleCounter =0;
    bloomCycleCounter++;

    creep += 0.016;

    if( runningFadeIn > kFadeInStartPoint )
        background.active = false;

    updateSpinnerMode();
    
    // SET BACKGROUND COLOR...
    if( (((frameCount+spinnerModeAdvanceRate/4)%(spinnerModeAdvanceRate*2))/(spinnerModeAdvanceRate) == 0) 
       || (mode == AppMode::MENU) )
    {
        backgroundColor = { ROMBGColorRedA[ selectedPreset ], ROMBGColorGreenA[ selectedPreset ], ROMBGColorBlueA[ selectedPreset ] };
    }
    else
    {
        backgroundColor = { ROMBGColorRedB[ selectedPreset ], ROMBGColorGreenB[ selectedPreset ], ROMBGColorBlueB[ selectedPreset ] };
    }
    
    // UPDATE ALL MAIN SPINNERS...
    for( int spinnerIndex=0; spinnerIndex< MAX_ACTIVE_SPINNERS ; spinnerIndex++ )
    {
        float rhythmBloom = 0.78+((1.7-abs(cos(bloomCycleCounter/700.0)+0.7))*0.43) // <- long cycle
                + sin(((int)audioLoopPosition%100000)/101000.0*3.141592654)*0.80 * cos(bloomCycleCounter/150.0); // <- short cycle
        
        float biggestSpinner = 0;
        for( int i=8; i>=spinnerIndex; i-- )
        {
            float spinnerSizeX = spinnerArray[i].scaleFactor * (runningFadeIn - kFadeInStartPoint) * menuFadeIn * rhythmBloom * 0.97;
            if( spinnerSizeX > biggestSpinner )
                biggestSpinner = spinnerSizeX;
        }

        spinnerArray[spinnerIndex].xPosition = convergeValue( spinnerArray[spinnerIndex].xPosition, 0.5, 0.002 );
        spinnerArray[spinnerIndex].yPosition = convergeValue( spinnerArray[spinnerIndex].yPosition, 0.5, 0.002 );
        
        if( (spinnerArray[spinnerIndex].active) )
        {
            
            //#define kSpinnerSplit (spinnerIndex*0.25-0.5)
#define kSpinnerSplit 0
            
            // Enforce minimum spinner speed -- looks better and avoids copyright issues
            if(abs(spinnerArray[spinnerIndex].rotationRate + creep) < 8)
                spinnerArray[spinnerIndex].rotationRate +=  1.7;
            if((long)abs(spinnerArray[spinnerIndex].rotationRate + creep)%180 > 171)
                spinnerArray[spinnerIndex].rotationRate +=  1.7;
            if((long)abs(spinnerArray[spinnerIndex].rotationRate + creep)%180 < 8)
                spinnerArray[spinnerIndex].rotationRate +=  1.7;
            
            // ROTATE SPINNER
            spinnerArray[spinnerIndex].rotationPosition += spinnerArray[spinnerIndex].rotationRate + creep;
            
            // DEBUG! -- THIS SHOULD BE MOVED TO CLASS OR DERIVED FROM FRAMECOUNT
            static int flipper=1;
            flipper *= -1;
            
            float spinnerSizeX, spinnerSizeY;
         
            // apply menuFadeIn to every spinner size except the first
            const float LARGE_SPINNER_SCALE_X = 0.5;  // ORIGINAL VALUE = 0.7
            const float LARGE_SPINNER_SCALE_Y = 0.6;  // ORIGINAL VALUE = 0.85
            const float LARGE_SPINNER_SIZE_OFFSET = 0.6;
            const float SPINNER_SCALE_X = 0.3;  // ORIGINAL VALUE = 0.7
            const float SPINNER_SCALE_Y = 0.4;  // ORIGINAL VALUE = 0.85
            const float SPINNER_SIZE_OFFSET = 0.1;
            if( spinnerIndex == 0 )
            {
                // FIRST SPINNER (the biggest spinner in the background)
                spinnerSizeX = spinnerArray[spinnerIndex].scaleFactor * 
                                    ( runningFadeIn - kFadeInStartPoint ) * rhythmBloom * 
                                    LARGE_SPINNER_SCALE_X * spinnerScaleX * pitchBend + spinnerSizeOffset + LARGE_SPINNER_SIZE_OFFSET;
                spinnerSizeY = spinnerArray[spinnerIndex].scaleFactor * 
                                    ( runningFadeIn - kFadeInStartPoint ) * LARGE_SPINNER_SCALE_Y * 
                                    spinnerScaleX * pitchBend + spinnerSizeOffset + LARGE_SPINNER_SIZE_OFFSET;
                const float kMinSpinnerSize = 0.8; 
                if( spinnerSizeX < kMinSpinnerSize )
                    spinnerSizeX = kMinSpinnerSize;
            }
            else 
            {    // ALL OTHER SPINNERS
                spinnerSizeX = spinnerArray[spinnerIndex].scaleFactor * 
                                    ( runningFadeIn - kFadeInStartPoint ) * menuFadeIn * rhythmBloom * 
                                    SPINNER_SCALE_X * spinnerScaleX * pitchBend + SPINNER_SIZE_OFFSET;
                spinnerSizeY = spinnerArray[spinnerIndex].scaleFactor * 
                                    ( runningFadeIn - kFadeInStartPoint ) * menuFadeIn * SPINNER_SCALE_Y * 
                                    spinnerScaleY * pitchBend + SPINNER_SIZE_OFFSET;
            } //*/
            
            // MAKE SPINNERS SMALLER IN INSTRUMENT MODE
            float spinnerScaling;
            /*if( appSoundMode==kAppSoundModeInstrumentA )
            {
                switch( spinnerIndex )
                {
                    case 0:
                        spinnerScaling = looper.voiceArrayPtr[0].envelope*10-9;
                        if( spinnerScaling <= 0.5 )
                            spinnerScaling = 0.5;
                        spinnerSizeX *= spinnerScaling;
                        spinnerSizeY *= spinnerScaling;
                        break;
                    default:
                        spinnerScaling = looper.voiceArrayPtr[0].envelope*10.7-9;
                        if( spinnerScaling <= 0.3 )
                            spinnerScaling = 0.3;
                        spinnerSizeX *= spinnerScaling;
                        spinnerSizeY *= spinnerScaling;
                        break;
                }
            }
            else //*/ 
                spinnerScaling = 1.0;
            
            const float kMaxSpinnerSize = 1.5; // ORIGINAL VALUE 2.5
            if( spinnerSizeX > kMaxSpinnerSize )
                spinnerSizeX = kMaxSpinnerSize;
            spinnerArray[spinnerIndex].size = spinnerSizeX; 
            
            ////glScalef( spinnerSizeX, spinnerSizeY, 0.0); // <-- OPENGL CODE INCLUDED FOR REFERENCE
            
            ////glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // <-- OPENGL CODE INCLUDED FOR REFERENCE
            //*/
         }  
        
    } // for all main spinnaz    
}















