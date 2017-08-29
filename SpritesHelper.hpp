#ifndef SPRITES_HELPER_HEADER
#define SPRITES_HELPER_HEADER

#include "Sprite.hpp"
#include "AnimatedSprite.hpp"

extern Sprites sprites;

class SpritesHelper {
  public:
    static void drawSelfMasked(const Sprite &sprite);
    static void drawOverwrite(const Sprite &sprite);
    static void drawSelfMasked( AnimatedSprite &sprite);
    static void drawOverwrite( AnimatedSprite &sprite);
};

#endif
