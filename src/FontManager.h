#pragma once

#include "Common.h"

#include "SpriteManager.h"

namespace NGame {

class TFontManager {
public:
    enum EColor {
        White,
        Gray,
        Red,
        Green,
        Blue,
        Purple,
        Gold,
        Swamp,
        LightBlue,
        SentinelMax
    };

    TFontManager(TSpriteManager& spriteManager);
    DELETE_COPY(TFontManager)
    
    void Draw(EColor color, const Vec2i position, const std::string& text);

private:
    TSpriteManager& SpriteManager_;
    const Vec2i GlyphSize = {5, 12};
    std::array<std::shared_ptr<TSpriteManager::TSprite>, SentinelMax> Fonts_;
};

} // namespace NGame