// mc_game.hpp
////////////////////////////////////////////////////////////////////////


class MCApplication;


class MCGame
{
public:
    MCGame( MCApplication* newApp );
    ~MCGame();
    void init();
    void updateFrame();
    
private:
    MCApplication* app;
    // ~  ~  ~  ~  ~  ~  ~  
    int frameCount = 0;
    float prayerWheelPosition = 0.0;
    // ~  ~  ~  ~  ~  ~  ~  
    void loadPreset( const int presetNumber );
};
