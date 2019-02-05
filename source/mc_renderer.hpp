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
};
