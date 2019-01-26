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
    short* binuaralAudioBuffer = NULL;
    int binuaralAudioBufferLength = 0;
    short* musicAudioBuffer = NULL;
    int musicAudioBufferLength;
    int playbackOffset = 0;
    // ~  ~  ~  ~  ~  ~  
    SDL_Thread *fileThread;
    volatile bool keepFileThreadRunning = true;
    volatile bool musicFileLoaded = false;
    volatile bool binuaralFileLoaded = false;
    volatile int loadedMusicPreset = -1;
    // ~  ~  ~  ~  ~  ~
    short* loadAudioFile( std::string filename, int* fileLength );
};
