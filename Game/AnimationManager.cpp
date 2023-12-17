#include "AnimationManager.h"

#include "../Utility/Logger.h"

AnimationManager& AnimationManager::Get()
{
	static AnimationManager instance;
	return instance;
}

void AnimationManager::OnUpdate(float timestep)
{
	for (auto& animation : m_animations)
		animation.second->OnUpdate(timestep);
}

void AnimationManager::Apply(const std::string& name, Sprite* sprite)
{
	SpriteAnimation* animation = GetAnimation(name);
	if (!animation)
		return;

	animation->Apply(sprite);
}

SpriteAnimation* AnimationManager::CreateAnimation(const std::string& name)
{
	SpriteAnimation* animation = GetAnimation(name);
	if (animation)
	{
		LOG("Found animation {} in cache. Returning the cached one...", name);
		return animation;
	}

	animation = new SpriteAnimation();
	m_animations[name] = std::unique_ptr<SpriteAnimation>(animation);
	return animation;
}

SpriteAnimation* AnimationManager::GetAnimation(const std::string& name)
{
	auto it = m_animations.find(name);
	return it == m_animations.end() ? nullptr : it->second.get();
}
