#pragma once

#include "Common.h"

#include "LRU.h"
#include "FileManager.h"

#include <memory>
#include <SDL2/SDL_surface.h>

namespace NGame {

class TSurfaceManager {
public:
    TSurfaceManager(TFileManager& fileManager, std::size_t cacheSize = 4);
    DELETE_COPY(TSurfaceManager)

    std::shared_ptr<SDL_Surface> Get(const std::string& path);

private:
    TFileManager& FileManager_;
    TLRU<std::string, std::shared_ptr<SDL_Surface>> Cache_;
};

} // namespace NGame