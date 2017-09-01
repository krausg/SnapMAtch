#include "Player.hpp"


Player::Player() {
  decksize = DEFAULT_DECK_SIZE;
  DEBUG_PRINTLN("start deck init");
  createNewDeck(deck);
  DEBUG_PRINTLN("deck content: ");
  for (int i = 0; i < decksize; i++) {
    DEBUG_PRINT("index[");
    DEBUG_PRINT(i);
    DEBUG_PRINT("]:");
    DEBUG_PRINTLN(deck[i]->id);
  }
}


const Card* Player::playCard() {
  DEBUG_PRINT(human == 0 ? "cpu " : "human ");
  DEBUG_PRINT("with decksize: ");
  DEBUG_PRINT(decksize);
  DEBUG_PRINT(" and content: (");
  for (int i = 0; i < decksize; i++) {

    if (i > 0) {
      DEBUG_PRINT(",");
    }
    if ((DEFAULT_DECK_SIZE - decksize) - i == 0) {
      DEBUG_PRINT("[");
    }
    DEBUG_PRINT(deck[i]->id);
    if ((DEFAULT_DECK_SIZE - decksize) - i == 0) {
      DEBUG_PRINT("]");
    }
  }
  DEBUG_PRINTLN(")");

  const Card *c = getCurrentCard();
  decksize--;

  return c;
}

void Player::addCard(Card* card) {
  //  deck[decksize] = card;
  for (int i = decksize - 1; i >= 0 ; i--) {
    deck[i + 1] = deck[i];
  }
  deck[0] = card;
  decksize++;
}

const Card* Player::getCurrentCard() {
  if (arduboy.justPressed(LEFT_BUTTON)) {
    DEBUG_PRINT("player: ")
    DEBUG_PRINT(human == 0 ? "cpu " : "human ")
    DEBUG_PRINT("current card id: ")
    DEBUG_PRINT(deck[decksize - 1]->id)
    DEBUG_PRINT(" index: ")
    DEBUG_PRINTLN(decksize - 1);
  }
  return deck[decksize - 1];
}

boolean Player::hasPressedPlayCard() {
  return arduboy.justPressed(A_BUTTON);
}

boolean Player::hasPressedSnapCard() {

}

boolean Player::hasPressedOptions() {

}

