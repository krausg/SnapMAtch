#include "Global.h"
#include "Title.hpp"
#include "Game.hpp"
#include "Options.hpp"
#include <stdio.h>


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


void rotate_point(Point *p, int cx, int cy, double angle) {
  float radians = (2 * 3.1416 * angle) / 360;

  float c = (float)cos(radians);
  float s = (float)sin(radians);

  // translate point back to origin:
  p->x -= cx;
  p->y -= cy;

  // rotate point
  float xnew = p->x * c - p->y * s;
  float ynew = p->x * s + p->y * c;

  // translate point back:
  p->x = xnew + cx;
  p->y = ynew + cy;
}

void drawCard(int x, int y, int w, int h, double angle) {
  const int r = 3;
  const int x2 = x + w;
  const int y2 = y + h - 1;

  const int xcenter = x + (w / 2);
  const int ycenter = y + (h / 2);



  Point center = { .x = x + (w / 2), .y = y + (h / 2) };

  // links oben
  Point llup = { .x = double(x), .y = double(y + r) };
  Point lrup = { .x = double(x + r), .y = double(y) };
  //lrup.x *= 1.30;
  // rechts oben
  Point rrup = { .x = double(x2), .y = double(y + r) };
  //rrup.x *= 1.30;
  Point rlup = { .x = double(x2 - r), .y = double(y) };
  //rlup.x *= 1.30;
  //links unten
  Point lrdp = { .x = double(x + r), .y = double(y2) };
  Point lldp = { .x = double(x), .y = double(y2 - r) };
  // rechts unten
  Point rldp = { .x = double(x2 - r), .y = double(y2) };
  Point rrlp = { .x = double(x2), .y = double(y2 - r) };

  rotate_line(&lrup, &rlup, &center, &angle);
  arduboy.drawLine(lrup.x, lrup.y, rlup.x, rlup.y);

  rotate_line(&lrdp, &rldp, &center, &angle);
  arduboy.drawLine(lrdp.x, lrdp.y, rldp.x, rldp.y);

  rotate_line(&llup, &lldp, &center, &angle);
  arduboy.drawLine(llup.x, llup.y , lldp.x, lldp.y);

  rotate_line(&rrup, &rrlp, &center, &angle);
  arduboy.drawLine(rrup.x, rrup.y, rrlp.x, rrlp.y);

  // --------------
  // circle points
  // --------------

  // corner links oben
  Point cllup = { .x = double(x + r - 1), .y = double(y) };
  //cllup.x *= 1.30;
  Point clrup = { .x = double(x), .y = double(y + r - 1) };
  //clrup.x *= 1.30;
  // corner rechts oben
  Point crlup = { .x = double(x2 - r + 1), .y = double(y) };
  //crlup.x *= 1.30;
  Point crrup = { .x = double(x2), .y = double(y + r - 1) };
  //crrup.x *= 1.30;
  // corner links unten
  Point clldp = { .x = double(x), .y = double(y2 - r + 1) };
  Point clrdp = { .x = double(x + r - 1), .y = double(y2) };
  // corner rechts unten
  Point crldp = { .x = double(x2 - r + 1), .y = double(y2) };
  Point crrdp = { .x = double(x2), .y = double(y2 - r + 1) };

  rotate_line(&cllup, &clrup, &center, &angle);
  arduboy.drawLine(cllup.x, cllup.y, clrup.x, clrup.y);

  rotate_line(&crlup, &crrup, &center, &angle);
  arduboy.drawLine(crlup.x, crlup.y, crrup.x, crrup.y);

  rotate_line(&clldp, &clrdp, &center, &angle);
  arduboy.drawLine(clldp.x, clldp.y, clrdp.x, clrdp.y);

  rotate_line(&crldp, &crrdp, &center, &angle);
  arduboy.drawLine(crldp.x, crldp.y, crrdp.x, crrdp.y);
}


void rotate_line(Point* first, Point* second, Point* center, double* angle) {
  rotate_point(first, center->x, center->y, *angle);
  rotate_point(second, center->x, center->y, *angle);
}

double angle = 0;
double xpos = 10;
double ypos = 5;
double size_w = 15;
double size_h = 20;

void drawCardTest() {
  if (arduboy.pressed(RIGHT_BUTTON)) {
    angle = angle >= 355 ? 0 : (angle + 5);
    xpos = xpos > 128 ? 0 : xpos + 5;
  }
  if (arduboy.pressed(LEFT_BUTTON)) {
    angle = angle >= 355 ? 0 : (angle + 5);
    xpos = xpos < -5 ? 128 : xpos - 5;
  }
  if (arduboy.pressed(UP_BUTTON)) {
    ypos = ypos < -5 ? 64 : ypos - 5;
  }
  if (arduboy.pressed(DOWN_BUTTON)) {
    ypos = ypos > 64 ?  0 : ypos + 5;
  }

  if (arduboy.justPressed(A_BUTTON)) {
    size_w *= 1.05;
    size_h *= 1.05;
  } else if (arduboy.justPressed(B_BUTTON)) {
    size_w *= 0.95;
    size_h *= 0.95;
  }

  tinyfont.setCursor(0, 0);
  tinyfont.print("x:" + toString(xpos, 3) + " y:" + toString(ypos, 3) + " w:" + toString(size_w, 3) + " h:" + toString(size_h, 3));
  drawCard(xpos, ypos, size_w, size_h, angle);

}

void addRotateTransform(int8_t* tMat, int8_t angle) {
  double radians = (2 * 3.1416 * angle) / 360;
  tMat[0] = int8_t(cos(radians));
  tMat[8] = 1;
  tMat[1] = int8_t(sin(radians));
  tMat[3] = int8_t(-sin(radians));
  tMat[4] = int8_t(cos(radians));
  
}

Card test(1);

void drawCardWithCard() {
  int8_t* tMat  = new int8_t[9];
  addRotateTransform(tMat, 45);
  //test.transform(tMat);
  //test.draw();
}


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
  arduboy.clear();

  // ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  //drawCardTest();
  drawCardWithCard();
  arduboy.display();
}

