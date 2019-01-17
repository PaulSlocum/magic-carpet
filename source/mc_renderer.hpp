// mc_renderer.hpp
///////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "SDL.h"


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
    SDL_Texture *texture = NULL;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    std::vector<SDL_Texture*> spinnerTextureArray;
    std::vector<bool> spinnerTextureArrayLoaded;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    void loadTexture( const std::string imageFilename, int arrayPosition );

    
    /* TEXTURES
    GLuint spinnerTextureArray[kMaxSpinnerTextures];
    bool spinnerTextureArrayLoaded[kMaxSpinnerTextures];
    GLuint buttonsTextureBG[1];
    GLuint buttonTextureArray[32]; */
};
