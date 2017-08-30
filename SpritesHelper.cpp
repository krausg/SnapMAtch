#include "SpritesHelper.hpp"


void SpritesHelper::drawSelfMasked(const Sprite &sprite) {
  if (sprite.isVisible) {
    sprites.drawSelfMasked(sprite.x, sprite.y, sprite.bitmap, sprite.frame);
  }
}
void SpritesHelper::drawOverwrite(const Sprite &sprite) {
  if (sprite.isVisible) {
    sprites.drawOverwrite(sprite.x, sprite.y, sprite.bitmap, sprite.frame);
  }
}

void SpritesHelper::drawSelfMasked( AnimatedSprite &sprite) {
  sprite.animate();
  if (sprite.isVisible) {
    sprites.drawSelfMasked(sprite.x, sprite.y, sprite.bitmap, sprite.frame);
  }
}
void SpritesHelper::drawOverwrite( AnimatedSprite &sprite) {
  sprite.animate();
  if (sprite.isVisible) {
    sprites.drawOverwrite(sprite.x, sprite.y, sprite.bitmap, sprite.frame);
  }
}

