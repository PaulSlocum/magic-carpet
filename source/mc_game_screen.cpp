// mc_game_screen.cpp
////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "mc_game_screen.hpp"
#include "mc_game.hpp"
#include "mc_sequence_data.hpp"
#include "mc_util.hpp"


// TODO: RENAME, MAYBE MOVE
const float kFadeInStartPoint = 0.7; // 0.5



//////////////////////////////////////////////////////////////////////////////////////
MCGameScreen::MCGameScreen( MCGame* newGame )
{
    game = newGame;
}



//////////////////////////////////////////////////////////////////////////////////////
MCGameScreen::~MCGameScreen()
{
}


//////////////////////////////////////////////////////////////////////////////////////
void MCGameScreen::init()
{
    game->loadPreset( game->visualPreset );
    //game->loadPreset( (int) game->menuWheelPosition ); // <-- OLD VERSION, CAN DELETE 

    game->manualTextureSelection = false;
    game->runningFadeIn = 0.4;
    game->normalButton.active = false;
    game->muteButton.active = false;
    game->instrumentButton.active = false;
}



//////////////////////////////////////////////////////////////////////////////////////
void MCGameScreen::updateFrame()
{
    // DEBUG! - bloomCycleCounter SHOULD EITHER BE MOVED TO CLASS OR USE FRAMECOUNTER INSTEAD
    static long bloomCycleCounter =0;
    bloomCycleCounter++;
    
    game->creep += 0.016;
    
    if( game->runningFadeIn > kFadeInStartPoint )
        game->background.active = false;
    
    updateSpinnerMode();
    
    // SET BACKGROUND COLOR...
    if( (((game->frameCount+game->spinnerModeAdvanceRate/4)%(game->spinnerModeAdvanceRate*2))/(game->spinnerModeAdvanceRate) == 0) 
       || (game->mode == AppMode::MENU) )
    {
        game->backgroundColor = { ROMBGColorRedA[ game->visualPreset ], ROMBGColorGreenA[ game->visualPreset ], ROMBGColorBlueA[ game->visualPreset ] };
    }
    else
    {
        game->backgroundColor = { ROMBGColorRedB[ game->visualPreset ], ROMBGColorGreenB[ game->visualPreset ], ROMBGColorBlueB[ game->visualPreset ] };
    }
    
    // UPDATE ALL MAIN SPINNERS...
    for( int spinnerIndex=0; spinnerIndex< MAX_ACTIVE_SPINNERS ; spinnerIndex++ )
    {
        float scaleFactor = ROMSpinnerSize[ state->visualPreset * MAX_MAIN_SPINNERS + i ];

        float rhythmBloom = 0.78+((1.7-abs(cos(bloomCycleCounter/700.0)+0.7))*0.43) // <- long cycle
        + sin(((int)game->audioLoopPosition%100000)/101000.0*3.141592654)*0.80 * cos(bloomCycleCounter/150.0); // <- short cycle
        
        float biggestSpinner = 0;
        for( int i=8; i>=spinnerIndex; i-- )
        {
            float spinnerSizeX = game->spinnerArray[i].scaleFactor * (game->runningFadeIn - kFadeInStartPoint) * game->menuFadeIn * rhythmBloom * 0.97;
            if( spinnerSizeX > biggestSpinner )
                biggestSpinner = spinnerSizeX;
        }
        
        game->spinnerArray[spinnerIndex].xPosition = convergeValue( game->spinnerArray[spinnerIndex].xPosition, 0.5, 0.002 );
        game->spinnerArray[spinnerIndex].yPosition = convergeValue( game->spinnerArray[spinnerIndex].yPosition, 0.5, 0.002 );
        
        if( (game->spinnerArray[spinnerIndex].active) )
        {
            // Enforce minimum spinner speed -- looks better and avoids copyright issues
            if(abs(game->spinnerArray[spinnerIndex].rotationRate + game->creep) < 8)
                game->spinnerArray[spinnerIndex].rotationRate +=  1.7;
            if((long)abs(game->spinnerArray[spinnerIndex].rotationRate + game->creep)%180 > 171)
                game->spinnerArray[spinnerIndex].rotationRate +=  1.7;
            if((long)abs(game->spinnerArray[spinnerIndex].rotationRate + game->creep)%180 < 8)
                game->spinnerArray[spinnerIndex].rotationRate +=  1.7;
            
            // ROTATE SPINNER
            game->spinnerArray[spinnerIndex].rotationPosition += game->spinnerArray[spinnerIndex].rotationRate + game->creep;
            
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
            const float SPINNER_SIZE_OFFSET = 0.2;
            if( spinnerIndex == 0 )
            {
                // FIRST SPINNER (the biggest spinner in the background)
                spinnerSizeX = game->spinnerArray[spinnerIndex].scaleFactor * 
                ( game->runningFadeIn - kFadeInStartPoint ) * rhythmBloom * 
                LARGE_SPINNER_SCALE_X * game->spinnerScaleX * game->pitchBend + game->spinnerSizeOffset + LARGE_SPINNER_SIZE_OFFSET;
                spinnerSizeY = game->spinnerArray[spinnerIndex].scaleFactor * 
                ( game->runningFadeIn - kFadeInStartPoint ) * LARGE_SPINNER_SCALE_Y * 
                game->spinnerScaleX * game->pitchBend + game->spinnerSizeOffset + LARGE_SPINNER_SIZE_OFFSET;
                const float kMinSpinnerSize = 0.8; 
                if( spinnerSizeX < kMinSpinnerSize )
                    spinnerSizeX = kMinSpinnerSize;
            }
            else 
            {    // ALL OTHER SPINNERS
                spinnerSizeX = game->spinnerArray[spinnerIndex].scaleFactor * 
                ( game->runningFadeIn - kFadeInStartPoint ) * game->menuFadeIn * rhythmBloom * 
                SPINNER_SCALE_X * game->spinnerScaleX * game->pitchBend + SPINNER_SIZE_OFFSET;
                spinnerSizeY = game->spinnerArray[spinnerIndex].scaleFactor * 
                ( game->runningFadeIn - kFadeInStartPoint ) * game->menuFadeIn * SPINNER_SCALE_Y * 
                game->spinnerScaleY * game->pitchBend + SPINNER_SIZE_OFFSET;
            } //*/
            
            // MAKE SPINNERS SMALLER IN INSTRUMENT MODE - THIS SECTION TO BE IMPLEMENTED LATER
            /*float spinnerScaling;
            if( appSoundMode==kAppSoundModeInstrumentA )
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
             else 
            spinnerScaling = 1.0; //*/
            
            const float kMaxSpinnerSize = 1.5; // ORIGINAL VALUE 2.5
            if( spinnerSizeX > kMaxSpinnerSize )
                spinnerSizeX = kMaxSpinnerSize;
            game->spinnerArray[spinnerIndex].size = spinnerSizeX; 
            
            ////glScalef( spinnerSizeX, spinnerSizeY, 0.0); // <-- OPENGL CODE INCLUDED FOR REFERENCE
            
            ////glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // <-- OPENGL CODE INCLUDED FOR REFERENCE
            //*/
        }  
        
    } // for all main spinnaz    
}




////////////////////////////////////////////////////////////////////////////////////////
void MCGameScreen::updateSpinnerMode()
{
    //spinnerPhase = (frameCount%(spinnerModeAdvanceRate*2))/((spinnerModeAdvanceRate*2)/8);
    
    //---------------------------
    // CYCLE SPINNER MODES
    if( (game->frameCount%(game->spinnerModeAdvanceRate/4)==0) && (game->mode == AppMode::RUNNING) )
    {
        // THINGS TO DO HERE
        // - load different spinners every two complete cycles
        // - change audio samples every two or three complete cycles
        
        if( game->soundMode != SoundMode::INSTRUMENT )
        {
            switch( (game->frameCount % game->spinnerModeAdvanceRate)/(game->spinnerModeAdvanceRate/4) )
            {
                case 0: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) game->spinnerArray[i].active=false;
                    for(int i=0; i<2; i++ ) game->spinnerArray[i].active=true;  
                    //[looper creepJump]; // TODO: IMPLEMENT THIS 
                    break;
                case 1: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) game->spinnerArray[i].active=false;
                    for(int i=0; i<4; i++ ) game->spinnerArray[i].active=true;  
                    //[looper creepJump]; // TODO: IMPLEMENT THIS  
                    break;
                case 2: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) game->spinnerArray[i].active=false;
                    for(int i=2; i<6; i++ ) game->spinnerArray[i].active=true;  
                    game->spinnerArray[0].active=true;  
                    //[looper creepJump];  // TODO: IMPLEMENT THIS 
                    break;
                case 3: for(int i=0; i<MAX_MAIN_SPINNERS; i++ ) game->spinnerArray[i].active=false;
                    for(int i=4; i<8; i++ ) game->spinnerArray[i].active=true;  
                    game->spinnerArray[0].active=true;  
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
        
        
        if( game->manualTextureSelection == false )
        {
            // ALTERNATE SECONDARY SPINNER PATTERNS EVERY 8 CYCLES
            const int* ROMPattern;
            if( (game->frameCount%(game->spinnerModeAdvanceRate*4))/(game->spinnerModeAdvanceRate*2) == 0 )
            {
                switch( game->visualPreset)
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
                switch( game->visualPreset )
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
                game->spinnerArray[spinner].texture = ROMPattern[spinner]; 
        }
        
        game->menuFadeIn = 0.4; 
        
        // TODO: IMPLEMENT THIS IS SOUND CLASS
        //if( (appSoundMode==kAppSoundModeInstrumentA) || (appSoundMode==kAppSoundModeiPod) )
        //    looper.voiceArrayPtr[frameCount%3].loopOffset = frameCount*(frameCount%3);
    }
    /* */
    
}

