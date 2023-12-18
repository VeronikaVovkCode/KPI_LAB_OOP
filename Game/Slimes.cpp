#include "Slimes.h"

#include "AnimationManager.h"
#include "TextureAtlas.h"
#include "Player.h"

Slime::Slime(const Vec2& pos, const BoundingBox& boundingBox)
	: Entity(pos, boundingBox)
{
	TextureAtlas& textureAtlas = TextureAtlas::Get();
	uint32_t textureWidth = textureAtlas.GetTextureWidth();
	uint32_t textureHeight = textureAtlas.GetTextureHeight();
	m_SlimePos = pos + Vec2(textureWidth / 2.0f, textureHeight / 2.0f);


	AnimationManager& animationManager = AnimationManager::Get();
	m_animation = AnimationManager::Get().CreateAnimation("anim_slime");
	m_animation->AddTexture(textureAtlas.GetTexture(TextureType::TEXTURE_SLIME_RED_IDLE));
	m_animation->AddTexture(textureAtlas.GetTexture(TextureType::TEXTURE_SLIME_RED_JUMPING));
	m_animation->Init(0.25f);
	m_sprite.SetPosition(m_pos);
	m_boundingBox = BoundingBox(m_SlimePos, 16.0f, 16.0f);

}

void Slime::OnUpdate(float timestep)
{
	AnimationManager::Get().Apply("anim_slime", &m_sprite);
	//m_timeSinceLastAttack += timestep;

	if (!m_path.empty())
	{
		m_arrived = false;
		float time = 1.0f / m_tilesPerSec;
		m_moveTime += timestep;
		if (m_path.size() > 1)
		{
			Vec2 from = *m_path.begin();
			Vec2 to = *(m_path.begin() + 1);
			if (m_moveTime > time)
			{
				m_moveTime = 0.0f;
				m_path.erase(m_path.begin());
			}
			else
			{
				Move(from, to, m_moveTime * m_tilesPerSec);
			}
		}
		else
		{
			Vec2 pos = m_path.back();
			this->SetPosition(pos);
			this->GetSprite()->SetPosition(pos);
			m_boundingBox = BoundingBox(pos, 16.0f, 16.0f);
			m_path.clear();
		}
	}
	else m_arrived = true;
}

void Slime::Move(const Vec2& from, const Vec2& to, float t)
{
	Vec2 pos;
	pos.x = std::lerp(from.x, to.x, t);
	pos.y = std::lerp(from.y, to.y, t);
	this->SetPosition(pos);
	this->GetSprite()->SetPosition(pos);
	m_boundingBox = BoundingBox(pos, 16.0f, 16.0f);
}

void Slime::OnEntityCollision(Entity* entity) {

	if (entity->GetType() == ENTITY_PLAYER)
	{
		Player* player = (Player*)entity;
		if (!player->IsImmune())
		{
			AudioManager::Get().PlaySound(AudioType::AUDIO_ENEMY_DAMAGE);
			player->DealDamage();
		}
	}
};
