#include "Player.hpp"

Player::Player() {
  decksize = DEFAULT_DECK_SIZE;
  DEBUG_PRINTLN("start deck init");
  deck = createNewDeck();
  DEBUG_PRINTLN("deck content: ");
  for (int i = 0; i < decksize; i++) {
    DEBUG_PRINT("index[");
    DEBUG_PRINT(i);
    DEBUG_PRINT("]:");
    DEBUG_PRINTLN(deck[i]->id);
  }
}


const Card* Player::playCard() {
  DEBUG_PRINTLN(decksize);
  for (int i = 0; i < DEFAULT_DECK_SIZE; i++) {

    DEBUG_PRINT(",");
    if ((DEFAULT_DECK_SIZE - decksize) - i == 0) {
      DEBUG_PRINT("[");
    }
    DEBUG_PRINT(deck[i]->id);
    if ((DEFAULT_DECK_SIZE - decksize) - i == 0) {
      DEBUG_PRINT("]");
    }
  }
  DEBUG_PRINTLN("");

  const Card *c = getCurrentCard();
  decksize--;

  return c;
}

void Player::addCard(Card* cards) {

}

const Card* Player::getCurrentCard() {
  return deck[DEFAULT_DECK_SIZE - decksize];
}

