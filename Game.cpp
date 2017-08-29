#include "Game.hpp"
#include "BlinkableSprite.hpp"
#include "AI.hpp"

#define PLAYER_ONE 1
#define PLAYER_TWO 2

Player playerOne;
Player playerTwo;
AI ai;

byte playersTurn = PLAYER_ONE;

const Card* cardPool[MAX_CARD_POOL_SIZE];
byte cardPoolSize = 0;

Sprite gameScreen(0, 0 , gameTest_screen);
BlinkableSprite pauseToJoin_sprite(82, 1, pauseToJoin_sketch);

void stateGameIntro() {
  gameState = STATE_GAME_TITLE;
}

void stateGamePlay() {
  drawGameScreen();

  if (!playerTwo.human) {
    handleAIActions();
  }

  handleGamePlayerInput();
}

void stateGamePrepare() {
  DEBUG_PRINTLN("start Prepare for Game");
  gameState = STATE_GAME_PLAY;

  pauseToJoin_sprite.setOnScreenTime(2);
  pauseToJoin_sprite.setOffScreenTime(1);

  //playerOne = Player();
  //playerTwo = Player();
  //ai = AI();

  playerOne.human = true;
  playerTwo.human = false;
  DEBUG_PRINT("playerOne deck index 0 test:");
  DEBUG_PRINTLN(playerOne.deck[0]->id);
  DEBUG_PRINTLN("finish Prepare for Game");
}

void stateGameInfo() {

}



void handleGamePlayerInput() {
  // check single or multiplayer
  if (arduboy.justPressed(A_BUTTON) && playersTurn == PLAYER_ONE) {
    if (playerOne.decksize > 0) {
      cardPool[cardPoolSize++] = playerOne.playCard();
      playersTurn = PLAYER_TWO;
    }
  } else if (arduboy.justPressed(B_BUTTON)) {
    //snapping
  }

  if (arduboy.justPressed(DOWN_BUTTON)) {
    gameState = STATE_GAME_TITLE;
  }
}

void handleAIActions() {
  if (playersTurn == PLAYER_TWO) {
    if (ai.hasPlayedCard()) {
      cardPool[cardPoolSize++] = playerTwo.playCard();
      playersTurn = PLAYER_ONE;
    }
  }

  if (ai.hasSnapped(cardPool[cardPoolSize - 1], cardPool[cardPoolSize - 2])) {
    evaluateSnap(cardPool[cardPoolSize - 1], cardPool[cardPoolSize - 2]);
  }

}

void evaluateSnap(const Card* first, const Card* second) {

}

void drawGameScreen() {
  if (arduboy.justPressed(B_BUTTON)) {
    DEBUG_PRINT("testTwo:");
    DEBUG_PRINTLN(playerOne.deck[0]->id);
  }

  SpritesHelper::drawOverwrite(gameScreen);

  // check if singleplayer
  SpritesHelper::drawSelfMasked(pauseToJoin_sprite);

  // mostly debug
  tinyfont.setCursor(4, 3);
  tinyfont.print(playerOne.decksize);
  tinyfont.setCursor(10, 30);
  tinyfont.print(playerOne.getCurrentCard()->id);
  tinyfont.setCursor(95, 30);
  tinyfont.print(playerTwo.getCurrentCard()->id);
  tinyfont.setCursor(35, 30);
  tinyfont.print(cardPool[cardPoolSize - 1]->id);
  tinyfont.setCursor(65, 30);
  tinyfont.print(cardPool[cardPoolSize - 2]->id);
  arduboy.display();
}
