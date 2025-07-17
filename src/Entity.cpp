#include "Entity.h"

namespace NGame {

TEntity::TEntity(TEntity::TId id)
    : Id_(id) {

}

void TEntity::Tick(std::uint32_t delta) {
    Alarm_.Update(delta);
    
    TAlarm::TId alarmId;
    while (Alarm_.Next(alarmId)) {
        Alarm(alarmId);
    }
    Update(delta);
}

void TEntity::Input(SDL_Event* event) {
    GAME_UNUSED(event);
}

void TEntity::Update(std::uint32_t delta) {
    GAME_UNUSED(delta);
}

void TEntity::Alarm(TAlarm::TId id) {
    GAME_UNUSED(id);
}

void TEntity::Draw() const {
}

void TEntity::SetPosition(Vec2i value) {
    Position_ = value;
}

void TEntity::SetSize(Vec2i value) {
    Size_ = value;
}

const Vec2i& TEntity::Position() const {
    return Position_;
}

const Vec2i& TEntity::Size() const {
    return Size_;
}

const Vec2i& TEntity::AckPosition() const {
    return AckPosition_;
}

const Vec2i& TEntity::AckSize() const {
    return AckSize_;
}

bool TEntity::HasChanges() const {
    if (AckPosition_ != Position_ || AckSize_ != Size_)
        return true;

    return false;
}

void TEntity::AckChanges() {
    AckPosition_ = Position_;
    AckSize_ = Size_;
}

TEntity::TCollisionGroup TEntity::CollisionGroup() const {
    return CollisionGroup_;
}

void TEntity::SetCollisionGroup(TCollisionGroup group) {
    CollisionGroup_ = group;
}

float TEntity::MovementPerTick(std::uint32_t delta, float speed) {
    return speed * (delta / 1000.0f);
}

Vec2f TEntity::MovementPerTick(std::uint32_t delta, Vec2f speed) {
    return speed * (delta / 1000.0f);
}

std::pair<std::int32_t, float> TEntity::NextMovement(float speed, float fraction) {
    std::pair<std::int32_t, float> result;

    result.second = speed + fraction;
    result.first = static_cast<std::int32_t>(result.second);
    result.second -= result.first;

    return result;
}

TEntity::TId TEntity::Id() const {
    return Id_;
}

void TEntity::Remove() {
    IsRemoved_ = true;
}

bool TEntity::IsRemoved() const {
    return IsRemoved_;
}

bool TEntity::IsPersistent() const {
    return IsPersistent_;
}

} // namespace NGame
