#include "Common.h"

#include <algorithm>
#include <cctype>
#include <iterator>
#include <string_view>

namespace NGame {

std::string ToUpper(const std::string_view& value) {
    std::string result; 
    result.resize(value.size());

    std::transform(value.begin(), value.end(), result.begin(), ::toupper);
    return result;
}

std::string ToLower(const std::string_view& value) {
    std::string result; 
    result.resize(value.size());

    std::transform(value.begin(), value.end(), result.begin(), ::tolower);
    return result;
}

std::string_view LeftTrim(const std::string_view& value) {
    auto firstNonSpace = std::find_if(value.begin(), value.end(), [](char symbol) {
        return !std::isspace(symbol);
    });

    auto length = std::distance(firstNonSpace, value.end());
    return std::string_view(&*firstNonSpace, length);
}

std::string_view RightTrim(const std::string_view& value) {
    auto lastNonSpace = std::find_if(value.rbegin(), value.rend(), [](char symbol) {
        return !std::isspace(symbol);
    });

    auto index = value.size() - std::distance(value.rbegin(), lastNonSpace);
    auto length = std::distance(value.begin(), value.begin() + index);
    return std::string_view(&*value.begin(), length);
}

std::string_view Trim(const std::string_view& value) {
    return LeftTrim(RightTrim(value));
}

std::string_view NextToken(std::string_view& value, const std::string_view& token) {
    auto position = value.find(token);
    auto result = value.substr(0, position);

    if (position == std::string_view::npos) {
        value = {};
    } else {
        value = value.substr(position + token.size());
    }
    
    return result;
}

bool RectContains(const Vec2i& position, const Vec2i& size, const Vec2i& point) {
    if (point.X < position.X || point.X - position.X > size.X ||
        point.Y < position.Y || point.Y - position.Y > size.Y) {
        return false;
    }
    
    return true;
}

bool RectOverlaps(const Vec2i& positionA, const Vec2i& sizeA, const Vec2i& positionB, const Vec2i& sizeB) {
    if (positionB.X + sizeB.X <= positionA.X || 
        positionA.X + sizeA.X <= positionB.X || 
        positionB.Y + sizeB.Y <= positionA.Y ||
        positionA.Y + sizeA.Y <= positionB.Y) {
        return false;
    }
    return true;
}

} // namespace NGame
