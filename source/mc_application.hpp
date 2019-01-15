// mc_application.hpp
//
// THE TOP LEVEL CLASS FOR THE MAGIC CARPET APPLICATION
//////////////////////////////////////////////////////////////////////////////

#ifndef MC_APPLICATION_HPP
#define MC_APPLICATION_HPP

class MCRenderer;


class MCApplication
{
public:
    void start();
    void stop();
    MCApplication();
    ~MCApplication();
private:
    void runLoop();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    MCRenderer* renderer;
};


#endif
