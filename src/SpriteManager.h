#pragma once

#include "Common.h"

#include "FileManager.h"
#include "LRU.h"
#include "RenderManager.h"

namespace NGame {

class TSpriteManager {
public:
    struct TFrame {
        Vec2i Position;
        Vec2i Size;
    };

    struct TSprite {        
        std::shared_ptr<SDL_Texture> Texture;
        std::vector<TFrame> Frames;
    };

    TSpriteManager(TFileManager& fileManager, TRenderManager& renderManager, std::size_t cacheSize = 4);
    DELETE_COPY(TSpriteManager)

    std::shared_ptr<TSprite> Get(const std::string& path);
    void Draw(const std::shared_ptr<TSprite>& sprite, size_t frame, const Vec2i& position, const Vec2f& scale = {1.0f, 1.0f});

private:
    TSprite ParseInfoFile(const std::string& path);

private:
    TFileManager& FileManager_;
    TRenderManager& RenderManager_;
    TLRU<std::string, std::shared_ptr<TSprite>> Cache_;
};

} // namespace NGame