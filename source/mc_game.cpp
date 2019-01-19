// mc_game.cpp
////////////////////////////////////////////////////////////////////////


#include "mc_game.hpp"
#include "mc_application.hpp"



//////////////////////////////////////////////////////////////////////////////////////
MCGame::MCGame( MCApplication* newApp )
{
    app = newApp;
}



//////////////////////////////////////////////////////////////////////////////////////
MCGame::~MCGame()
{
}




//////////////////////////////////////////////////////////////////////////////////////
void MCGame::updateFrame()
{
    frameCount++;
    
    app->spinnerArray[0].active = true;
    app->spinnerArray[0].rotationPosition = frameCount * 30.1;
    app->spinnerArray[0].texture = 13;

    app->spinnerArray[1].active = true;
    app->spinnerArray[1].rotationPosition = frameCount * 19.1;
    app->spinnerArray[1].size = 0.5;
    app->spinnerArray[1].texture = 14;
    
    app->spinnerArray[2].active = true;
    app->spinnerArray[2].rotationPosition = frameCount * 49.1;
    app->spinnerArray[2].size = 0.2;
    app->spinnerArray[2].texture = 19;
    
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
