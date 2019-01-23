// mc_audio.hpp
/////////////////////////////////////////////////////////////////////


class MCAppState;

class MCAudio 
{
public:
    MCAudio( MCAppState* newState );
    ~MCAudio();
    void start();
    void callback( Uint8* stream, int len );
    
private:
    MCAppState* state;
    // ~  ~  ~  ~  ~  ~  
    bool started = false;
    short* audioDecodeBuffer;
    long audioFileLength = 0;
    long playbackOffset = 0;
    
};
