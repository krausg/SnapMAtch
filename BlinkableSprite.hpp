#ifndef BLINKABLE_SPRITE_HEADER
#define BLINKABLE_SPRITE_HEADER

#include "AnimatedSprite.hpp"

extern Arduboy2Base arduboy;

class BlinkableSprite : public AnimatedSprite {
  public:
    BlinkableSprite(int8_t inX, int8_t inY, const  unsigned char *inBitMap);
    void setOnScreenTime(int onScreenTime);
    void setOffScreenTime(int offScreenTime);
    void animate();
  private:
    byte offScreenTime;
    byte onScreenTime;
    byte counter;
};




#endif
