#ifndef CARD_HEADER
#define CARD_HEADER

#include "Global.h"

#define INVALID_CARD_ID   255
#define INVALID_CARD      Card(INVALID_CARD_ID)


struct Card {
    byte id;
    Card();
    Card(byte id);
    boolean matches(Card *);
};


const PROGMEM Card CARDS[] = { Card(1), Card(2), Card(3), Card(4), Card(5), Card(6), Card(7) , Card(8), Card(9), Card(10) } ;

void createNewDeck(const Card* emptyDeck[]);
void ptr_swap(const Card *deck[], byte *indFrom, byte *indTo);

#endif
