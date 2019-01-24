// mc_touch.hpp
//////////////////////////////////////////////////////////////////////////////////////

#ifndef MC_TOUCH_HPP
#define MC_TOUCH_HPP


class MCTouch
{
public:
    //long frameCountOfLastRefresh;
    //UITouch* touch;
    //int touchID;
    float x = 0.0;
    float y = 0.0;
    float xStart = 0.0;
    float yStart = 0.0;
    //float fade; // TBI
    // ~  ~  ~  ~  ~  ~  ~  
    float moveDistance();
}; //*/




#endif

