// mc_renderer.hpp
///////////////////////////////////////////////////////////////////////////////////


#include <map>
#include "SDL.h"


class MCSprite;


class MCApplication;

class MCRenderer
{
public:
    MCRenderer( MCApplication* newApp );
    ~MCRenderer();
    void start();
    void stop();
    void render();
    void presentBuffer();
    void loadTextures();
    void loadJpegTexture( const std::string imageFilename, int textureNumber );
    
private:
    MCApplication* app;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    SDL_Renderer *sdlRenderer = NULL;
    SDL_Window *window = NULL;
    int screenWidth = 0;
    int screenHeight = 0;
    // ~  ~  ~  ~  ~  ~  ~  ~
    bool rendererStarted = false;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    std::map<int, SDL_Texture*> spinnerTextureArray;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    void drawSprite( const MCSprite spinner );
    // ~  ~  ~  ~  ~  ~  ~  ~  
};
