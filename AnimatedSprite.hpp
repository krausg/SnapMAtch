#ifndef ANIMATED_SPRITE
#define ANIMATED_SPRITE

#include "Sprite.hpp"

struct AnimatedSprite : public  Sprite {
  public:
    AnimatedSprite(int8_t x, int8_t y, const  unsigned char *bitmap);
   virtual void animate() = 0;
};



#endif
