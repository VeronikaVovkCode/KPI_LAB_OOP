#pragma once

#include "Entity.h"
#include "TextureAtlas.h"

class Tile : public Entity
{
public:
    Tile(const Vec2& pos, const BoundingBox& boundingBox, TextureType type, bool isCollider);
    virtual ~Tile() = default;

    virtual void OnUpdate(float timestep) override {}
    virtual void OnEntityCollision(Entity* entity) override;
    virtual EntityType GetType() const { return ENTITY_TILE; }
    virtual Sprite* GetSprite() override { return &m_sprite; }
    auto& IsCollider() { return m_isCollider; }
    auto& IsCollider() const { return m_isCollider; }

private:
    Sprite m_sprite;
    bool m_isCollider = true;
};
