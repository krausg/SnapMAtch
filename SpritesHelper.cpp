#include "SpritesHelper.hpp"


void SpritesHelper::drawSelfMasked(const Sprite &sprite) {
  sprites.drawSelfMasked(sprite.x, sprite.y, sprite.bitmap, sprite.frame);
}
void SpritesHelper::drawOverwrite(const Sprite &sprite) {
  sprites.drawOverwrite(sprite.x, sprite.y, sprite.bitmap, sprite.frame);
}

void SpritesHelper::drawSelfMasked( AnimatedSprite &sprite) {
  sprite.animate();
  sprites.drawSelfMasked(sprite.x, sprite.y, sprite.bitmap, sprite.frame);
}
void SpritesHelper::drawOverwrite( AnimatedSprite &sprite) {
  sprite.animate();
  sprites.drawOverwrite(sprite.x, sprite.y, sprite.bitmap, sprite.frame);
}

