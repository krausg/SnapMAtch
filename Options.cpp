#include "Options.hpp"

#include "Sprite.hpp"

Sprite optionScreen(0,0,optionsTest_screen);

void stateOptions(){
  drawOptionScreen();
  handleOptionUserInput();

  
}

void drawOptionScreen(){
  arduboy.clear();
  SpritesHelper::drawOverwrite(optionScreen);
  arduboy.display();
}
  
void handleOptionUserInput(){
  if(arduboy.justPressed(B_BUTTON)){
    gameState=STATE_GAME_PLAY;
  }
}

