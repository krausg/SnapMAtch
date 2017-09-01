#include "AI.hpp"

#include <stdint.h>

AI::AI() {
  AI(EASY_AI);

}

AI::AI(byte inDifficulty) {
  difficulty = inDifficulty;
  playDelay = 1 * difficulty;
  snapDelay = 1 * difficulty;
}

bool AI::hasPlayedCard() {
  if (arduboy.justPressed(UP_BUTTON)) {
    DEBUG_PRINT("play delay: ");
    DEBUG_PRINTLN(playDelay);
  }
  return evaluateDelay(&playDelay);
}

bool AI::hasSnapped(bool cardMatches) {
  if (difficulty == EASY_AI || cardMatches) {
    return evaluateDelay(&snapDelay);
  }
}


bool AI::evaluateDelay(uint8_t *delayPointer) {

  if (*delayPointer == 0) {
    *delayPointer = random(1 * difficulty, 5 * difficulty);
    return true;
  }

  *delayPointer-=1;
  return false;
}
