// mc_application.hpp
//////////////////////////////////////////////////////////////////////////////

#ifndef MC_APPLICATION_HPP
#define MC_APPLICATION_HPP

#include <map>
#include "mc_sprite.hpp"
#include "mc_game.hpp"



class MCRenderer;
class MCGame;


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
class MCApplication
{
public:
    MCApplication();
    ~MCApplication();
    void start();
    void stop();
    // ~  ~  ~  ~  ~  ~  ~  ~
    RGBColor backgroundColor;
    std::map<int,MCSprite> spriteRenderList;
    void loadJpegTexture( const std::string filename, const int textureNumber );
    
private:
    void runLoop();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    MCRenderer* renderer;
    MCGame* gameController;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    bool vsyncEnabled = false;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    volatile bool isQuitting = false;
    bool appStarted = false;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    const int FRAMES_PER_SECOND = 60.0; 
};


#endif
