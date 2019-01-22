// mc_game.cpp
////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "mc_game.hpp"
#include "mc_application.hpp"
#include "mc_sequence_data.hpp"


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


///////////////////////////////////////////////////////////////////////////////////////
void MCGame::loadPreset( const int presetNumber )
{
    printf( "LOAD PRESET ---- %d \n", presetNumber );
    
    //===============================================================
    // VISUAL SETTINGS
    
    state->visualPreset = ROMVisualPresetOrder[ state->presetIndex ];
    
    state->spinnerModeAdvanceRate = ROMSpinModeAdvRate[ state->visualPreset ];
    
    state->dualSpinners = ROMDualSpinners[ state->visualPreset ];
    state->spinnerSizeOffset = ROMSpinnerSizeOffset[ state->visualPreset ];
    state->spinnerScaleX = ROMSpinnerScaleX[ state->visualPreset ];
    state->spinnerScaleY = ROMSpinnerScaleY[ state->visualPreset ];
    
    // set up correct textures based on menu selection
    const int* ROMPattern;
    switch( state->visualPreset )
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
        state->spinnerArray[i].size = ROMSpinnerSize[ state->visualPreset * MAX_MAIN_SPINNERS + i ];
    }
    
    // then turn on a few spinners
    for( int i=0; i<4; i++ )
        state->spinnerArray[i].active = true;
    
    // reset the frame count so spinner sequence starts in the same place
    frameCount = 0;
    //*/

    // \/    \/    \/    \/    \/ //
    //---------------------------------------------------------------------------------------------------------
    // END OF NEW CODE
    // -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - 
    
    
    
    
    // -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- -
    // START OF ORIGINAL CODE
    //---------------------------------------------------------------------------------------------------------    
    
    // set app into play mode
    /*appMode = kAppModeRunning;
    
    // USE PRESET LOOKUP TABLE FOR INDEPENDENT VISUAL AND SOUND PRESETS
    visualPreset = ROMVisualPresetOrder[presetIndex];
    originalPresetIndex = visualPreset;
    int tempSoundPreset = ROMSoundPresetOrder[presetIndex];
    if( loadAudio )
        soundPreset = tempSoundPreset;
    
    //===============================================================
    // SOUND SETTINGS
    
    looper.vibratoLevel = ROMVibrato[tempSoundPreset];
    looper.creepRate = ROMLoopCreepRate[tempSoundPreset];
    looper.vibratoRate = ROMVibratoRate[tempSoundPreset];
    looper.loopOffsetUpdateInterval = ROMLoopOffsetUpdateInterval[tempSoundPreset];
    looper.binauralVibrato = ROMBinauralVibrato[tempSoundPreset];
    looper.binauralVibratoRate = ROMBinauralVibratoRate[tempSoundPreset];
    
    // THE VOLUME SETTING is generally just to compensate for the volume of the source material, so...
    // only set the volume when also loading a new audio file.
    if( loadAudio )
    {
        looper.loopDivider = ROMloopDivider[tempSoundPreset];
        looper.binauralPitch = ROMBinauralPitch[tempSoundPreset];
        looper.binauralVolume = ROMBinauralVolume[tempSoundPreset];
        looper.presetVolume = ROMVolume[tempSoundPreset];
        looper.loopLengthInFrames = ROMLoopLength[tempSoundPreset];
    }
    
    // set up initial audio status
    for( int trackIndex=0; trackIndex<=2; trackIndex++ )
    {
        looper.voiceArrayPtr[trackIndex].loopOffset = 0;
        looper.voiceArrayPtr[trackIndex].totalFrames = 0;
        looper.voiceArrayPtr[trackIndex].loopCount = 0;
        looper.voiceArrayPtr[trackIndex].envelope = 0.5;
    } 
    
    if( appSoundMode==kAppSoundModeInstrumentA )
        looper.loopLengthInFrames /= 4;
    
    // setup track 3 as an echo of track 0 
    //looper.voiceArrayPtr[3].loopOffset = looper.voiceArrayPtr[1].loopOffset+kEchoOffset;
    //looper.voiceArrayPtr[3].envelope = looper.voiceArrayPtr[1].envelope;
    
    //===============================================================
    // VISUAL SETTINGS
    
    spinnerModeAdvanceRate = ROMSpinModeAdvRate[visualPreset];
    
    dualSpinners = ROMDualSpinners[visualPreset];
    spinnerSizeOffset = ROMSpinnerSizeOffset[visualPreset];
    spinnerScaleX = ROMSpinnerScaleX [visualPreset];
    spinnerScaleY = ROMSpinnerScaleY [visualPreset];
    
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
        mainSpinnerArray[spinner].texture = ROMPattern[spinner];
    
    // turn off all spinners and set rotation rates
    for( int i=0; i<kMaxMainSpinners; i++ )
    {
        mainSpinnerArray[i].rotationRate = 45.0+i*5;
        mainSpinnerArray[i].active = false;
        mainSpinnerArray[i].size = ROMSpinnerSize[ visualPreset*kMaxMainSpinners + i ];
    }
    
    // then turn on a few spinners
    for( int i=0; i<4; i++ )
        mainSpinnerArray[i].active = true;
    
    // reset the frame count so spinner sequence starts in the same place
    frameCount = 0;
    //*/
    
}



//////////////////////////////////////////////////////////////////////////////////////
void MCGame::updateFrame()
{
    frameCount++;
    static long bloomCycleCounter =0;
    bloomCycleCounter++;
    
    int buttonJiggler = frameCount; 
    
    // HANDLE FADE INS
    if( state->menuFadeIn < 1 )
        state->menuFadeIn += 0.012;
    if( state->menuFadeIn > 1.0 )
        state->menuFadeIn = 1.0;

    // IF STARTING MENU MODE...
    if( state->mode == AppMode::RUNNING  &&  state->previousMode != AppMode::RUNNING )
    {
        for( int i=0; i<MAX_ACTIVE_SPINNERS; i++ )
            state->spinnerArray[i].active = false;
    }
    
    // MENU MODE FRAME UPDATE...
    if( state->mode == AppMode::MENU )
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

    // IF STARTING RUNNING MODE...
    if( state->mode == AppMode::RUNNING  &&  state->previousMode != AppMode::RUNNING )
    {
        state->presetIndex = (int) state->menuWheelPosition;
        //manualTextureSelection = false;
        state->runningFadeIn = 0.4;
        loadPreset( state->presetIndex );
    }

    // TODO: MOVE SOMEWHERE
    const float kFadeInStartPoint = 0.7; // 0.5
    
    
    // RUNNING MODE FRAME UPDATE...
    if( state->mode == AppMode::RUNNING )
    {
        // UPDATE ALL MAIN SPINNERS...
        for( int spinnerIndex=0; spinnerIndex< MAX_ACTIVE_SPINNERS ; spinnerIndex++ )
        {
            
            float rhythmBloom = 0;
            rhythmBloom = 0.78+((1.7-abs(cos(bloomCycleCounter/700.0)+0.7))*0.43) // <- long cycle
                + sin(((int)state->audioLoopPosition%100000)/101000.0*3.141592654)*0.80 * cos(bloomCycleCounter/150.0); // <- short cycle
            
            float biggestSpinner = 0;
            for( int i=8; i>=spinnerIndex; i-- )
            {
                float spinnerSizeX = state->spinnerArray[i].size * (state->runningFadeIn - kFadeInStartPoint) * state->menuFadeIn * rhythmBloom * 0.97;
                if( spinnerSizeX > biggestSpinner )
                    biggestSpinner = spinnerSizeX;
            }
            
            /*if( (state->spinnerArray[spinnerIndex].active) )
            {
                // DUAL SPINNERS ON/OFF
                if( !state->dualSpinners )
                    state->spinPolarity = 0;
                
                //#define kSpinnerSplit (spinnerIndex*0.25-0.5)
#define kSpinnerSplit 0
                
                // Enforce minimum spinner speed -- looks better and avoids copyright issues
                if(abs(state->spinnerArray[spinnerIndex].rotationRate + state->creep) < 8)
                    state->spinnerArray[spinnerIndex].rotationRate +=  1.7;
                if((long)abs(state->spinnerArray[spinnerIndex].rotationRate + state->creep)%180 > 171)
                    state->spinnerArray[spinnerIndex].rotationRate +=  1.7;
                if((long)abs(state->spinnerArray[spinnerIndex].rotationRate + state->creep)%180 < 8)
                    state->spinnerArray[spinnerIndex].rotationRate +=  1.7;
                
                state->spinnerArray[spinnerIndex].rotationPosition += state->spinnerArray[spinnerIndex].rotationRate + creep;
                ////glBindTexture(GL_TEXTURE_2D,spinnerTextureArray[ state->spinnerArray[spinnerIndex].texture ]);
                ////glLoadIdentity();
                
                static int flipper=1;
                flipper *= -1;
                
                const float kMaxSpinnerSize = 2.5;
                float spinnerSizeX, spinnerSizeY;
                
                // apply menuFadeIn to every spinner size except the first
                /*if( spinnerIndex == 0 )
                {
                    // FIRST SPINNER (the biggest spinner in the background)
                    spinnerSizeX = state->spinnerArray[spinnerIndex].size*(state->runningFadeIn-kFadeInStartPoint)*rhythmBloom*0.7*state->spinnerScaleX*pitchBend+spinnerSizeOffset;
                    spinnerSizeY = state->spinnerArray[spinnerIndex].size*(state->runningFadeIn-kFadeInStartPoint)*0.85*state->spinnerScaleX*pitchBend+spinnerSizeOffset;
                }
                else 
                {    // ALL OTHER SPINNERS
                    spinnerSizeX = state->spinnerArray[spinnerIndex].size*(state->runningFadeIn-kFadeInStartPoint)*state->menuFadeIn*rhythmBloom*0.7*spinnerScaleX*pitchBend;
                    spinnerSizeY = state->spinnerArray[spinnerIndex].size*(state->runningFadeIn-kFadeInStartPoint)*state->menuFadeIn*0.85*spinnerScaleY*pitchBend;
                } //*/
                
                // MAKE SPINNERS SMALLER IN INSTRUMENT MODE
                /*float spinnerScaling;
                if( state->appSoundMode==kAppSoundModeInstrumentA )
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
              /*      spinnerScaling = 1.0;
                
                if( !showMenuSideways )
                    glTranslatef( (-0.7+(runningFadeIn-0.5)*0.7),
                                 (prayerWheelPosition*2-(int)prayerWheelPosition*2-1)*(1.5-runningFadeIn)+0.2*spinPolarity*(doubleSpin*2-1)
                                 +kSpinnerSplit, 0.0f);
                else 
                    glTranslatef( (-0.7+(1.5-0.5)*0.7),
                                 (1.5-runningFadeIn)*0.7+0.2*spinPolarity*(doubleSpin*2-1)
                                 +kSpinnerSplit, 0.0f);
                
                glRotatef(mainSpinnerArray[spinnerIndex].rotationPosition, 0.0f, 0.0f, 1.0f);
                if( spinnerSizeX > kMaxSpinnerSize )
                    spinnerSizeX = kMaxSpinnerSize;
                glScalef( spinnerSizeX, spinnerSizeY, 0.0);

                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            }  //*/
            
        } // for all main spinnaz 
    }
    

    state->previousMode = state->mode;

        // \/    \/    \/    \/    \/ //
    //---------------------------------------------------------------------------------------------------------
    // END OF NEW CODE
    // -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - 
    
    

    
    // -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- - -- -
    // START OF ORIGINAL CODE
    //---------------------------------------------------------------------------------------------------------    
    /*
    // GET CURRENT ELAPSED TIME IN FRAMES
    float framesPerFrame = (displayID.timestamp - lastTimestamp)*60.0;
    lastTimestamp = displayID.timestamp;
    
    GLenum error = glGetError();
    if( error != 0 ) NSLog(@"OpenGL Error at start of drawView : Error #%d",error);
    
    const float kFadeInStartPoint = 0.7; // 0.5
    
    // HANDLE FADE INS
    if( menuFadeIn < 1 )
        menuFadeIn += 0.012;
    if( menuFadeIn > 1.0 )
        menuFadeIn = 1.0;
    
    
    if( runningFadeIn < 1.5 )
        runningFadeIn += 0.006;
    if( runningFadeIn > 1.5 )
        runningFadeIn = 1.5;
    
    //----------------------------------------------------------------------------
    
    //===================================================
    // CHANGE IMAGE/SOUND SETTINGS AT REGULAR INTERVALS
    //===================================================
    
    static float texOffset=0;
    texOffset += 0.12;
    //static const 
    //GLfloat texCoords[] = {sin(texOffset),0.0,1.0,sin(texOffset),0.0,0.0,sin(texOffset),0.0 };
    
    //---------------------------
    // LOAD NEW TEXTURE PRESET EVERY 32 CYCLES
#ifdef kEnableSpinnerPresetCycling_Debug
    if( appMode == kAppModeRunning )
        //if( (frameCount%(spinnerModeAdvanceRate*4) == 0) && ( frameCount > spinnerModeAdvanceRate ) ) // EVERY 32 CYCLES
        if( (frameCount%(spinnerModeAdvanceRate*2) == 0) && ( frameCount > spinnerModeAdvanceRate ) && ( appSoundMode != kAppSoundModeInstrumentA) ) // EVERY 16 CYCLES
            //if( (frameCount%(spinnerModeAdvanceRate/16) == 0) ) //&& (frameCount > spinnerModeAdvanceRate) ) // EVER 1 CYCLE
        {
            presetIndex++;
            if( presetIndex == kNumberOfPresets )
                presetIndex = 0;
            [self loadPreset:presetIndex loadAudio:false];
        }
#endif
    
    spinnerPhase = (frameCount%(spinnerModeAdvanceRate*2))/((spinnerModeAdvanceRate*2)/8);
    
    //---------------------------
    // CYCLE SPINNER MODES
    if( (frameCount%(spinnerModeAdvanceRate/4)==0) && (appMode == kAppModeRunning) && !disableSpinnerModes )
    {
        // THINGS TO DO HERE
        // - load different spinners every two complete cycles
        // - change audio samples every two or three complete cycles
        
        
#ifndef kDisableSpinnerPhases_Debug
        
        if( appSoundMode != kAppSoundModeInstrumentA )
            switch( (frameCount%spinnerModeAdvanceRate)/(spinnerModeAdvanceRate/4) )
        {
            case 0: for(int i=0; i<kMaxMainSpinners; i++ ) mainSpinnerArray[i].active=FALSE;
                for(int i=0; i<2; i++ ) mainSpinnerArray[i].active=TRUE;  
                [looper creepJump]; break;
            case 1: for(int i=0; i<kMaxMainSpinners; i++ ) mainSpinnerArray[i].active=FALSE;
                for(int i=0; i<4; i++ ) mainSpinnerArray[i].active=TRUE;  
                [looper creepJump]; break;
            case 2: for(int i=0; i<kMaxMainSpinners; i++ ) mainSpinnerArray[i].active=FALSE;
                for(int i=2; i<6; i++ ) mainSpinnerArray[i].active=TRUE;  
                mainSpinnerArray[0].active=TRUE;  
                [looper creepJump]; break;
            case 3: for(int i=0; i<kMaxMainSpinners; i++ ) mainSpinnerArray[i].active=FALSE;
                for(int i=4; i<8; i++ ) mainSpinnerArray[i].active=TRUE;  
                mainSpinnerArray[0].active=TRUE;  
                [looper creepJump]; break;
        }
        
#endif
        
        looper.tremoloRate = ROMTromoloRate[soundPreset][(frameCount/(spinnerModeAdvanceRate/4))%8];
        
        if( appSoundMode != kAppSoundModeBinaural )
            looper.tremoloLevel = (ROMTromoloLevel[soundPreset][(frameCount/(spinnerModeAdvanceRate/4))%8]) * kMasterTremoloLevel;
        else 
            looper.tremoloLevel = 1.0;
        
        
        if( manualTextureSelection == false )
        {
            
            // ALTERNATE SECONDARY SPINNER PATTERNS EVERY 8 CYCLES
            const int* ROMPattern;
            if( (frameCount%(spinnerModeAdvanceRate*4))/(spinnerModeAdvanceRate*2) == 0 )
            {
                switch( visualPreset)
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
                switch( visualPreset )
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
                mainSpinnerArray[spinner].texture = ROMPattern[spinner];
        }
        
        menuFadeIn = 0.4;
        
        //if( (appSoundMode==kAppSoundModeInstrumentA) || (appSoundMode==kAppSoundModeiPod) )
        //    looper.voiceArrayPtr[frameCount%3].loopOffset = frameCount*(frameCount%3);
    }
    frameCount++;
    //*/
    
    
}
