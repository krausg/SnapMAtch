#include "AI.hpp"

#include <stdint.h>

AI::AI() {
  AI(EASY_AI);

}

AI::AI(byte inDifficulty) {
  difficulty = inDifficulty;
  playDelay = 0 * difficulty;
  snapDelay = 0 * difficulty;
}

bool AI::hasPlayedCard() {
  return evaluateDelay(playDelay);
}

bool AI::hasSnapped(bool cardMatches) {
  if (difficulty == EASY_AI || cardMatches) {
    return evaluateDelay(snapDelay);
  }
}


bool AI::evaluateDelay(uint8_t &delayPointer) {
  if (delayPointer == 0) {
    delayPointer = random(1 * difficulty, 2 * difficulty);
    return true;
  }

  delayPointer--;
  return false;
}
