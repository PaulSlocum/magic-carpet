// mc_audio.hpp
/////////////////////////////////////////////////////////////////////


class MCGame;

class MCAudio 
{
public:
    MCAudio( MCGame* newGame );
    ~MCAudio();
    void start();
    void callback( Uint8* stream, int len );
    
private:
    MCGame* game;
    // ~  ~  ~  ~  ~  ~  
    bool started = false;
    short* audioDecodeBuffer;
    long audioFileLength = 0;
    long playbackOffset = 0;
    
};
