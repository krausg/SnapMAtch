#include "Sprite.hpp"

Sprite::Sprite(int8_t inX, int8_t inY, const  unsigned char *inBitMap) {
  x = inX;
  y = inY;
  bitmap  = inBitMap;
  visibleAmount = -1;
}

void Sprite::moveTo(int8_t moveX, int8_t moveY) {
  x = moveX;
  y = moveY;
}

void Sprite::nextFrame() {
  if (visibleAmount > 0) {
    visibleAmount-=1;
  }
}

void Sprite::setVisibleAmount(int8_t inVisibleAmount) {
  visibleAmount = inVisibleAmount;
}

boolean  Sprite::isVisible() {
  return visibleAmount != 0;
}

