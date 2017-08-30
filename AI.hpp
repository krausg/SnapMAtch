#ifndef AI_HEADER
#define AI_HEADER

#include "Card.hpp"

#define EASY_AI 10
#define NORMAL_AI 5
#define DIFFICULT_AI 1

class AI {
  public:
    AI();
    AI(byte difficulty);
    bool hasPlayedCard();
    bool hasSnapped(bool cardMatches);
  private:
    uint8_t difficulty;
    uint8_t playDelay;
    uint8_t snapDelay;
    bool evaluateDelay(uint8_t &delayPointer);
};





#endif
