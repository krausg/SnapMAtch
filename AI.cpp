#include "AI.hpp"

#include <stdint.h>
#include "Game.hpp"

AI::AI(byte playerNum) : AI(EASY_AI, playerNum) { }

AI::AI(byte inDifficulty, byte playerNum) : Player(playerNum) {
  difficulty = inDifficulty;
  playDelay = 1 * difficulty;
  snapDelay = 1 * difficulty;
  human = false;
}


bool AI::hasPressedPlayCard() {
  return evaluateDelay(&playDelay);
}

bool AI::hasPressedSnapCard() {
  switch (difficulty) {
    case EASY_AI: {
        int aaa = random(1, 20);
        if (aaa == 1)  {
          return true;
        } else {
          return cardMatches && evaluateDelay(&snapDelay);
        }
      }
    case NORMAL_AI:
    case DIFFICULT_AI:
    default: {
        bool tt = cardMatches && evaluateDelay(&snapDelay);
        DEBUG_PRINT("DEBUG RANDOM: ");
        DEBUG_PRINTLN(tt);
        return tt;
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
