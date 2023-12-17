#include "Coin.h"

#include "../Audio/AudioManager.h"
#include "TextureAtlas.h"
#include "AnimationManager.h"

Coin::Coin(const Vec2& pos, const BoundingBox& boundingBox)
	: Entity(pos, boundingBox)
{
	TextureAtlas& atlas = TextureAtlas::Get();
	AnimationManager& animationManager = AnimationManager::Get();
	m_animation = AnimationManager::Get().CreateAnimation("anim_coin");
	m_animation->AddTexture(atlas.GetTexture(TEXTURE_COIN1));
	m_animation->AddTexture(atlas.GetTexture(TEXTURE_COIN2));
	m_animation->AddTexture(atlas.GetTexture(TEXTURE_COIN3));
	m_animation->AddTexture(atlas.GetTexture(TEXTURE_COIN4));
	m_animation->Init(0.25f);
	m_sprite.SetTexture(atlas.GetTexture(TEXTURE_COIN1));
	m_sprite.SetPosition(m_pos);
	m_boundingBox = BoundingBox(pos, 32.0f, 32.0f);
}

void Coin::OnUpdate(float timestep)
{
	AnimationManager::Get().Apply("anim_coin", &m_sprite);
}

void Coin::OnEntityCollision(Entity* entity)
{
	if (entity->GetType() == ENTITY_PLAYER)
		AudioManager::Get().PlaySound(AudioType::AUDIO_COIN_COLLECT);
}
