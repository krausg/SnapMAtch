#include "Title.hpp"
#include "Player.hpp"

#include "BlinkableSprite.hpp"

BlinkableSprite mainSelected_sprite(73, 28, mainTest_selected);
byte selectedMenuItem = STATE_TITLE_PLAY;

void stateGameTitle() {
  mainSelected_sprite.setOnScreenTime(2);
  mainSelected_sprite.setOffScreenTime(1);
  handleTitleUserInput();
  drawTitleScreen();
}

void stateTitlePlay() {
  // in case of singleplayer
  gameState = STATE_GAME_PREPARE;
}
void stateTitleOptions() {

}
void stateTitleInfo() {

}



void handleTitleUserInput() {
  if (arduboy.justPressed(DOWN_BUTTON) && selectedMenuItem < STATE_TITLE_INFO) {
    selectedMenuItem++;
  } else if (arduboy.justPressed(UP_BUTTON) && selectedMenuItem > STATE_TITLE_PLAY) {
    selectedMenuItem--;
  }

  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) {
    gameState = selectedMenuItem;
  }
}


void drawTitleScreen() {
  sprites.drawOverwrite(0, 0, mainTest, 0);
  switch (selectedMenuItem) {
    case STATE_TITLE_PLAY:
      mainSelected_sprite.moveTo(73, 28);
      break;
    case STATE_OPTIONS:
      mainSelected_sprite.moveTo(73, 36);
      break;
    case STATE_TITLE_INFO:
      mainSelected_sprite.moveTo(73, 43);
      break;
  }

  SpritesHelper::drawSelfMasked(mainSelected_sprite);

  arduboy.display();
}


