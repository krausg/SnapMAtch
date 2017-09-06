#include "AI.hpp"

#include <stdint.h>
#include "Game.hpp"

AI::AI(byte playerNum) : Player(playerNum) {
  AI(EASY_AI, playerNum);
}

AI::AI(byte inDifficulty, byte playerNum) : Player(playerNum) {
  DEBUG_PRINTLN("AI CTOR");
  difficulty = inDifficulty;
  playDelay = 1 * difficulty;
  snapDelay = 1 * difficulty;
  human = false;
}


bool AI::hasPressedPlayCard() {
  return evaluateDelay(&playDelay);
}

bool AI::hasPressedSnapCard() {
  DEBUG_PRINTLN("AI method used");
  switch (difficulty) {
    case EASY_AI:
      return evaluateDelay((snapDelay * 15));
    case NORMAL_AI:
    case DIFFICULT_AI:
    default:
      if (cardMatches) {
        return evaluateDelay(&snapDelay);
      }
  }
}


bool AI::evaluateDelay(uint8_t *delayPointer) {
  if (*delayPointer == 0) {
    *delayPointer = random(1 * difficulty, 5 * difficulty);
    return true;
  }

  *delayPointer -= 1;
  return false;
}
