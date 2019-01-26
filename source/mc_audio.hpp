// mc_audio.hpp
/////////////////////////////////////////////////////////////////////


class SDL_Thread;


class MCGame;

class MCAudio 
{
public:
    MCAudio( MCGame* newGame );
    ~MCAudio();
    void start();
    void callback( Uint8* stream, int len );
    // ~  ~  ~  ~  ~  ~  
    void fileLoaderThread();
    
private:
    MCGame* game;
    // ~  ~  ~  ~  ~  ~  
    bool started = false;
    short* audioDecodeBuffer;
    long audioFileLength = 0;
    long playbackOffset = 0;
    // ~  ~  ~  ~  ~  ~  
    SDL_Thread *fileThread;
    volatile bool keepFileThreadRunning = true;
    volatile bool audioFilesLoaded = false;
    
};
