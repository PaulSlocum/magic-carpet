// mc_renderer.hpp
///////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>
#include "SDL.h"
#include "mc_sprite.hpp"



class MCAppState;

class MCRenderer
{
public:
    MCRenderer( MCAppState* newState );
    ~MCRenderer();
    void start();
    void render();
    void loadTextures();
    
private:
    MCAppState* state;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    int frameCount = 0;
    long long startTimeMSec = 0;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    SDL_Renderer *SDLRenderer = NULL;
    SDL_Window *window = NULL;
    int screenWidth = 0;
    int screenHeight = 0;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    std::map<int, SDL_Texture*> spinnerTextureArray;
    //std::map<int, SDL_Texture*> buttonTextureArray;
    //SDL_Texture* backgroundTexture;
    std::map<int, bool> spinnerTextureArrayLoaded;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    SDL_Texture* loadJpegTexture( const std::string imageFilename );
    void drawSpinner( const MCSprite spinner );
    // ~  ~  ~  ~  ~  ~  ~  ~  
    // DEBUG - TRYING TO IMPLEMENT RENDER TARGET
    //SDL_Surface *softSurface;
    //SDL_Renderer *softRenderer;
};
