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
  
    // --   --   --   --   --   --   --   --   --   --   --   --   --   --   
    // ORIGINAL CODE
    
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
    int buttonJiggler = frameCount; 
    
    // HANDLE FADE INS
    if( state->menuFadeIn < 1 )
        state->menuFadeIn += 0.012;
    if( state->menuFadeIn > 1.0 )
        state->menuFadeIn = 1.0;

    // KEEP MENU WHEEL IN RANGE
    if( state->menuWheelPosition>=NUMBER_OF_PRESETS )
        state->menuWheelPosition -= NUMBER_OF_PRESETS;
    if( state->menuWheelPosition<0.0 )
        state->menuWheelPosition += NUMBER_OF_PRESETS;

    if( state->mode == AppMode::MENU )
    {
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

    
    /*state->spinnerArray[0].active = true;
    state->spinnerArray[0].rotationPosition = frameCount * 30.1;
    state->spinnerArray[0].texture = 13;

    state->spinnerArray[1].active = true;
    state->spinnerArray[1].rotationPosition = frameCount * 19.1;
    state->spinnerArray[1].size = 0.5;
    state->spinnerArray[1].texture = 14;
    
    state->spinnerArray[2].active = true;
    state->spinnerArray[2].rotationPosition = frameCount * 49.1;
    state->spinnerArray[2].size = 0.2;
    state->spinnerArray[2].texture = 19; //*/
    
    // DEBUG -- ANY ANIMATION SHOULD REALLY BE DONE IN THE 'GAME' CLASS
    /*static float angle;
    angle = frameCount * 30.1;
    static float size;
    size += 0.001;
    if( size>1.3 ) size = 0.0;
    size = 0.25;
    static float xOffset;
    xOffset += 0.002;
    if( xOffset>0.8 ) xOffset = 0.2;
    static float yOffset;
    //yOffset += 0.001;
    //if( yOffset>1.2 ) yOffset = -1.0;
    yOffset = 0.5; //*/
    // \/    \/    \/    \/    \/ //
    //---------------------------------------------------------------------------------------------------------
    // END OF TEST CODE
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
