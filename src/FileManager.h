#pragma once

#include "Common.h"

#include "LRU.h"

namespace NGame {

class TFileManager {
public:
    TFileManager(const std::string& dataDirectory, const std::string& archivePath, std::size_t cacheSize = 4);
    DELETE_COPY(TFileManager)

    std::string Get(const std::string& path);

private:
    std::pair<std::string, bool> FromFilesystem(const std::string& path);
    std::pair<std::string, bool> FromArchive(const std::string& path);
    std::uint32_t ReadInt32(std::ifstream& stream);

private:
    const std::string DataDirectory_;
    const std::string ArchivePath_;
    TLRU<std::string, std::string> Cache_;
};

} // namespace NGame