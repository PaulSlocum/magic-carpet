// mc_game_screen.hpp
////////////////////////////////////////////////////////////////////////////////

class MCGame;


class MCGameScreen 
{
public:
    MCGameScreen( MCGame* newGame );
    ~MCGameScreen();
    void init();
    void updateFrame();
    
private:
    MCGame* game;
    // ~  ~  ~  ~  ~  ~  ~
    void updateSpinnerMode();
};

