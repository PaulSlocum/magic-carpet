// mc_game.hpp
////////////////////////////////////////////////////////////////////////


class MCAppState;
class MCInput;
class MCAudio;
union SDL_Event;


#define NUMBER_OF_PRESETS 7


class MCGame
{
public:
    MCGame( MCAppState* newState );
    ~MCGame();
    void start();
    void stop();
    void processEvent( SDL_Event event );
    void updateFrame();
    
private:
    MCAppState* state;
    // ~  ~  ~  ~  ~  ~  ~  
    int frameCount = 0;    
    long long startTimeMSec = 0;
    // ~  ~  ~  ~  ~  ~  ~  
    void loadPreset( const int presetNumber );
    // ~  ~  ~  ~  ~  ~  ~
    MCInput* inputHandler;
    MCAudio* audioController;
    // ~  ~  ~  ~  ~  ~  ~
    void initMenuMode();
    void updateMenuModeFrame();
    void initRunningMode();
    void updateRunningModeFrame();
    void updateSpinnerMode();
};
