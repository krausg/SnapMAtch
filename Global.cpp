#include "Global.h"

Arduboy2Base arduboy;
Sprites sprites;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());
byte gameState = STATE_GAME_INTRO;

String toString(int num) {
  char numstr[21];
  return itoa(num, numstr, 10);
}

String toString(int num, int minimum) {
  String str = toString(num);
  while (str.length() < minimum)str = '0' + str;
  return str;
}

