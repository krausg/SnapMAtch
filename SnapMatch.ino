#include "Global.h"
#include "Title.hpp"
#include "Game.hpp"
#include "Options.hpp"

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM mainGameLoop[] =
{
  stateGameIntro,
  stateGameTitle,
  stateTitlePlay,
  stateOptions,
  stateTitleInfo,
  stateGamePrepare,
  stateGamePlay
  //stateGame
};


void setup() {
  DEBUG_PREPARE(9600)
  randomSeed(analogRead(0));
  
  /*arduboy.boot();
    arduboy.blank();*/
  arduboy.begin();

  

  arduboy.setFrameRate(MAX_FPS);
}

void loop() {
  if ((!arduboy.nextFrame())) {
    return;
  }
  arduboy.pollButtons();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  DEBUG_FPS_COUNTER(arduboy);
}
