#pragma once

#include "Common.h"

#include "SpriteManager.h"

namespace NGame {

class TDigitManager {
public:
    TDigitManager(TSpriteManager& spriteManager);
    DELETE_COPY(TDigitManager)
    
    void Draw(const Vec2i position, int value, int length, int point);

private:
    TSpriteManager& SpriteManager_;
    const Vec2i GlyphSize = {7, 12};
    std::shared_ptr<TSpriteManager::TSprite> Digits_;
};

} // namespace NGame