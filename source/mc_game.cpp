// mc_game.cpp
////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "mc_game.hpp"
#include "mc_application.hpp"
#include "mc_sequence_data.hpp"
#include "mc_util.hpp"


// TODO: MOVE SOMEWHERE
const float kFadeInStartPoint = 0.7; // 0.5



//////////////////////////////////////////////////////////////////////////////////////
MCGame::MCGame( MCAppState* newState )
{
    state = newState;
}



//////////////////////////////////////////////////////////////////////////////////////
MCGame::~MCGame()
{
}



//////////////////////////////////////////////////////////////////////////////////////
void MCGame::init()
{
    state->background.active = true;
    state->background.type = SpinnerType::BACKGROUND;
}






//////////////////////////////////////////////////////////////////////////////////////
void MCGame::updateFrame()
{
    frameCount++;
    
    // DEBUG -- KEEP UNTIL AUDIO SYSTEM IS IMPLEMENTED 
    state->audioLoopPosition += 22000;
    
    // HANDLE FADE INS
    state->menuFadeIn = convergeValue( state->menuFadeIn, 1.0, 0.012 );
    state->runningFadeIn = convergeValue( state->runningFadeIn, 1.5, 0.006 );
    
    // IF STARTING MENU MODE...
    if( state->mode == AppMode::MENU  &&  state->previousMode != AppMode::MENU )
    {
        initMenuMode();
    }
    
    // MENU MODE FRAME UPDATE...
    if( state->mode == AppMode::MENU )
    {
        updateMenuModeFrame();
    }
    
    // IF STARTING RUNNING MODE...
    if( state->mode == AppMode::RUNNING  &&  state->previousMode != AppMode::RUNNING )
    {
        initRunningMode();
    }
    
    // RUNNING MODE FRAME UPDATE...
    if( state->mode == AppMode::RUNNING )
    {
        updateRunningModeFrame();
    }
    
    state->previousMode = state->mode;
}






///////////////////////////////////////////////////////////////////////////////////////
void MCGame::loadPreset( const int presetNumber )
{
    printf( "LOAD PRESET ---- %d \n", presetNumber );
    
    //===============================================================
    // VISUAL SETTINGS
    
    state->selectedPreset = ROMVisualPresetOrder[ state->presetIndex ];
    
    state->spinnerModeAdvanceRate = ROMSpinModeAdvRate[ state->selectedPreset ];
    
    state->spinnerSizeOffset = ROMSpinnerSizeOffset[ state->selectedPreset ];
    state->spinnerScaleX = ROMSpinnerScaleX[ state->selectedPreset ];
    state->spinnerScaleY = ROMSpinnerScaleY[ state->selectedPreset ];
    
    // set up correct textures based on menu selection
    const int* ROMPattern;
    switch( state->selectedPreset )
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
        state->spinnerArray[spinner].texture = ROMPattern[spinner];
    
    // turn off all spinners and set rotation rates
    for( int i=0; i<MAX_MAIN_SPINNERS; i++ )
    {
        state->spinnerArray[i].rotationRate = 45.0+i*5;
        state->spinnerArray[i].active = false;
        state->spinnerArray[i].scaleFactor = ROMSpinnerSize[ state->selectedPreset * MAX_MAIN_SPINNERS + i ];
    }
    
    // then turn on a few spinners
    for( int i=0; i<4; i++ )
        state->spinnerArray[i].active = true;
    
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
        state->spinnerArray[i].active = false;
}



//////////////////////////////////////////////////////////////////////////////////////
void MCGame::updateMenuModeFrame()
{
    // PAN WHEEL AND KEEP MENU WHEEL IN RANGE
    if( state->wheelPan == WheelPanMode::LEFT )
        state->menuWheelPosition -= 0.01;
    if( state->wheelPan == WheelPanMode::RIGHT )
        state->menuWheelPosition += 0.01; //*/
    if( state->menuWheelPosition>=NUMBER_OF_PRESETS )
        state->menuWheelPosition -= NUMBER_OF_PRESETS;
    if( state->menuWheelPosition<0.0 )
        state->menuWheelPosition += NUMBER_OF_PRESETS;
    
    state->spinnerArray[0].active = true;
    state->spinnerArray[0].rotationPosition = frameCount * 30.1;
    state->spinnerArray[0].texture = ROMPreviewTrack0[ ROMVisualPresetOrder[ (int)state->menuWheelPosition ] ];
    state->spinnerArray[0].size = 0.3;
    state->spinnerArray[0].yPosition = 0.4;
    state->spinnerArray[0].xPosition = state->menuWheelPosition - floor( state->menuWheelPosition);
    
    state->spinnerArray[1] = state->spinnerArray[0];
    state->spinnerArray[1].size = 0.19;
    state->spinnerArray[1].texture = ROMPreviewTrack1[ ROMVisualPresetOrder[ (int)state->menuWheelPosition ] ];
    
    state->normalButton.active = true;
    state->normalButton.texture = 0;
    state->normalButton.rotationPosition = frameCount * 25.1;
    state->normalButton.size = 0.15;
    state->normalButton.yPosition = 0.65;
    state->normalButton.type = SpinnerType::BUTTON;
    
    state->muteButton = state->normalButton;
    state->muteButton.texture = 1;
    state->muteButton.xPosition = 0.38;
    
    state->instrumentButton = state->normalButton;
    state->instrumentButton.texture = 2;
    state->instrumentButton.xPosition = 0.62;
    
    state->background.rotationPosition = sin(buttonJiggler*2.78)*1.6;
}



//////////////////////////////////////////////////////////////////////////////////////
void MCGame::initRunningMode()
{
    state->presetIndex = (int) state->menuWheelPosition;
    //manualTextureSelection = false; // <-- FROM ORIGINAL CODE -- IS THIS A DEBUG VARIABLE?
    state->runningFadeIn = 0.4;
    loadPreset( state->presetIndex );
    state->normalButton.active = false;
    state->muteButton.active = false;
    state->instrumentButton.active = false;
}



////////////////////////////////////////////////////////////////////////////////////////
void MCGame::updateSpinnerMode()
{
    //state->spinnerPhase = (frameCount%(state->spinnerModeAdvanceRate*2))/((state->spinnerModeAdvanceRate*2)/8);
    
    //---------------------------
    // CYCLE SPINNER MODES
    if( (frameCount%(state->spinnerModeAdvanceRate/4)==0) && (state->mode == AppMode::RUNNING) )
    {
        // THINGS TO DO HERE
        // - load different spinners every two complete cycles
        // - change audio samples every two or three complete cycles
        
        if( state->soundMode != SoundMode::INSTRUMENT )
        {
            switch( (frameCount%state->spinnerModeAdvanceRate)/(state->spinnerModeAdvanceRate/4) )
            {
                case 0: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) state->spinnerArray[i].active=false;
                    for(int i=0; i<2; i++ ) state->spinnerArray[i].active=true;  
                    //[looper creepJump]; // TODO: IMPLEMENT THIS 
                    break;
                case 1: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) state->spinnerArray[i].active=false;
                    for(int i=0; i<4; i++ ) state->spinnerArray[i].active=true;  
                    //[looper creepJump]; // TODO: IMPLEMENT THIS  
                    break;
                case 2: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) state->spinnerArray[i].active=false;
                    for(int i=2; i<6; i++ ) state->spinnerArray[i].active=true;  
                    state->spinnerArray[0].active=true;  
                    //[looper creepJump];  // TODO: IMPLEMENT THIS 
                    break;
                case 3: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) state->spinnerArray[i].active=false;
                    for(int i=4; i<8; i++ ) state->spinnerArray[i].active=true;  
                    state->spinnerArray[0].active=true;  
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
        
        
        if( state->manualTextureSelection == false )
        {
            // ALTERNATE SECONDARY SPINNER PATTERNS EVERY 8 CYCLES
            const int* ROMPattern;
            if( (frameCount%(state->spinnerModeAdvanceRate*4))/(state->spinnerModeAdvanceRate*2) == 0 )
            {
                switch( state->selectedPreset)
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
                switch( state->selectedPreset )
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
                state->spinnerArray[spinner].texture = ROMPattern[spinner]; 
        }
        
        state->menuFadeIn = 0.4; 
        
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

    state->creep += 0.016;

    if( state->runningFadeIn > kFadeInStartPoint )
        state->background.active = false;

    updateSpinnerMode();
    
    // SET BACKGROUND COLOR...
    if( (((frameCount+state->spinnerModeAdvanceRate/4)%(state->spinnerModeAdvanceRate*2))/(state->spinnerModeAdvanceRate) == 0) 
       || (state->mode == AppMode::MENU) )
    {
        state->backgroundColor.red = ROMBGColorRedA[ state->selectedPreset ];
        state->backgroundColor.green = ROMBGColorBlueA[ state->selectedPreset ];
        state->backgroundColor.blue = ROMBGColorGreenA[ state->selectedPreset ];
    }
    else
    {
        state->backgroundColor.red = ROMBGColorRedB[ state->selectedPreset ];
        state->backgroundColor.green = ROMBGColorGreenB[ state->selectedPreset ];
        state->backgroundColor.blue = ROMBGColorBlueB[ state->selectedPreset ];
    }
    
    ////if( (((frameCount+spinnerModeAdvanceRate/4)%(spinnerModeAdvanceRate*2))/(spinnerModeAdvanceRate) == 0) || (appMode == kAppModeMenu) )
        ////glClearColor(ROMBGColorRedA[originalPresetIndex], ROMBGColorGreenA[originalPresetIndex], ROMBGColorBlueA[originalPresetIndex], 1.0f );
    ////else
        ////glClearColor(ROMBGColorRedB[originalPresetIndex], ROMBGColorGreenB[originalPresetIndex], ROMBGColorBlueB[originalPresetIndex], 1.0f );

    
    // UPDATE ALL MAIN SPINNERS...
    for( int spinnerIndex=0; spinnerIndex< MAX_ACTIVE_SPINNERS ; spinnerIndex++ )
    {
        float rhythmBloom = 0.78+((1.7-abs(cos(bloomCycleCounter/700.0)+0.7))*0.43) // <- long cycle
                + sin(((int)state->audioLoopPosition%100000)/101000.0*3.141592654)*0.80 * cos(bloomCycleCounter/150.0); // <- short cycle
        
        float biggestSpinner = 0;
        for( int i=8; i>=spinnerIndex; i-- )
        {
            float spinnerSizeX = state->spinnerArray[i].scaleFactor * (state->runningFadeIn - kFadeInStartPoint) * state->menuFadeIn * rhythmBloom * 0.97;
            if( spinnerSizeX > biggestSpinner )
                biggestSpinner = spinnerSizeX;
        }

        state->spinnerArray[spinnerIndex].xPosition = convergeValue( state->spinnerArray[spinnerIndex].xPosition, 0.5, 0.002 );
        state->spinnerArray[spinnerIndex].yPosition = convergeValue( state->spinnerArray[spinnerIndex].yPosition, 0.5, 0.002 );
        
        if( (state->spinnerArray[spinnerIndex].active) )
        {
            
            //#define kSpinnerSplit (spinnerIndex*0.25-0.5)
#define kSpinnerSplit 0
            
            // Enforce minimum spinner speed -- looks better and avoids copyright issues
            if(abs(state->spinnerArray[spinnerIndex].rotationRate + state->creep) < 8)
                state->spinnerArray[spinnerIndex].rotationRate +=  1.7;
            if((long)abs(state->spinnerArray[spinnerIndex].rotationRate + state->creep)%180 > 171)
                state->spinnerArray[spinnerIndex].rotationRate +=  1.7;
            if((long)abs(state->spinnerArray[spinnerIndex].rotationRate + state->creep)%180 < 8)
                state->spinnerArray[spinnerIndex].rotationRate +=  1.7;
            
            // ROTATE SPINNER
            state->spinnerArray[spinnerIndex].rotationPosition += state->spinnerArray[spinnerIndex].rotationRate + state->creep;
            ////glBindTexture(GL_TEXTURE_2D,spinnerTextureArray[ state->spinnerArray[spinnerIndex].texture ]); // <-- OPENGL CODE INCLUDED FOR REFERENCE
            ////glLoadIdentity(); // <-- OPENGL CODE INCLUDED FOR REFERENCE
            
            // DEBUG! -- THIS SHOULD BE MOVED TO CLASS OR DERIVED FROM FRAMECOUNT
            static int flipper=1;
            flipper *= -1;
            
            const float kMaxSpinnerSize = 2.5;
            float spinnerSizeX, spinnerSizeY;
         
            // apply menuFadeIn to every spinner size except the first
            const float LARGE_SPINNER_SCALE_X = 0.9;  // ORIGINAL VALUE = 0.7
            const float LARGE_SPINNER_SCALE_Y = 1.0;  // ORIGINAL VALUE = 0.85
            if( spinnerIndex == 0 )
            {
                // FIRST SPINNER (the biggest spinner in the background)
                spinnerSizeX = state->spinnerArray[spinnerIndex].scaleFactor * 
                                    ( state->runningFadeIn - kFadeInStartPoint ) * rhythmBloom * 
                                    LARGE_SPINNER_SCALE_X * state->spinnerScaleX * state->pitchBend + state->spinnerSizeOffset;
                spinnerSizeY = state->spinnerArray[spinnerIndex].scaleFactor * 
                                    ( state->runningFadeIn - kFadeInStartPoint ) * LARGE_SPINNER_SCALE_Y * 
                                    state->spinnerScaleX * state->pitchBend + state->spinnerSizeOffset;
            }
            else 
            {    // ALL OTHER SPINNERS
                spinnerSizeX = state->spinnerArray[spinnerIndex].scaleFactor * 
                                    ( state->runningFadeIn - kFadeInStartPoint ) * state->menuFadeIn * rhythmBloom * 0.7 * state->spinnerScaleX * state->pitchBend;
                spinnerSizeY = state->spinnerArray[spinnerIndex].scaleFactor * 
                                    ( state->runningFadeIn - kFadeInStartPoint ) * state->menuFadeIn * 0.85 * state->spinnerScaleY * state->pitchBend;
            } //*/
            
            // MAKE SPINNERS SMALLER IN INSTRUMENT MODE
            float spinnerScaling;
            /*if( state->appSoundMode==kAppSoundModeInstrumentA )
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
            
            // I THINK THIS CODE IS PRIMARILY TO SLIDE THE SPINNERS TO THE CENTER AS A TRANSITION FROM THE MENU...
            // ...THIS SHOULD PROBABLY BE IMPLEMENTED DIFFERENTLY...
            // ... OPENGL CODE INCLUDED FOR REFERENCE
            ////if( !showMenuSideways )
                ////glTranslatef( (-0.7+(runningFadeIn-0.5)*0.7),
                    ////         (prayerWheelPosition*2-(int)prayerWheelPosition*2-1)*(1.5-runningFadeIn)+0.2*spinPolarity*(doubleSpin*2-1)
                        ////     +kSpinnerSplit, 0.0f);    
            ////else 
                ////glTranslatef( (-0.7+(1.5-0.5)*0.7),
                    ////         (1.5-runningFadeIn)*0.7+0.2*spinPolarity*(doubleSpin*2-1)
                        ////     +kSpinnerSplit, 0.0f); //*/
            
            ////glRotatef(mainSpinnerArray[spinnerIndex].rotationPosition, 0.0f, 0.0f, 1.0f);   // <-- OPENGL CODE INCLUDED FOR REFERENCE

            if( spinnerSizeX > kMaxSpinnerSize )
                spinnerSizeX = kMaxSpinnerSize;
            state->spinnerArray[spinnerIndex].size = spinnerSizeX; 
            
            ////glScalef( spinnerSizeX, spinnerSizeY, 0.0); // <-- OPENGL CODE INCLUDED FOR REFERENCE
            
            ////glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // <-- OPENGL CODE INCLUDED FOR REFERENCE
            //*/
         }  
        
    } // for all main spinnaz    
}















