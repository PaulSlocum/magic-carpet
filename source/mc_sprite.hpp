// mc_sprite.hpp
//////////////////////////////////////////////////////////////////////////////////////

#ifndef MC_SPRITE_HPP
#define MC_SPRITE_HPP


enum class SpriteType { SPINNER, BUTTON, BACKGROUND };


// SPINNER STRUCT -----------------------------
// Structure to track of spinning patterns
class MCSprite 
{
public:
    bool active = false;
    int texture = 0;
    float xPosition = 0.5; 
    float yPosition = 0.5;
    float rotationPosition = 0.0;
    float rotationRate = 0.0;
    float size = 1.0;
    float scaleFactor = 1.0;
    SpriteType type = {SpriteType::SPINNER};
    // ~  ~  ~  ~  ~  ~  ~  
    bool isTouching( const float testXCoord, const float testYCoord );
};



#endif

