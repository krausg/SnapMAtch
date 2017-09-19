#include "Card.hpp"
#include <stdio.h>


Card::Card() {
  x = 10;
  y = 10;
  x2 = x + CARD_WIDTH;
  y2 = y + CARD_HEIGHT;
  cord = new int8_t[MAX_EDGES];
  DEBUG_PRINTLN("x: " + toString(x) + " y:" + toString(y) + " x2: " + toString("x2"));
//  // line: left right up
  cord[0] = x + ROUND_EDGE_SIZE;
  cord[16] = y;
//  // line: left right up
  cord[1] = x2 - ROUND_EDGE_SIZE;
  cord[17] = y;
//  // line: left right down
//  cord[2] = x + ROUND_EDGE_SIZE;
//  cord[18] = y2;
//  // line: right left down
//  cord[3] = x2 - ROUND_EDGE_SIZE;
//  cord[19] = y2;
//  // line: left left up
//  cord[4] = x;
//  cord[20] = y + ROUND_EDGE_SIZE;
//  // line: left left down
//  cord[5] = x;
//  cord[21] = y2 - ROUND_EDGE_SIZE;
//  // line: right right up
//  cord[6] = x2;
//  cord[22] = y + ROUND_EDGE_SIZE;
//  // line: right right down
//  cord[7] = x2;
//  cord[23] = y2 - ROUND_EDGE_SIZE;
//  // quarter circle left left up
//  cord[8] = x + ROUND_EDGE_SIZE - 1;
//  cord[24] = y;
//  // quarter circle left right up
//  cord[9] = x;
//  cord[25] = y + ROUND_EDGE_SIZE - 1;
//  // quarter circle right left up
//  cord[10] = x2 - ROUND_EDGE_SIZE + 1;
//  cord[26] = y;
//  // quarter circle right right up
//  cord[11] = x2;
//  cord[27] = y + ROUND_EDGE_SIZE - 1;
//  // quarter circle left left down
//  cord[12] = x;
//  cord[28] = y2 - ROUND_EDGE_SIZE + 1;
//  // quarter circle left right down
//  cord[13] = x + ROUND_EDGE_SIZE - 1;
//  cord[29] = y2;
//  // quarter circle right left down
//  cord[14] = x2 - ROUND_EDGE_SIZE + 1;
//  cord[30] = y2;
//  // quarter circle right right down
//  cord[15] = x2;
//  cord[31] = y2 - ROUND_EDGE_SIZE + 1;
}

Card::Card(byte inId) : Card() {
  id = inId;
}

bool Card::matches(Card *card) {
  return this->id == card->id;
}

void Card::draw() {
  for (int i = 0; i < MAX_EDGES; i += 2) {
    //arduboy.drawLine(cord[i], cord[i + CORD_Y_OFFSET], cord[i + 1], cord[i + 1 + CORD_Y_OFFSET]);
  }
}



void Card::transform(int8_t* tMatrix) {

}


void createNewDeck(const Card* emptyDeck[]) {
  for (int i = 0; i < MAX_CARD_POOL_SIZE; i++) {
    emptyDeck[i] = &CARDS[i];
  }

  for (byte i = DEFAULT_DECK_SIZE - 1; i > 1 ; i--) {
    byte j = random(1, 10);
    const Card *cardFrom = emptyDeck[i];
    emptyDeck[i] = emptyDeck[j];
    emptyDeck[j] = cardFrom;
  }
}


