#include "Game.hpp"
#include "BlinkableSprite.hpp"
#include "AI.hpp"

#define PLAYER_ONE 1
#define PLAYER_TWO 2

//define
#define SINGLEPLAYER false

Player playerOne;
Player playerTwo;
AI ai;

byte playersTurn = PLAYER_ONE;

const Card* cardPool[MAX_CARD_POOL_SIZE];
byte cardPoolSize = 0;

Sprite gameScreen(0, 0 , gameTest_screen);
Sprite snapBGSprite(0, 0, snapBG_spriteArr);
Sprite snapTXSprite(0, 0, snapTX_spriteArr);
BlinkableSprite pauseToJoin_sprite(82, 55, pauseToJoin_sketch);

void stateGameIntro() {
  gameState = STATE_GAME_TITLE;
}

void stateGamePlay() {
  // DEBUG
  if (arduboy.justPressed(UP_BUTTON)) {
    DEBUG_PRINT("current players turn:");
    DEBUG_PRINTLN(playersTurn == 1 ? "player_one" : "player_two");
  }


  boolean gameOver = (playerOne.decksize <= 0 || playerTwo.decksize <= 0) && cardPoolSize == 0;
  if (!gameOver) {
    if (!playerTwo.human) {
      handleAIActions();
    }

    handleGamePlayerInput();
  }

  drawGameScreen();
  if (gameOver) {
    tinyfont.setCursor(50, 30);
    tinyfont.print("GAME OVER");
    //tinyfont.print(( playerOne.decksize > 0 ? "Player 2 won!" : "Player 1 won!"));
    if (arduboy.justPressed(UP_BUTTON)) {
      DEBUG_PRINT("cardpoolsize:");
      DEBUG_PRINTLN(cardPoolSize);
    }
  }
  arduboy.display();


}

void stateGamePrepare() {
  DEBUG_PRINTLN("start Prepare for Game");
  gameState = STATE_GAME_PLAY;

  pauseToJoin_sprite.setOnScreenTime(2);
  pauseToJoin_sprite.setOffScreenTime(1);
  snapBGSprite.setVisibleAmount(SPRITE_NOT_VISIBLE);
  snapTXSprite.setVisibleAmount(SPRITE_NOT_VISIBLE);
  DEBUG_PRINTLN(snapBGSprite.isVisible());

  playerOne = Player();
  playerTwo = Player();
  if (SINGLEPLAYER) {
    ai = AI(NORMAL_AI);
    playerTwo.human = false;
  }

  DEBUG_PRINT("playerOne deck index 0 test:");
  DEBUG_PRINTLN(playerOne.deck[0]->id);
  DEBUG_PRINTLN("finish Prepare for Game");
}

void stateGameInfo() {

}



void handleGamePlayerInput() {
  // check single or multiplayer

  Player *currentPlayer = playersTurn == PLAYER_ONE ? &playerOne : &playerTwo;
  if (currentPlayer->hasPressedPlayCard()) {
    if (playerOne.decksize > 0) {
      cardPool[cardPoolSize++] = playerOne.playCard();
      playersTurn = PLAYER_TWO;
    }
  }else if(currentPlayer->hasPressedSnapCard()){

  //if (arduboy.justPressed(A_BUTTON) && playersTurn == PLAYER_ONE) {

  } else if (arduboy.justPressed(B_BUTTON)) {
    boolean cardMatches = cardPoolSize != 0 && cardPoolSize != 1 && cardPool[cardPoolSize - 1]->matches(cardPool[cardPoolSize - 2]);
    proceedSnap(&playerOne, &playerTwo, cardMatches);
    snapBGSprite.moveTo(0, 25);
    snapTXSprite.moveTo(5, 31);
    snapBGSprite.setVisibleAmount(30);
    snapTXSprite.setVisibleAmount(30);
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


  boolean cardMatches = cardPoolSize != 0 && cardPoolSize != 1 && cardPool[cardPoolSize - 1]->matches(cardPool[cardPoolSize - 2]);
  cardMatches = playerOne.decksize <= 0 || playerTwo.decksize <= 0 ? true : cardMatches;
  if (ai.hasSnapped(cardMatches)) {
    proceedSnap(&playerTwo, &playerOne, cardMatches);
    snapBGSprite.moveTo(91, 25);
    snapTXSprite.moveTo(96, 31);
    snapBGSprite.setVisibleAmount(30);
    snapTXSprite.setVisibleAmount(30);
  }


}

void proceedSnap(Player *snappedPlayer, Player *otherPlayer, boolean cardMatched) {
  DEBUG_PRINT("poolSize: ");
  DEBUG_PRINT(cardPoolSize)
  DEBUG_PRINT(" snappedPlayer::")
  DEBUG_PRINTLN(snappedPlayer->human)


  Player *playerGetCards = cardMatched ? snappedPlayer : otherPlayer;
  for (int i = cardPoolSize - 1; i >= 0; i--) {
    DEBUG_PRINT("card snapped was:")
    DEBUG_PRINTLN(cardPool[i]->id)
    playerGetCards->addCard(cardPool[i]);
    cardPool[i] = NULL;
  }
  cardPoolSize = 0;
}

void drawGameScreen() {
  SpritesHelper::drawOverwrite(gameScreen);

  if (SINGLEPLAYER) {
    SpritesHelper::drawOverwrite(pauseToJoin_sprite);
  }

  // mostly debug
  tinyfont.setCursor(4, 3);
  tinyfont.print(playerOne.decksize);
  tinyfont.setCursor(109, 3);
  tinyfont.print(playerTwo.decksize);
  if (playerOne.decksize > 0) {
    tinyfont.setCursor(10, 30);
    tinyfont.print(playerOne.getCurrentCard()->id);
  }
  if (playerTwo.decksize > 0) {
    tinyfont.setCursor(95, 30);
    tinyfont.print(playerTwo.getCurrentCard()->id);
  }
  if (cardPoolSize > 0) {
    tinyfont.setCursor(35, 30);
    tinyfont.print(cardPool[cardPoolSize - 1]->id);
  }
  if (cardPoolSize > 1) {
    tinyfont.setCursor(65, 30);
    tinyfont.print(cardPool[cardPoolSize - 2]->id);
  }

  SpritesHelper::drawOverwrite(snapBGSprite);
  SpritesHelper::drawOverwrite(snapTXSprite);


}

