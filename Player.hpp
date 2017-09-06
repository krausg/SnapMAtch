
#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "Global.h"
#include "Card.hpp"


class Player {
  public:
    Player(byte inPlayerNum);
    Player();
    const Card * playCard();
    virtual boolean hasPressedPlayCard();
    virtual boolean hasPressedSnapCard();
    virtual boolean hasPressedOptions();
    void setButtonLayout(byte playButton, byte snapButton, byte optionButton);
    const Card* getCurrentCard();
    void addCard(Card* cards);
    byte playerNum;
    const Card* deck[MAX_CARD_POOL_SIZE];
    int decksize;
    bool human;
  private:
    byte playButton, snapButton, optionButton;
};

#endif
