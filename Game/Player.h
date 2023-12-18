#pragma once

#include "../Core/Sprite.h"
#include "../Core/SpriteAnimation.h"
#include "../Utility/Math.h"
#include "Entity.h"



class Player : public Entity
{
public:
    Player(const Vec2& pos, const BoundingBox& boundingBox);
    virtual ~Player() = default;

    // OnUpdate will update the position of sprites, AABB and CanMove state
    // Should be called before updating all the Tiles
    virtual void OnUpdate(float timestep) override;
    
    virtual void OnEntityCollision(Entity* entity) override;
    virtual EntityType GetType() const { return ENTITY_PLAYER; }
    virtual Sprite* GetSprite() override { return m_activeSprite; }
    void OnCoinPickup();
    void OnWeaponPickup();
    void OnEnemyInteract();
    void OnTileCollision();
    void SetHealth(uint32_t val) { m_health = val; }
    void SetDirection(Direction direction);
    uint32_t GetCollectedCoins() const { return m_collectedCoins; }
    uint32_t GetHealth() const { return m_health; }
    void DealDamage() { if (GetHealth() > 0) --m_health; }
    bool IsImmune() const { return m_timeSinceDamageDealt < 4.0f; }
    const Vec2& GetCenterPos() const { return m_playerPos; }

private:
    Vec2 m_playerPos;
    bool m_hasWeapon = false;
    float m_lastTimestep = 0.0f;
    float m_timeSinceAnimationTick = 0.0f;
    float m_timeSinceDamageDealt = 0.0f;
    uint32_t m_collectedCoins = 0;
    uint32_t m_health = 3;
    Sprite* m_activeSprite = nullptr;
    Sprite m_sprites[4]; // Sprite for each direction
    Sprite m_damageSprites[4];
    Direction m_direction;
};
