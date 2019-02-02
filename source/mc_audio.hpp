// mc_audio.hpp
/////////////////////////////////////////////////////////////////////

#include <mutex>


class SDL_Thread;


class MCGame;

class MCAudio 
{
public:
    MCAudio( MCGame* newGame );
    ~MCAudio();
    void start();
    void audioCallback( Uint8* stream, const int len );
    void updateFrame();
    // ~  ~  ~  ~  ~  ~  
    void fileLoaderThread();
    
private:
    MCGame* game;
    // ~  ~  ~  ~  ~  ~  
    bool started = false;
    short* binauralAudioBuffer = NULL;
    int binauralAudioBufferLength = 0;
    short* musicAudioBuffer = NULL;
    int musicAudioBufferLength;
    int playbackOffset = 0;
    // ~  ~  ~  ~  ~  ~  
    SDL_Thread *fileThread;
    std::mutex fileThreadMutex;
    int internalAudioPreset = 0;
    volatile bool keepFileThreadRunning = true;
    volatile bool musicFileLoaded = false;
    volatile bool binauralFileLoaded = false;
    volatile int loadedMusicPreset = -1;
    // ~  ~  ~  ~  ~  ~
    short* loadOggAudioFile( const std::string filename, int* fileLength );
};
