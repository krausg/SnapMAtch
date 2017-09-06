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
void proceedSnap(Player *snappedPlayer, Player *otherPlayer, bool cardMatched) ;
Player* getNextPlayer();


extern const Card *cardPool[];
extern byte cardPoolSize;
extern bool gameOver;
extern bool cardMatches;

#endif
