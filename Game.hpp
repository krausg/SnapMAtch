#ifndef SNAPMATCH_HEADER
#define SNAPMATCH_HEADER

#include "Global.h"
#include "Player.hpp"

void stateGameIntro();
void stateGamePrepare();
void stateGamePlay();
void stateGameInfo();

void handleGamePlayerInput();
void handleAIActions();
void drawGameScreen();
void evaluateSnap(const Card* first, const Card* second);


extern const Card *cardPool[];
extern byte cardPoolSize;


#endif
