#include "SurfaceManager.h"

#include <cstring>
#include <SDL2/SDL_rwops.h>
#include <SDL2/SDL_surface.h>
#include <stdexcept>

namespace NGame {

TSurfaceManager::TSurfaceManager(TFileManager& fileManager, std::size_t cacheSize) 
    : FileManager_(fileManager), Cache_(cacheSize) {
}

std::shared_ptr<SDL_Surface> TSurfaceManager::Get(const std::string& path) {
    if (Cache_.Contains(path)) {
        return Cache_.Get(path);
    }

    std::string data = FileManager_.Get(path);
    SDL_RWops* rw = SDL_RWFromConstMem(data.data(), data.size());
    SDL_Surface* surface = SDL_LoadBMP_RW(rw, 1);

    if (!surface) {
        std::runtime_error("Can't create surface from file " + path);
    }
    
    std::shared_ptr<SDL_Surface> result(surface, [](SDL_Surface* surface) { SDL_FreeSurface(surface); });
    Cache_.Set(path, result);
    return result;
}

} // namespace NGame