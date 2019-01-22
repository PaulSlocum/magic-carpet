// mc_input.hpp
////////////////////////////////////////////////////////////////////////////////

#include <set>

class MCAppState;
struct SDL_TouchFingerEvent;
struct SDL_KeyboardEvent;


class MCInput 
{
public:
    MCInput( MCAppState* newState );
    ~MCInput();
    void processTouchEvent( const SDL_TouchFingerEvent event );
    void processKeyboardEvent( const SDL_KeyboardEvent event );

private:
    MCAppState* state;
    // ~  ~  ~  ~  ~  ~  ~
    std::set<int> keyState;
};
