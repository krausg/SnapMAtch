#ifndef CARD_HEADER
#define CARD_HEADER

#include "Global.h"

#define INVALID_CARD_ID   255
#define INVALID_CARD      Card(INVALID_CARD_ID)


#define CARD_WIDTH        15
#define CARD_HEIGHT       20
#define MAX_EDGES         32
#define ROUND_EDGE_SIZE   3
#define CORD_Y_OFFSET     16

struct Card {
  public:
    byte id;
    Card();
    Card(byte id);
    bool matches(Card *);
    void draw();
    void transform(int8_t* tMatrix);
  private:
    // put in new class
    int8_t x, y, x2, y2;
    int8_t* cord;
};


const PROGMEM Card CARDS[] = { Card(1), Card(2), Card(3), Card(4), Card(5), Card(6), Card(7) , Card(8), Card(9), Card(10) } ;

void createNewDeck(const Card* emptyDeck[]);

#endif
