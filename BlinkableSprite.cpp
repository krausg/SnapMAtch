#include "BlinkableSprite.hpp"

#include "SpritesHelper.hpp"


BlinkableSprite::BlinkableSprite(int8_t inX, int8_t inY, const  unsigned char *inBitMap): AnimatedSprite(inX, inY, NULL) {
  counter = 0;
  bitMapCache = inBitMap;
}


void BlinkableSprite::setOnScreenTime(int inOnScreenTime) {
  onScreenTime = inOnScreenTime;
}
void BlinkableSprite::setOffScreenTime(int inOffScreenTime) {
  offScreenTime = inOffScreenTime;
}

void BlinkableSprite::animate() {
  if (arduboy.everyXFrames(15)) {
    counter++;
  }

  if (counter > offScreenTime) {
    bitmap = bitMapCache;

    if (counter > (onScreenTime + offScreenTime) ) {
      counter = 0;
      bitmap = NULL;
    }
  }
}


