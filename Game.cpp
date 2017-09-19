#include "Game.hpp"
#include "BlinkableSprite.hpp"

#include "AI.hpp"

#define PLAYER_ONE 1
#define PLAYER_TWO 2

// change to dynamic var
#define SINGLEPLAYER false

Player* playerOne;
Player* playerTwo;
Player* playersTurn;

const Card* cardPool[MAX_CARD_POOL_SIZE];
byte cardPoolSize = 0;
bool gameOver = false;
bool cardMatches = false;

Sprite gameScreen(0, 0 , gameTest_screen);
Sprite snapBGSprite(0, 0, snapBG_spriteArr);
Sprite snapTXSprite(0, 0, snapTX_spriteArr);
BlinkableSprite pauseToJoin_sprite(82, 55, pauseToJoin_sketch);

void stateGameIntro() {
  gameState = STATE_GAME_TITLE;
}

void stateGamePrepare() {
  DEBUG_PRINTLN("start Prepare for Game");
  gameState = STATE_GAME_PLAY;

  pauseToJoin_sprite.setOnScreenTime(2);
  pauseToJoin_sprite.setOffScreenTime(1);
  snapBGSprite.setVisibleAmount(SPRITE_NOT_VISIBLE);
  snapTXSprite.setVisibleAmount(SPRITE_NOT_VISIBLE);
  DEBUG_PRINTLN(snapBGSprite.isVisible());

  playerOne = new Player(PLAYER_ONE);
  playersTurn = playerOne;
  if (SINGLEPLAYER) {
    DEBUG_PRINTLN("AI STARTED")
    playerTwo = new AI(NORMAL_AI, PLAYER_TWO);
    playerOne->setButtonLayout(A_BUTTON, B_BUTTON, DOWN_BUTTON);

  } else {
    DEBUG_PRINTLN("PLAYER2 STARTED")
    playerTwo = new Player(PLAYER_TWO);
    playerTwo->setButtonLayout(B_BUTTON, A_BUTTON , NULL);
    playerOne->setButtonLayout(LEFT_BUTTON, RIGHT_BUTTON, DOWN_BUTTON);
  }

  DEBUG_PRINT("playerOne deck index 0 test:");
  DEBUG_PRINTLN(playerOne->deck[0]->id);

  DEBUG_PRINTLN("playerOne deck content: ");
  for (int i = 0; i < playerOne->decksize; i++) {
    DEBUG_PRINT("index[");
    DEBUG_PRINT(i);
    DEBUG_PRINT("]:");
    DEBUG_PRINTLN(playerOne->deck[i]->id);
  }

  DEBUG_PRINTLN("finish Prepare for Game");
}

void stateGamePlay() {
  gameOver = (playerOne->decksize <= 0 || playerTwo->decksize <= 0) && cardPoolSize == 0;
  //  if (arduboy.everyXFrames(30)) {
  //    DEBUG_PRINT("gameOver?")
  //    DEBUG_PRINTLN(gameOver ? "yes" : "no");
  //    DEBUG_PRINT("decksizeofplayerOne:");
  //    DEBUG_PRINTLN(playerOne->decksize);
  //  }


  if (!gameOver) {
    if (!playerTwo->human) {
      handleAIActions();
    }
    handleGamePlayerInput();
  }

  drawGameScreen();
  if (gameOver) {
    tinyfont.setCursor(40, 30);
    tinyfont.print("GAME OVER");
    tinyfont.setCursor(40, 35);
    tinyfont.print(( playerOne->decksize > 0 ? "Player 1 won!" : "Player 2 won!"));
    if (arduboy.justPressed(UP_BUTTON)) {
      DEBUG_PRINT("cardpoolsize:");
      DEBUG_PRINTLN(cardPoolSize);
    }
  }
  arduboy.display();


}

void stateGameInfo() {

}



void handleGamePlayerInput() {
  if (playersTurn->hasPressedPlayCard()) {
    if (playersTurn->decksize > 0) {
      cardPool[cardPoolSize++] = playersTurn->playCard();
      if (getNextPlayer()->decksize != 0) {
        playersTurn = getNextPlayer();
      }
    }
    DEBUG_PRINT("NEXTPLAYER: ");
    DEBUG_PRINTLN(playersTurn->playerNum);
  }

  bool cardMatches = cardPoolSize != 0 && cardPoolSize != 1 && cardPool[cardPoolSize - 1]->matches(cardPool[cardPoolSize - 2]);
  if (playerOne->hasPressedSnapCard()) {
    proceedSnap(playerOne, playerTwo, cardMatches);
    snapBGSprite.moveTo(0, 25);
    snapTXSprite.moveTo(5, 31);
    snapBGSprite.setVisibleAmount(30);
    snapTXSprite.setVisibleAmount(30);
  }

  if (playerTwo->hasPressedSnapCard()) {
    proceedSnap(playerTwo, playerOne, cardMatches);
    snapBGSprite.moveTo(91, 25);
    snapTXSprite.moveTo(96, 31);
    snapBGSprite.setVisibleAmount(30);
    snapTXSprite.setVisibleAmount(30);
  }

  if (playerOne->hasPressedOptions() || playerTwo->hasPressedOptions()) {
    gameState = STATE_GAME_TITLE;
  }
}

void handleAIActions() {
  /* if (playersTurn->playerNum == PLAYER_TWO) {
     if (ai.hasPlayedCard()) {
       cardPool[cardPoolSize++] = playerTwo.playCard();
       playersTurn = playerOne;
     }
    }


    bool cardMatches = cardPoolSize != 0 && cardPoolSize != 1 && cardPool[cardPoolSize - 1]->matches(cardPool[cardPoolSize - 2]);
    cardMatches = playerOne->decksize <= 0 || playerTwo.decksize <= 0 ? true : cardMatches;
    if (ai.hasSnapped(cardMatches)) {
     proceedSnap(&playerTwo, playerOne, cardMatches);
     snapBGSprite.moveTo(91, 25);
     snapTXSprite.moveTo(96, 31);
     snapBGSprite.setVisibleAmount(30);
     snapTXSprite.setVisibleAmount(30);
    }

  */
}

void proceedSnap(Player *snappedPlayer, Player *otherPlayer, bool cardMatched) {
  /* DEBUG_PRINT("poolSize: ");
    DEBUG_PRINT(cardPoolSize)
    DEBUG_PRINT(" snappedPlayer::")
    DEBUG_PRINTLN(snappedPlayer->human)
  */

  Player *playerGetCards = cardMatched ? snappedPlayer : otherPlayer;
  for (int i = cardPoolSize - 1; i >= 0; i--) {
    // DEBUG_PRINT("card snapped was:")
    // DEBUG_PRINTLN(cardPool[i]->id)
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
  tinyfont.print(playerOne->decksize);
  tinyfont.setCursor(109, 3);
  tinyfont.print(playerTwo->decksize);
  if (playerOne->decksize > 0) {
    tinyfont.setCursor(10, 30);
    tinyfont.print(playerOne->getCurrentCard()->id);
  }
  if (playerTwo->decksize > 0) {
    tinyfont.setCursor(95, 30);
    tinyfont.print(playerTwo->getCurrentCard()->id);
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

Player* getNextPlayer() {
  return playersTurn->playerNum == PLAYER_ONE ? playerTwo : playerOne;
}

