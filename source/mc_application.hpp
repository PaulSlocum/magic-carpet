// mc_application.hpp
//////////////////////////////////////////////////////////////////////////////

#ifndef MC_APPLICATION_HPP
#define MC_APPLICATION_HPP

#include <map>
#include "mc_sprite.hpp"
#include "mc_game.hpp"


const int FRAMES_PER_SECOND = 60.0;


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
    
private:
    void runLoop();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    MCRenderer* renderer;
    MCGame* gameController;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    bool vsyncEnabled = false;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    bool isQuitting = false;
    bool appStarted = false;
};


#endif
