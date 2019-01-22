// mc_renderer.hpp
///////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>
#include "SDL.h"
#include "mc_spinner.hpp"



class MCApplication;

class MCRenderer
{
public:
    MCRenderer( MCApplication* newApp );
    ~MCRenderer();
    void render();
    void loadTextures();
    
private:
    MCApplication* app;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    int frameCount = 0;
    long long startTimeMSec = 0;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    std::map<int, SDL_Texture*> spinnerTextureArray;
    std::map<int, SDL_Texture*> buttonTextureArray;
    SDL_Texture* backgroundTexture;
    std::map<int, bool> spinnerTextureArrayLoaded;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    SDL_Texture* loadJpegTexture( const std::string imageFilename );
    void drawSpinner( const MCSpinner spinner );
    // ~  ~  ~  ~  ~  ~  ~  ~  
    // DEBUG - TRYING TO IMPLEMENT RENDER TARGET
    //SDL_Surface *softSurface;
    //SDL_Renderer *softRenderer;
};
