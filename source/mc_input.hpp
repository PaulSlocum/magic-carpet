// mc_input.hpp
////////////////////////////////////////////////////////////////////////////////


class MCAppState;
struct SDL_TouchFingerEvent;


class MCInput 
{
public:
    MCInput( MCAppState* newState );
    ~MCInput();
    void processTouchEvent( const SDL_TouchFingerEvent event );

private:
    MCAppState* state;
    // ~  ~  ~  ~  ~  ~  ~  
};
