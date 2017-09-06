#include "BlinkableSprite.hpp"

#include "Global.h"
#include "SpritesHelper.hpp"


BlinkableSprite::BlinkableSprite(int8_t inX, int8_t inY, const  unsigned char *inBitMap): AnimatedSprite(inX, inY, inBitMap) {
  counter = 0;
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
    this->setVisibleAmount(SPRITE_ALWAYS_VISIBLE);
    if (counter > (onScreenTime + offScreenTime) ) {
      counter = 0;
      this->setVisibleAmount(SPRITE_NOT_VISIBLE);
    }
  }
}


