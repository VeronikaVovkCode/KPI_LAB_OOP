#include "Entity.h"

#include <algorithm>

Entity::Entity(const Vec2& pos, const BoundingBox& boundingBox)
    : m_boundingBox(boundingBox)
    , m_pos(pos)
{
}

bool Entity::Collide(const Entity* otherEntity) const
{
    return m_boundingBox.Collide(otherEntity->GetAABB());
}

EntityFactory::~EntityFactory()
{
	// Clean up dynamically allocated entities
	for (auto& pair : m_entities)
	{
		for (Entity* e : pair.second)
			delete e;
	}
}

void EntityFactory::DestroyEntity(Entity* entity)
{
	EntityType type = entity->GetType();
	if (type == ENTITY_UNKNOWN)
		return;

	auto& typeVec = m_entities[type];
	auto it = std::ranges::find(typeVec, entity);
	if (it == typeVec.end())
		return;

	typeVec.erase(it);
}
