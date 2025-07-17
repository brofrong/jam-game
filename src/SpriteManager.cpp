#include "SpriteManager.h"

#include <SDL2/SDL_render.h>
#include <sstream>

namespace NGame {

TSpriteManager::TSpriteManager(TFileManager& fileManager, TRenderManager& renderManager, std::size_t cacheSize)
    : FileManager_(fileManager), RenderManager_(renderManager), Cache_(cacheSize) {
}

std::shared_ptr<TSpriteManager::TSprite> TSpriteManager::Get(const std::string& path) {
    if (Cache_.Contains(path)) {
        return Cache_.Get(path);
    }

    auto result = std::make_shared<TSprite>(ParseInfoFile(path));
    Cache_.Set(path, result);
    return result;
}

void TSpriteManager::Draw(const std::shared_ptr<TSprite>& sprite, size_t frame, const Vec2i& position, const Vec2f& scale) {
    const auto& frameData = sprite->Frames[frame];
    
    int flip = 0;
    Vec2i size = frameData.Size * scale;
    
    if (size.X < 0) {
        size.X = -size.X;
        flip |= SDL_FLIP_HORIZONTAL;
    }
    if (size.Y < 0) {
        size.Y = -size.Y;
        flip |= SDL_FLIP_VERTICAL;
    }
    
    RenderManager_.SetTexture(sprite->Texture);
    RenderManager_.DrawSprite(frameData.Position, frameData.Size, position, size, static_cast<SDL_RendererFlip>(flip));
}

TSpriteManager::TSprite TSpriteManager::ParseInfoFile(const std::string& path) {
    std::string data = FileManager_.Get(path);
    std::istringstream inputStream(data);

    std::shared_ptr<SDL_Texture> currentTexture;
    std::vector<TFrame> currentFrames;

    for (std::string line; std::getline(inputStream, line); ) {
        auto remainder = Trim(std::string_view(line));

        auto action = RightTrim(NextToken(remainder, " "));
        if (action == "Texture") {
            auto textureString = Trim(NextToken(remainder, " "));
            if (textureString.empty()) {
                throw std::runtime_error("texture name should not be empty for " + path);
            }
            currentTexture = RenderManager_.Get(std::string(textureString));
        } else if (action == "Frame") {
            auto xString = Trim(NextToken(remainder, " "));
            auto yString = Trim(NextToken(remainder, " "));
            auto widthString = Trim(NextToken(remainder, " "));
            auto heightString = Trim(NextToken(remainder, " "));
            

            TFrame frame;

            if (xString.empty() && yString.empty()) {
                frame.Position.X = 0;
                frame.Position.Y = 0;
            } else {
                frame.Position.X = std::stoi(std::string(xString));
                frame.Position.Y = std::stoi(std::string(yString));
            }

            if (widthString.empty() && heightString.empty()) {
                int width, height;

                if (SDL_QueryTexture(currentTexture.get(), NULL, NULL, &width, &height)) {
                    throw std::runtime_error("can't query texture information for " + path);
                }

                frame.Size.X = width;
                frame.Size.Y = height;
            } else {
                frame.Size.X = std::stoi(std::string(widthString));
                frame.Size.Y = std::stoi(std::string(heightString));
            }

            if (xString.empty() || yString.empty() || widthString.empty() || heightString.empty()) {
                throw std::runtime_error("frame should have x, y, width, height parameters for " + path);
            }
            
            currentFrames.push_back(frame);
        }
    }

    if (!currentTexture) {
        std::runtime_error("no texture for " + path);
    }

    if (currentFrames.empty()) {
        TFrame frame;
        int width, height;
        if (SDL_QueryTexture(currentTexture.get(), NULL, NULL, &width, &height)) {
            throw std::runtime_error("can't query texture information for " + path);
        }

        frame.Position.X = 0;
        frame.Position.Y = 0;
        frame.Size.X = width;
        frame.Size.Y = height;
        currentFrames.push_back(frame);
    }

    return {currentTexture, currentFrames};
}


} // namespace NGame
