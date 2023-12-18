#pragma once

#include <vector>
#include "Entity.h"
#include "Pathfinder.h"
#include "../Utility/Math.h"
#include "../Utility/Clock.h"
#include "../Audio/AudioManager.h"
#include "../Core/SpriteAnimation.h"

class Slime: public Entity
{
public:
    Slime(const Vec2& pos, const BoundingBox& boundingBox);

    virtual void OnUpdate(float timestep);
    virtual EntityType GetType()const { return ENTITY_ENEMY; }
    virtual Sprite* GetSprite() override { return &m_sprite; }
    virtual void OnEntityCollision(Entity* entity);
    bool IsArrived()const { return m_arrived; }
    void SetAttackInterval(float interval) { m_attackInterval = interval; }
    void SetPath(const std::vector<Vec2>& path) { m_path = path; }
    const auto& GetPath() const { return m_path; }
    void Move(const Vec2& from, const Vec2& to, float t);
    void SetTilesPerSec(float tilesPerSec) { m_tilesPerSec = tilesPerSec; }

protected:
    std::vector<Vec2> m_path;
    Vec2 m_SlimePos;
    bool m_arrived = true;
    SpriteAnimation* m_animation;
    Sprite m_sprite;
    float m_attackInterval = 4.0f;
    //float m_timeSinceLastAttack = 0.0f;
    float m_moveTime = 0.0f;
    float m_tilesPerSec = 4.0f;
}; 
