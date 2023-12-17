#pragma once

#include <memory>
#include <unordered_map>
#include "../Core/Sprite.h"
#include "../Core/SpriteAnimation.h"

class AnimationManager
{
private:
	AnimationManager() = default;

public:
	AnimationManager(const AnimationManager&) = delete;
	AnimationManager& operator=(const AnimationManager&) = delete;

	static AnimationManager& Get();

	void OnUpdate(float timestep);
	void Apply(const std::string& name, Sprite* sprite);
	SpriteAnimation* CreateAnimation(const std::string& name);
	SpriteAnimation* GetAnimation(const std::string& name);

private:
	std::unordered_map<std::string, std::unique_ptr<SpriteAnimation>> m_animations;
};
