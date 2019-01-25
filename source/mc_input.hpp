// mc_input.hpp
////////////////////////////////////////////////////////////////////////////////

#include <set>

class MCGame;
struct SDL_TouchFingerEvent;
struct SDL_KeyboardEvent;


class MCInput 
{
public:
    MCInput( MCGame* newGame );
    ~MCInput();
    void processTouchEvent( const SDL_TouchFingerEvent event );
    void processKeyboardEvent( const SDL_KeyboardEvent event );

private:
    MCGame* game;
    // ~  ~  ~  ~  ~  ~  ~
    std::set<int> keysDown;
};
