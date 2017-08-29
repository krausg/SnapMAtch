#include "Card.hpp"
#include <stdio.h>


Card::Card() {
}

Card::Card(byte inId) {
  id = inId;
}

const Card **createNewDeck() {
  //    -- To shuffle an array a of n elements (indices 0..n-1):
  //  for i from n−1 downto 1 do
  //       j ← random integer such that 0 ≤ j ≤ i
  //       exchange a[j] and a[i]

  const Card* newDeck[DEFAULT_DECK_SIZE];
  DEBUG_PRINTLN("startDeckCreation");

  for (int i = 0; i < DEFAULT_DECK_SIZE; i++) {
    DEBUG_PRINT("indexOfPtr:");
    DEBUG_PRINT(i);
   // DEBUG_PRINT(" addr: ");
   // DEBUG_PRINT(newDeck[i]);
    DEBUG_PRINT(" oldValue: ");
    DEBUG_PRINT(newDeck[i]->id);
    newDeck[i] = &CARDS[i];
    DEBUG_PRINT(" newValue: ");
    DEBUG_PRINT(newDeck[i]->id);
    DEBUG_PRINT(" valueOfRealCard: ");
    DEBUG_PRINTLN(CARDS[i].id);

  }
  DEBUG_PRINTLN("startMixingCards");
  for (byte i = DEFAULT_DECK_SIZE - 1; i > 1 ; i--) {
    byte j = random(1, 10);
    //std::swap(swap(newDeck[i],newDeck[j]);
    ptr_swap(newDeck,&i,&j);
    DEBUG_PRINT("(now is) to[");
    DEBUG_PRINT(i);
    DEBUG_PRINT("]: ");
    DEBUG_PRINT(newDeck[i]->id);
    DEBUG_PRINT("(was in) from[");
    DEBUG_PRINT(j);
    DEBUG_PRINT("]: ");
    DEBUG_PRINTLN(newDeck[j]->id);
  }
  DEBUG_PRINTLN("finishedDeckCreation");


  return newDeck;
}

void ptr_swap(const Card *deck[], byte *indFrom, byte *indTo) {
  const Card *cardFrom = deck[*indFrom];
  deck[*indFrom] = deck[*indTo];
  deck[*indTo] = cardFrom;
  return;
}

