#pragma once

#include <bitset>
#include <cmath>
#include <cstdint>
#include <string_view>
#include <string>
#include <type_traits>

#define GAME_UNUSED(x) (void)(x)

#define DELETE_COPY(NAME) \
    NAME(const NAME&) = delete; \
    NAME& operator=(const NAME&) = delete;

namespace NGame {

template<class... Ts>
struct TOverload : Ts... { using Ts::operator()...; };

template<class... Ts>
TOverload(Ts...) -> TOverload<Ts...>;

template<typename T>
struct Vec2 {
    using TType = T;

    Vec2<T>()
        : X(), Y() {
    }

    Vec2<T>(T value) 
        : X(value), Y(value) {
    }
    Vec2<T>(T x, T y) 
        : X(x), Y(y) {
    }

    Vec2<T> operator+(const Vec2<T>& other) const {
        Vec2<T> result(X + other.X, Y + other.Y);
        return result;
    }

    Vec2<T>& operator+=(const Vec2<T>& other) {
        X += other.X;
        Y += other.Y;
        return *this;
    }

    Vec2<T> operator-(const Vec2<T>& other) const {
        Vec2<T> result(X - other.X, Y - other.Y);
        return result;
    }

    Vec2<T>& operator-=(const Vec2<T>& other) {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }

    template<typename Q>
    Vec2<T> operator*(const Vec2<Q>& other) const {
        Vec2<T> result(X * other.X, Y * other.Y);
        return result;
    }

    template<typename Q>
    Vec2<T>& operator*=(const Vec2<Q>& other) {
        X *= other.X;
        Y *= other.Y;
        return *this;
    }

    template<typename Q>
    Vec2<T> operator*(const Q& other) const {
        Vec2<T> result(X * other, Y * other);
        return result;
    }

    template<typename Q>
    Vec2<T>& operator*=(const Q& other) {
        X *= other;
        Y *= other;
        return *this;
    }

    template<typename Q>
    Vec2<T> operator/(const Vec2<Q>& other) const {
        Vec2<T> result(X / other.X, Y / other.Y);
        return result;
    }

    template<typename Q>
    Vec2<T>& operator/=(const Vec2<Q>& other) {
        X /= other.X;
        Y /= other.Y;
        return *this;
    }

    template<typename Q>
    Vec2<T> operator/(const Q& other) const {
        Vec2<T> result(X / other, Y / other);
        return result;
    }

    template<typename Q>
    Vec2<T>& operator/=(const Q& other) {
        X /= other;
        Y /= other;
        return *this;
    }

    template<typename Q = T, typename = typename std::enable_if<std::is_floating_point<Q>::value>::type>
    Q Length() const {
        return std::sqrt(X * X + Y * Y);
    }

    template<typename Q = T, typename = typename std::enable_if<std::is_floating_point<Q>::value>::type>
    Vec2<T> Normilize() const {
        return *this / Length();
    }

    template<typename Q = T, typename = typename std::enable_if<!std::is_floating_point<Q>::value>::type>
    float Length() const {
        return std::sqrt(static_cast<float>(X * X + Y * Y));
    }

    bool operator==(const Vec2<T>& other) const {
        return X == other.X && Y == other.Y;
    }

    bool operator!=(const Vec2<T>& other) const {
        return X != other.X || Y != other.Y;
    }

    union {
        struct {
            T X;
            T Y;
        };
        T Data[2];
    };
};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<std::int32_t>;

std::string ToUpper(const std::string_view& value);
std::string ToLower(const std::string_view& value);
std::string_view LeftTrim(const std::string_view& value);
std::string_view RightTrim(const std::string_view& value);
std::string_view Trim(const std::string_view& value);
std::string_view NextToken(std::string_view& value, const std::string_view& token);

bool RectContains(const Vec2i& position, const Vec2i& size, const Vec2i& point);
bool RectOverlaps(const Vec2i& positionA, const Vec2i& sizeA, const Vec2i& positionB, const Vec2i& sizeB);

} // namespace NGame

template<>
struct std::hash<NGame::Vec2i> {
    std::size_t operator()(const NGame::Vec2i& key) const {
        return ((static_cast<std::size_t>(key.X) * 73856093) ^ 
                (static_cast<std::size_t>(key.Y) * 19349663));
    }
};

template<>
struct std::hash<NGame::Vec2f> {
    std::size_t operator()(const NGame::Vec2f& key) const {
        return ((static_cast<std::size_t>(key.X) * 73856093) ^ 
                (static_cast<std::size_t>(key.Y) * 19349663));
    }
};