#pragma once

#include <concepts>
#include <unordered_map>
#include "../Utility/Math.h"
#include "../Utility/Logger.h"
#include "../Core/Sprite.h"

enum EntityType
{
	ENTITY_UNKNOWN,
	ENTITY_PLAYER,
	ENTITY_ENEMY,
	ENTITY_COIN,
	ENTITY_WEAPON,
	ENTITY_TILE,
};

class Entity
{
public:
	Entity(const Vec2& pos, const BoundingBox& boundingBox);
	virtual ~Entity() = default;

	virtual void OnUpdate(float timestep) = 0;
	virtual void OnEntityCollision(Entity* entity) = 0;
	virtual EntityType GetType() const { return ENTITY_UNKNOWN; }
	virtual Sprite* GetSprite() = 0;
	void AddPosition(const Vec2& offset) { m_pos += offset; }
	void SetPosition(const Vec2& pos) { m_pos = pos; }
	void SetAABB(const Vec2& pos, float radius) { m_boundingBox = BoundingBox(pos, radius); }
	bool Collide(const Entity* otherEntity) const;
	const Vec2& GetPosition() const { return m_pos; }
	const BoundingBox& GetAABB() const { return m_boundingBox; }

	// CanMove function returns true if the entity can move
	// The function is reset every frame for some entities, like player or enemy
	// For tiles and coins this value is immutable in most cases
	auto& CanMove() { return m_canMove; }
	auto& CanMove() const { return m_canMove; }

protected:
	bool m_canMove = true;
	BoundingBox m_boundingBox;
	Vec2 m_pos;
};

class EntityFactory
{
public:
	EntityFactory() = default;
	~EntityFactory();

	template<std::derived_from<Entity> T, typename... Args>
	T* RegisterEntity(Args&&... args) 
	{
		Entity* entity = new T(std::forward<Args>(args)...);
		EntityType type = entity->GetType();
		return static_cast<T*>(m_entities[type].emplace_back(entity));
	}

	void DestroyEntity(Entity* entity);

	template<EntityType Type>
	auto& GetEntities() { return m_entities[Type]; }

private:
	std::unordered_map<EntityType, std::vector<Entity*>> m_entities;
};
