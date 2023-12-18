#include "Tile.h"

#include "TextureAtlas.h"

Tile::Tile(const Vec2& pos, const BoundingBox& boundingBox, TextureType type, bool isCollider)
	: Entity(pos, boundingBox)
	, m_isCollider(isCollider)
{
	TextureAtlas& atlas = TextureAtlas::Get();
	m_sprite.SetTexture(atlas.GetTexture(type));
	m_sprite.SetPosition(pos);
}

void Tile::OnEntityCollision(Entity* entity)
{
	EntityType type = entity->GetType();
	if (type != ENTITY_PLAYER && type != ENTITY_ENEMY)
		return;

	entity->CanMove() = false;
}
