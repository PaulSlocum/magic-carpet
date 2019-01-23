// mc_audio.hpp
/////////////////////////////////////////////////////////////////////


class MCAppState;

class MCAudio 
{
public:
    MCAudio( MCAppState* newState );
    ~MCAudio();
    void start();
    
private:
    MCAppState* state;
    // ~  ~  ~  ~  ~  ~  
    bool started = false;
};
