#ifndef SPRITE_HEADER
#define SPRITE_HEADER


#include <Arduboy2.h>

struct Sprite {
  public:
    Sprite(int8_t x, int8_t y, const unsigned char *bitmap);
    void moveTo(int8_t x, int8_t y);
    void setVisibleAmount(int8_t inVisibleAmount);
    boolean isVisible();
    void nextFrame();
    int8_t visibleAmount;
    int8_t x, y, frame;
    const unsigned char *bitmap;


};


#endif
