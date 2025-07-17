#include "FontManager.h"

#include <iostream>

namespace NGame {

TFontManager::TFontManager(TSpriteManager& spriteManager) 
    : SpriteManager_(spriteManager) {
    Fonts_[White] = SpriteManager_.Get("Fonts/White.txt");
    Fonts_[Gray] = SpriteManager_.Get("Fonts/Gray.txt");
    Fonts_[Red] = SpriteManager_.Get("Fonts/Red.txt");
    Fonts_[Green] = SpriteManager_.Get("Fonts/Green.txt");
    Fonts_[Blue] = SpriteManager_.Get("Fonts/Blue.txt");
    Fonts_[Purple] = SpriteManager_.Get("Fonts/Purple.txt");
    Fonts_[Gold] = SpriteManager_.Get("Fonts/Gold.txt");
    Fonts_[Swamp] = SpriteManager_.Get("Fonts/Swamp.txt");
    Fonts_[LightBlue] = SpriteManager_.Get("Fonts/LightBlue.txt");
}

void TFontManager::Draw(EColor color, const Vec2i position, const std::string& text) {
    Vec2i currentPosition = position;

    for (const auto& symbol : text) {
        if (symbol >= ' ' && symbol <= '~') {
            SpriteManager_.Draw(Fonts_[color], (unsigned char)symbol - ' ', currentPosition);
            currentPosition += Vec2i(GlyphSize.X, 0);
        } else if (symbol == '\n') {
            currentPosition = Vec2i(position.X, currentPosition.Y + GlyphSize.Y);
        } else if (symbol == '\t') {
            currentPosition += Vec2i(GlyphSize.X * 4, 0);
        }
    }
}

} // namespace NGame