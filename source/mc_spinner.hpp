// mc_spinner.hpp
//////////////////////////////////////////////////////////////////////////////////////

#ifndef MC_SPINNER_HPP
#define MC_SPINNER_HPP





// SPINNER STRUCT -----------------------------
// Structure to track of spinning patterns
class MCSpinner 
{
public:
    bool active = false;
    int texture = 0;
    float xPosition = 0.5; 
    float yPosition = 0.5;
    float rotationPosition = 0.0;
    float rotationRate = 0.0;
    float size = 1.0;
    // ~  ~  ~  ~  ~  ~  ~  
    bool isTouching();
};



#endif

