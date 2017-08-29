#include "AI.hpp"

#include <stdint.h>

AI::AI() {
  playDelay = 0;
  snapDelay = 0;
}

bool AI::hasPlayedCard() {
  return evaluateDelay(playDelay);
}

bool AI::hasSnapped(const Card *first,const  Card *second) {
  return evaluateDelay(snapDelay);
}


bool AI::evaluateDelay(uint8_t &delayPointer) {
  if (delayPointer == 0) {
    delayPointer = random(10, 40);
    return true;
  }

  delayPointer--;
  return false;
}
