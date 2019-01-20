// mc_game.hpp
////////////////////////////////////////////////////////////////////////


class MCApplication;


class MCGame
{
public:
    MCGame( MCApplication* newApp );
    ~MCGame();
    void updateFrame();
    
private:
    MCApplication* app;
    int frameCount = 0;
    void loadPreset( int presetNumber );
};
