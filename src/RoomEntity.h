#pragma once

#include "App.h"

#define TERRAIN_GROUP 0x01
#define LADDER_GROUP 0x02
#define DAMAGE_GROUP 0x04
#define ITEM_GROUP 0x08
#define PASSAGE_GROUP 0x10
#define PLANK_GROUP 0x20

class TDirtEntity : public NGame::TEntity {
public:
    TDirtEntity(NGame::TEntity::TId id);

    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TGrassEntity : public NGame::TEntity {
public:
    TGrassEntity(NGame::TEntity::TId id);
    
    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TPlankEntity : public NGame::TEntity {
public:
    TPlankEntity(NGame::TEntity::TId id);
    
    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TStoneEntity : public NGame::TEntity {
public:
    TStoneEntity(NGame::TEntity::TId id);
    
    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TLadderEntity : public NGame::TEntity {
public:
    TLadderEntity(NGame::TEntity::TId id);

    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TExplosionEntity : public NGame::TEntity {
public:
    TExplosionEntity(NGame::TEntity::TId id);

    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;
    virtual void Alarm(NGame::TAlarm::TId id) override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TKeyEntity : public NGame::TEntity {
public:
    TKeyEntity(NGame::TEntity::TId id);

    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TMineEntity : public NGame::TEntity {
public:
    TMineEntity(NGame::TEntity::TId id);

    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;
    virtual void Alarm(NGame::TAlarm::TId id) override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TCurseEntity : public NGame::TEntity {
public:
    TCurseEntity(NGame::TEntity::TId id);

    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TSpikeEntity : public NGame::TEntity {
public:
    TSpikeEntity(NGame::TEntity::TId id);

    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TEntranceEntity : public NGame::TEntity {
public:
    TEntranceEntity(NGame::TEntity::TId id);

    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TExitEntity : public NGame::TEntity {
public:
    TExitEntity(NGame::TEntity::TId id);

    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Sprite_;
};

class TFloatingTextEntity : public NGame::TEntity {
public:
    TFloatingTextEntity(NGame::TEntity::TId id);

    void SetText(const std::string& text);
    void SetColor(NGame::TFontManager::EColor color);

    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;
    virtual void Alarm(NGame::TAlarm::TId id) override;

private:
    std::string Text_;
    NGame::TFontManager::EColor Color_;
};

class TRoomEntity : public NGame::TEntity {
public:
    TRoomEntity(NGame::TEntity::TId id);

private:
    enum EType {
        None,
        Left = 0x0001,
        Right = 0x0002,
        Up = 0x0004,
        Down = 0x0008,
        Start = 0x0010,
        Exit = 0x0020,
        LeftRight = Left | Right,
        LeftRightDown = Left | Right | Down,
        LeftRightUp = Left | Right | Up,
        LeftRightUpDown = Left | Right | Up | Down,
    };

    enum ETile {
        Empty,
        Baddy,
        Curse,
        Dirt,
        Grass,
        HighDirt,
        Ladder,
        LowDirt,
        MidDirt,
        Mine,
        Passage,
        Plank,
        Spike,
        Utility,
    };

    struct TRoom {
        ETile data[60];
    };

    void LoadTemplates();
    void ParseRooms(const std::string& data, std::vector<TRoom>& rooms);
    bool ParseRoom(std::istringstream& stream, TRoom& room);
    void FillRow(const std::string& data, std::size_t row, TRoom& room);
    bool GoLeft(int* maze, NGame::Vec2i& position);
    bool GoRight(int* maze, NGame::Vec2i& position);
    bool GoDown(int* maze, NGame::Vec2i& position);
    void GenerateLayout();
    void GenerateRoom(int* maze, const NGame::Vec2i& position);
    void SelectRoom(int type, TRoom& room);

private:
    std::vector<TRoom> LRRooms_;
    std::vector<TRoom> LRURooms_;
    std::vector<TRoom> LRDRooms_;
    std::vector<TRoom> LRUDRooms_;
    std::vector<TRoom> AnyRooms_;
};

class THero : public NGame::TEntity {
public:
    THero(NGame::TEntity::TId id);

    enum class EKeys {
        Left,
        Right,
        Up,
        Down,
        X,
        Z,
        C,
        Shift,
        Escape,
        MaxSentinel
    };

    enum class EState {
        Normal,
        Jump,
        Fall,
        Climb,
        Hold,
    };

    virtual void Input(SDL_Event* event) override;
    virtual void Update(std::uint32_t delta) override;
    virtual void Draw() const override;
    virtual void Alarm(NGame::TAlarm::TId id) override;

private:
    bool KeysPressed_[static_cast<int>(EKeys::MaxSentinel)] = {};
    bool KeysHeld_[static_cast<int>(EKeys::MaxSentinel)] = {};
    bool FaceLeft_ = false;
    bool IgnorePlanks_ = false;
    bool AlternateRun_ = false;
    EState State_ = EState::Normal;

    const float Gravity_ = 500.0;
    NGame::Vec2f Speed_ = NGame::Vec2f(0.0, 0.0);
    NGame::Vec2f Fraction_ = NGame::Vec2f(0.0, 0.0);
    NGame::Vec2i Want_;
};

class TBackgroundTiler : public NGame::TEntity {
public:    
    TBackgroundTiler(NGame::TEntity::TId id);
    virtual void Draw() const override;

private:
    std::shared_ptr<NGame::TSpriteManager::TSprite> Background_;
};