// mc_renderer.hpp
///////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>
#include "SDL.h"
#include "mc_sprite.hpp"



//class MCAppState;
class MCApplication;

class MCRenderer
{
public:
    MCRenderer( MCApplication* newApp );
    ~MCRenderer();
    void start();
    void render();
    void loadTextures();
    
private:
    MCApplication* app;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    SDL_Renderer *SDLRenderer = NULL;
    SDL_Window *window = NULL;
    int screenWidth = 0;
    int screenHeight = 0;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    std::map<int, SDL_Texture*> spinnerTextureArray;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    SDL_Texture* loadJpegTexture( const std::string imageFilename );
    void drawSprite( const MCSprite spinner );
    // ~  ~  ~  ~  ~  ~  ~  ~  
    // DEBUG - TRYING TO IMPLEMENT RENDER TARGET
    //SDL_Surface *softSurface;
    //SDL_Renderer *softRenderer;
};
