#pragma once

#include "Common.h"

#include "Alarm.h"
#include "State.h"

#include <bitset>
#include <cstdint>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

namespace NGame {

class TEntity {
public:
    using TId = std::uint32_t;
    using TCollisionGroup = std::bitset<32>;

    TEntity(TEntity::TId id);
    virtual ~TEntity() = default;
    void Tick(std::uint32_t delta);
    virtual void Input(SDL_Event* event);
    virtual void Update(std::uint32_t delta);
    virtual void Alarm(TAlarm::TId id);
    virtual void Draw() const;
    
    void SetPosition(Vec2i value);
    void SetSize(Vec2i value);
    const Vec2i& Position() const;
    const Vec2i& Size() const;
    const Vec2i& AckPosition() const;
    const Vec2i& AckSize() const;
    bool HasChanges() const;
    void AckChanges();

    TCollisionGroup CollisionGroup() const;
    void SetCollisionGroup(TCollisionGroup group);
    static float MovementPerTick(std::uint32_t delta, float speed);
    static Vec2f MovementPerTick(std::uint32_t delta, Vec2f speed);
    std::pair<Vec2i::TType, float> NextMovement(float speed, float fraction);

    template<typename UnaryPredicate>
    std::pair<Vec2f, std::pair<bool, bool>> MoveWithCondition(Vec2f speed, Vec2f fraction, UnaryPredicate p) {
        auto distanceX = NextMovement(speed.X, fraction.X);
        auto distanceY = NextMovement(speed.Y, fraction.Y);
        auto directionFlags = std::make_pair(true, true);

        Vec2f resultFraction(distanceX.second, distanceY.second);
        Vec2i resultDistance(distanceX.first, distanceY.first);

        Vec2i newPosition = Position() + resultDistance;
        if (p(newPosition)) {
            // There is no problem with the new position, we are done
            SetPosition(newPosition);
        } else {
            // There might be some problem, move 1px at a time
            Vec2i direction(1, 1);

            if (resultDistance.X < 0) {
                direction.X = -1;
            }
            if (resultDistance.Y < 0) {
                direction.Y = -1;
            }
            resultDistance.X = abs(resultDistance.X);
            resultDistance.Y = abs(resultDistance.Y);

            for (Vec2i::TType i = 0; i < resultDistance.X; ++i) {
                newPosition = Position() + Vec2i(direction.X, 0);
                if (!p(newPosition)) {
                    resultFraction.X = 0;
                    directionFlags.first = false;
                    break;
                }
                SetPosition(newPosition);
            }

            for (Vec2i::TType i = 0; i < resultDistance.Y; ++i) {
                newPosition = Position() + Vec2i(0, direction.Y);
                if (!p(newPosition)) {
                    resultFraction.Y = 0;
                    directionFlags.second = false;
                    break;
                }
                SetPosition(newPosition);
            }
        }

        return std::make_pair(resultFraction, directionFlags);
    }

    TEntity::TId Id() const;
    void Remove();
    bool IsRemoved() const;
    bool IsPersistent() const;

protected:
    TAlarm Alarm_;

private:
    bool IsPersistent_ = false;
    bool IsRemoved_ = false;
    TEntity::TId Id_;
    TCollisionGroup CollisionGroup_;
    Vec2i Position_;
    Vec2i Size_;
    Vec2i AckPosition_;
    Vec2i AckSize_;
};

} // namespace NGame