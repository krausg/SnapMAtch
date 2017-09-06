#include "Card.hpp"
#include <stdio.h>


Card::Card() {
}

Card::Card(byte inId) {
  id = inId;
}

bool Card::matches(Card *card) {
  return this->id == card->id;
}

void createNewDeck(const Card* emptyDeck[]) {
  for (int i = 0; i < MAX_CARD_POOL_SIZE; i++) {
    //  DEBUG_PRINT("indexOfPtr:");
    //  DEBUG_PRINT(i);
    //DEBUG_PRINT(" oldValue: ");
    // DEBUG_PRINT(emptyDeck[i]->id);
    //if(i < DEFAULT_DECK_SIZE){
    emptyDeck[i] = &CARDS[i];
    /* }else{
        emptyDeck[i] = &INVALID_CARD;
      }*/

    /*DEBUG_PRINT(" newValue: ");
      DEBUG_PRINT(emptyDeck[i]->id);
      DEBUG_PRINT(" valueOfRealCard: ");
      DEBUG_PRINTLN(CARDS[i].id);
    */
  }
  DEBUG_PRINTLN("startMixingCards");
  for (byte i = DEFAULT_DECK_SIZE - 1; i > 1 ; i--) {
    byte j = random(1, 10);
    //std::swap(swap(newDeck[i],newDeck[j]);
    ptr_swap(emptyDeck, &i, &j);
    DEBUG_PRINT("(now is) to[");
    DEBUG_PRINT(i);
    DEBUG_PRINT("]: ");
    DEBUG_PRINT(emptyDeck[i]->id);
    DEBUG_PRINT("(was in) from[");
    DEBUG_PRINT(j);
    DEBUG_PRINT("]: ");
    DEBUG_PRINTLN(emptyDeck[j]->id);
  }
  DEBUG_PRINTLN("finishedDeckCreation");
}

void ptr_swap(const Card *deck[], byte *indFrom, byte *indTo) {
  const Card *cardFrom = deck[*indFrom];
  deck[*indFrom] = deck[*indTo];
  deck[*indTo] = cardFrom;
  return;
}



