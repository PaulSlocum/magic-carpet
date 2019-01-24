// mc_game.hpp
////////////////////////////////////////////////////////////////////////


class MCAppState;


#define NUMBER_OF_PRESETS 7


class MCGame
{
public:
    MCGame( MCAppState* newState );
    ~MCGame();
    void start();
    void stop();
    void updateFrame();
    
private:
    MCAppState* state;
    // ~  ~  ~  ~  ~  ~  ~  
    int frameCount = 0;
    // ~  ~  ~  ~  ~  ~  ~  
    void loadPreset( const int presetNumber );
    // ~  ~  ~  ~  ~  ~  ~
    void initMenuMode();
    void updateMenuModeFrame();
    void initRunningMode();
    void updateRunningModeFrame();
    void updateSpinnerMode();
};
