#pragma once

#include "Entity.h"
#include "../Core/Sprite.h"
#include "../Core/SpriteAnimation.h"

class Coin : public Entity
{
public:
	Coin(const Vec2& pos, const BoundingBox& boundingBox);
	virtual ~Coin() = default;

	virtual void OnUpdate(float timestep) override;
	virtual void OnEntityCollision(Entity* entity) override;
	virtual EntityType GetType() const { return ENTITY_COIN; }
	virtual Sprite* GetSprite() { return &m_sprite; }

private:
	SpriteAnimation* m_animation;
	Sprite m_sprite;
};
