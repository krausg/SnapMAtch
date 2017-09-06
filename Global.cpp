#include "Global.h"

Arduboy2Base arduboy;
Sprites sprites;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());
byte gameState = STATE_GAME_INTRO;
