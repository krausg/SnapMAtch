#include "Sprite.hpp"

Sprite::Sprite(int8_t inX, int8_t inY, const  unsigned char *inBitMap){
  x = inX;
  y = inY;
  bitmap  = inBitMap;
}

void Sprite::moveTo(int8_t moveX, int8_t moveY){
  x = moveX;
  y = moveY;
}

