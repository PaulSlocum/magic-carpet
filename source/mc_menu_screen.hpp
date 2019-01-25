// mc_menu_screen.hpp
////////////////////////////////////////////////////////////////////////////////

class MCGame;


class MCMenuScreen 
{
public:
    MCMenuScreen( MCGame* newGame );
    ~MCMenuScreen();
    void init();
    void updateFrame();
    
private:
    MCGame* game;
    // ~  ~  ~  ~  ~  ~  ~
};

