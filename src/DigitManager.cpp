#include "DigitManager.h"

namespace NGame {

TDigitManager::TDigitManager(TSpriteManager& spriteManager) 
    : SpriteManager_(spriteManager) {
    Digits_ = SpriteManager_.Get("Sprites/Digits.txt");
}

void TDigitManager::Draw(const Vec2i position, int value, int length, int point) {
    Vec2i currentPosition = {position.X + length * GlyphSize.X, position.Y};

    for (size_t remainder = length; remainder; --remainder, --point) {
        if (value) {
            auto digit = value % 10;
            value /= 10;

            if (point == 0) {
                SpriteManager_.Draw(Digits_, digit + 11, currentPosition);
            } else {
                SpriteManager_.Draw(Digits_, digit, currentPosition);
            }
        } else {
            if (point == 0) {
                SpriteManager_.Draw(Digits_, 21, currentPosition);
            } else {
                SpriteManager_.Draw(Digits_, 10, currentPosition);
            }
        }
        
        currentPosition.X -= GlyphSize.X;
    }

}

} // namespace NGame