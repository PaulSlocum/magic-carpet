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
    std::map<int, bool> spinnerTextureArrayLoaded;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    void loadTexture( const std::string imageFilename, int arrayPosition );
    void drawSpinner( MCSpinner spinnerToDraw );

    SDL_Surface *softSurface;
    SDL_Renderer *softRenderer;
    
    /* TEXTURES
    GLuint spinnerTextureArray[kMaxSpinnerTextures];
    bool spinnerTextureArrayLoaded[kMaxSpinnerTextures];
    GLuint buttonsTextureBG[1];
    GLuint buttonTextureArray[32]; */
};
