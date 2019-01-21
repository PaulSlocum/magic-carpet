// mc_sequence_data.hpp
///////////////////////////////////////////////////////////////////////////////

//====================================================================================
//
// ** PRESETS **
//
// There are 7 presets that can be chosen from the menu.  Each preset has different
// music and graphics settings.  These const arrays define the settings for each
// preset.

// PRESETS:
// 1) Sound: KYRIE
// 2) Sound: GATHERING
// 3) Sound: SS BELLS
// 4) Sound: CHURCH ORGAN/CHOIR
// 5) Sound: BELLS
// 6) Sound: CHURCH ORGAN
// 7) Sound: SLOWDIVE
//

// GOOD TEXTURES (?)
//42 44 51 42 44 42 45 46
// 52,38,33,33,33,38,33,45 <
//44,27,33,36,44,44,37,38
//53,26,43,53,53,55,53,50

// NEW GOOD TEXTURES
// ---------------------
// 67,63,59,67,63,67,91,89
// 70,101,3,99,4,91,3,100
//107,64,96,97,20,93,110,74


//  #O#O#O#O#O#O#O#O#O#O#O#O
// <O#O VISUAL SETTINGS O#O#>
//  #O#O#O#O#O#O#O#O#O#O#O#O

#ifndef kLITE_VERSION
const int ROMVisualPresetOrder[] = {0,1,2,3,4,5,6};
#else
const int ROMVisualPresetOrder[] = {0,1,4,3,2,5,6};
#endif

// MENU SPINNER TEXTURES
const int ROMPreviewTrack0[] = {  1,  21,   22,   44,    53,   107,   48  };
const int ROMPreviewTrack1[] = {  1,  26,   25,   20,    53,   64,   4  };

// SPINNER TEXTURES     spinner#   1    2     3     4     5     6     7
const int ROMPatternA1[] = {  1,  1, 29,  1, 14, 29,  1, 21 };
const int ROMPatternA2[] = { 21, 20, 13, 21, 13, 20, 31,  0 };
const int ROMPatternA3[] = { 19, 25, 22, 19, 22, 25, 19, 19 };
const int ROMPatternA4[] = { 44, 20, 33, 36, 44, 44, 33, 38 };
const int ROMPatternA5[] = { 53, 26, 43, 53, 53, 55, 26, 50 };
const int ROMPatternA6[] = { 107,64, 96, 97, 20, 93,  4, 74 };
const int ROMPatternA7[] = { 48,  4, 20, 55,  4, 48,  4, 47 };

// SPINNER TEXTURES B   preset#   1    2     3     4     5     6     7
const int ROMPatternB1[] = {  2,  1, 30,  1, 14, 29,  1, 21  };
const int ROMPatternB2[] = { 42, 20, 13, 19, 14, 54, 13,  0  };
const int ROMPatternB3[] = { 57, 25, 22, 22, 28, 25, 36, 19  };
const int ROMPatternB4[] = { 41, 20, 33, 36, 44, 43, 33, 38  };
const int ROMPatternB5[] = { 55, 26, 49, 53, 53, 55, 45, 50  };
const int ROMPatternB6[] = { 111,64, 96, 97, 20, 93,111, 74  };
const int ROMPatternB7[] = { 46,  4, 20, 56,  4, 48,  4, 47  };

// SPINNER SIZES       spinner# 0    1    2    3    4    5    6    7  
const float ROMSpinnerSize[] = { 
    4.5, 1.4, 0.9, 0.7, 1.1, 0.9, 0.6, 0.5, // preset #1
    4.5, 1.2, 1.3, 0.7, 1.1, 0.6, 0.6, 0.5, // preset #2 
    4.5, 1.2, 1.3, 0.7, 1.1, 0.7, 0.4, 0.5, // preset #3
    4.5, 1.2, 1.3, 0.7, 1.1, 0.7, 0.4, 0.5, // preset #4
    4.5, 1.2, 1.3, 1.1, 1.2, 0.7, 0.5, 0.5, // preset #5
    1.5, 2.4, 2.3, 1.7, 2.1, 1.6, 1.6, 1.5, // preset #2 
    4.5, 1.2, 1.3, 0.7, 1.1, 0.7, 0.4, 0.5, // preset #7
};

const float ROMSpinnerSizeOffset[] = { -0.50,-0.25,0.00,0.00,-0.20,2.00,-0.20 };
const float ROMSpinnerScaleX[] = { 1.0,1.0,0.8,0.5, 0.5,0.5,0.5 };
const float ROMSpinnerScaleY[] = { 1.0,1.0,0.8,1.0, 1.0,0.5,1.0 };

// DUAL SPINNERS
const bool ROMDualSpinners[] = { false, false, false, false, false, false, false };

const float ROMBGColorRedA[] =   { 0.3f,  0.4f,  0.4f,  0.4f,  0.25f,  0.1f,  0.34f };
const float ROMBGColorGreenA[] = { 0.15f, 0.2f,  0.25f, 0.30f, 0.20f, 0.05f, 0.25f };
const float ROMBGColorBlueA[] = {  0.1f,  0.2f,  0.50f, 0.25f,  0.20f,  0.0f,  0.25f };

const float ROMBGColorRedB[] =   { 1.0f,  0.0f,  1.0f,  1.0f, 0.55f, 0.50f,  0.60f };
const float ROMBGColorGreenB[] = { 0.95f, 0.0f, 0.90f, 0.95f, 0.35f, 0.35f, 0.50f };
const float ROMBGColorBlueB[] = {  0.95f, 0.0f, 0.90f, 0.95f, 0.75f, 0.30f, 0.50f };

// SPINNER MODE ADV RATE
const long ROMSpinModeAdvRate[] =  { 7000, 6500, 6000, 4500, 5500, 5000, 4500 };


//  ========================
//  #O#O#O#O#O#O#O#O#O#O#O#O
// <O#O# SOUND SETTINGS O#O#>
//  #O#O#O#O#O#O#O#O#O#O#O#O
//  ========================

#ifndef kLITE_VERSION
const int ROMSoundPresetOrder[] = { 6 ,2 ,5 ,3 ,4 ,1 ,0 };
#else
const int ROMSoundPresetOrder[] = { 6 ,2 ,4 ,3 ,5 ,1 ,0 };
#endif

// VOLUME 
const float ROMVolume[] =               { -5,  -10, -18, -15,   -23, -23, -21 };
//        0    1   2     3     4    5    6
const float ROMBinauralVolume[] =      {  -7, -5,  -10,  -7,  -12,  -8,  -5 };
const float ROMBinauralVibrato[] =     { 0.1, 0.00, 0.03, 0.01,  0.03,  0.01, 0.02 };
const float ROMBinauralVibratoRate[] = { 0.01,0.01, 0.01, 0.01,  10.0,  0.01, 20.1 };
const float ROMBinauralPitch[] = //  0      1        2      3       4         5      6     
{    0,   -0.11,   -0.2,  0.099,  -0.11,   -0.002,  0.1, // phase 1 // 
    0,   -0.11,   -0.2,  0.099,  -0.11,   -0.002,  0.1, // phase 2
    0,   -0.11,   -0.1,  0.099,  -0.11,  -0.002,   0.2534, // phase 3
    0,   0.076,   -0.2,  0.099,  -0.11,  -0.148,  0.2534, // phase 4 //
    0,   -0.11,   -0.2,  -0.204, -0.25,   -0.002,  0.1, // phase 5 //
    0,   -0.11,   -0.2,  -0.204, -0.45,  -0.002 ,  0.1, // phase 6
    0,   0.076,   -0.3,  0.0129, -0.11,   -0.002,  -0.251, // phase 7
    0,   0.076,   -0.2,  0.0129, -0.211,  -0.148,  -0.251  // phase 8 //
}; //                0.21

const float ROMLoopOffsetUpdateInterval[] = {2,4,4,4, 4,4,2}; //??????

// LOOP LENGTHS                    1       2      3      4      5      6      7
const long ROMLoopLength[] = { 24000, 25000, 70000, 12000, 30000, 14000, 16384 };

const int ROMloopDivider[] = { 2, 2, 1, 2, 2, 1, 2 };

// VIBRATO
const float ROMVibrato[] =         {  0.5,  1.1,  5.1,   1.0,   0.3,   1.1,  0.5 };
const float ROMVibratoRate[] =     { 0.003, 0.003, 0.003, 0.003, 0.007, 0.003, 0.003 };

// LOOP ADVANCE RATE
const float ROMLoopCreepRate[] =   { 16000, 3000, 3000, 200, 2000, 1500, 700 };

// VOICE THICKNESS 2=thick 1=medium 0=thin
const long ROMVoiceThickness[] =   { 2,  1,  2,  1,  1,  1,  1 };

// spinner cycle#    1   2  3  4  5   6  7  8
const float ROMTromoloRate[][8] = {    
    {5,3,5,3, 5,3,5,3}, // preset #1
    {25,24,25,24, 25,24,25,24}, // preset #2
    {25,18,25,18, 25,18,25,18}, // preset #3
    {2,2.5,2,2.5, 2,2.5,2,2.5}, // preset #4
    {18,18,18,18, 18,18,18,18}, // preset #5
    {12,14,12,14, 12,14,12,14}, // preset #6
    {13,12,13,12, 12,13,12,26}}; // preset #7

// spinner cycle#    1   2  3  4  5   6  7  8
const float ROMTromoloLevel[][8] = {    
    {1,1,1,1, 1,1,1,1}, // preset #1
    {1,1,1,1, 1,1,1,1}, // preset #2
    {1,1,1,1, 1,1,1,1}, // preset #3
    {4,4,4,4, 4,4,4,4}, // preset #4
    {5,5,2,2, 4,5,2,2}, // preset #5
    {5,3,5,3, 5,3,5,3}, // preset #6
    {4,4,4,4, 4,4,4,4}}; // preset #7


// SOUND NOTES:
//
// 12 = good, 13 = good, right on, 14 = pretty good, too quiet, 15 = wonky, 16 = decent, kinda wonky, 17 = double, good, slightly wonky, 18 = good, like triplets, 19 = good, triplets, 
// 20 = good, wonky triplets , 21 = good, heavily lopsided triplets, 22 = wonky, 23 = almost 16ths, wonky, 24 = almost 16ths, little wonky, 25 = sixteenths, slightly wonky, 
// 26= sixteenths, pretty even, 27 = jerky sixteenths, 
// 13, 18, 19, 26

//====================================================================================
