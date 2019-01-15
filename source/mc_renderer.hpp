// mc_renderer.hpp
///////////////////////////////////////////////////////////////////////////////////



class MCApplication;

class MCRenderer
{
public:
    MCRenderer( MCApplication* newApp );
    ~MCRenderer();
    void render();
    
private:
    MCApplication* app;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    int frameCount = 0;
    long long startTimeMSec = 0;
};
