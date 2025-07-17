#include "FileManager.h"

#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace NGame {

TFileManager::TFileManager(const std::string& dataDirectory, const std::string& archivePath, std::size_t cacheSize) 
    : DataDirectory_(dataDirectory), ArchivePath_(archivePath), Cache_(cacheSize) {
    
}

std::string TFileManager::Get(const std::string& path) {
    if (Cache_.Contains(path)) {
        return Cache_.Get(path);
    }

    #ifdef __EMSCRIPTEN__
    printf("Emscripten: FileManager::Get(%s)\n", path.c_str());
    #endif

    auto getAttempt = FromFilesystem(path);
    if (getAttempt.second) {
        #ifdef __EMSCRIPTEN__
        printf("Emscripten: Found file %s in filesystem\n", path.c_str());
        #endif
        Cache_.Set(path, getAttempt.first);
        return getAttempt.first;
    }

    getAttempt = FromArchive(path);
    if (getAttempt.second) {
        #ifdef __EMSCRIPTEN__
        printf("Emscripten: Found file %s in archive\n", path.c_str());
        #endif
        Cache_.Set(path, getAttempt.first);
        return getAttempt.first;
    }

    #ifdef __EMSCRIPTEN__
    printf("Emscripten: Failed to find file %s\n", path.c_str());
    #endif
    throw std::runtime_error("can't find file " + path);
}

std::pair<std::string, bool> TFileManager::FromFilesystem(const std::string& path) {
    auto finalPath = DataDirectory_ + "/" + path;
    
    std::ifstream fileStream(finalPath, std::ios::in | std::ios::binary);
    if (!fileStream.is_open()) {
        return std::make_pair<std::string, bool>({}, false);
    }

    std::stringstream fileStringStream;
    fileStringStream << fileStream.rdbuf();
    return std::make_pair(fileStringStream.str(), true);
}

std::pair<std::string, bool> TFileManager::FromArchive(const std::string& path) {
    #ifdef __EMSCRIPTEN__
    printf("Emscripten: Trying to open archive: %s\n", ArchivePath_.c_str());
    #endif
    
    std::ifstream archiveStream(ArchivePath_, std::ios::in | std::ios::binary);
    if (!archiveStream.is_open()) {
        #ifdef __EMSCRIPTEN__
        printf("Emscripten: Failed to open archive: %s\n", ArchivePath_.c_str());
        #endif
        return std::make_pair<std::string, bool>({}, false);
    }
    
    #ifdef __EMSCRIPTEN__
    printf("Emscripten: Successfully opened archive: %s\n", ArchivePath_.c_str());
    #endif
    
    // Identify and validate PAK file
    char identifier[4];
    archiveStream.read(identifier, 4);
    if (std::memcmp(identifier, "PACK", 4)) {
        #ifdef __EMSCRIPTEN__
        printf("Emscripten: Invalid PAK header, expected PACK, got %.4s\n", identifier);
        #endif
        return std::make_pair<std::string, bool>({}, false);
    }
    
    #ifdef __EMSCRIPTEN__
    printf("Emscripten: Valid PAK header found\n");
    #endif
    
    std::uint32_t tocOffset = ReadInt32(archiveStream);
    std::uint32_t tocSize = ReadInt32(archiveStream) / 64;

    if (!tocSize || tocOffset < 12) {
        return std::make_pair<std::string, bool>({}, false);
    }

    // Find requested file
    archiveStream.seekg(tocOffset);

    for (std::uint32_t index = 0; index < tocSize; ++index) {
        char name[56];
        
        archiveStream.read(name, 56);
        std::uint32_t fileOffset = ReadInt32(archiveStream);
        std::uint32_t fileSize = ReadInt32(archiveStream);

        if (std::strncmp(name, path.c_str(), 56)) {
            continue;
        }

        #ifdef __EMSCRIPTEN__
        printf("Emscripten: Found file %s in archive at offset %u, size %u\n", path.c_str(), fileOffset, fileSize);
        #endif

        archiveStream.seekg(fileOffset);
        std::string result(fileSize, 0);
        archiveStream.read(result.data(), result.size());

        return std::make_pair(result, true);
    }

    #ifdef __EMSCRIPTEN__
    printf("Emscripten: File %s not found in archive\n", path.c_str());
    #endif
    return std::make_pair<std::string, bool>({}, false);
}

std::uint32_t TFileManager::ReadInt32(std::ifstream& stream) {
    unsigned char bytes[4];
    stream.read(reinterpret_cast<char*>(bytes), 4);
    return (bytes[0] << 0) | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
}

} // namespace NGame
