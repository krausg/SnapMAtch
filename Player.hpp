
#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "Global.h"
#include "Card.hpp"


class Player {
  public:
    Player();
    const Card * playCard();
    const Card* getCurrentCard();
    
    void addCard(Card* cards);
    

    const Card** deck;
    int decksize;
    bool human;
};

#endif
