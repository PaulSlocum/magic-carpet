// mc_renderer.hpp
///////////////////////////////////////////////////////////////////////////////////


class MCApplication;

class MCRenderer
{
public:
    MCRenderer( MCApplication* newApp );
    ~MCRenderer();
    
private:
    MCApplication* app;
    void render();
};
