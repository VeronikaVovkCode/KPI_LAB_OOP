#pragma once

#include "Window.h"
#include "Sprite.h"
#include "../Utility/Math.h"
#include "../UI/TextComponent.h"

// Primitive types, that are used in the project
enum class PrimitiveType
{
	POINTS,
	LINES,
	TRIANGLES
};

Color ColorOf(const Vec3& rgb, float alpha);

struct FrameDesc
{
	float clearcolor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
};

class Renderer
{
public:
	bool Init(Window* window);

	void BeginFrame(const FrameDesc& framedesc);
	void EndFrame();
	void SetViewport(const Vec2& topLeft, const Vec2& bottomRight);

	void Draw(const Vertex* vertices, uint32_t numVertices, PrimitiveType primitive);
	void Draw(const Sprite* sprite);
	void Draw(const TextComponent* text);
	void DebugDraw(const Vec2& min, const Vec2& max);
	void DebugDraw(const Vec2& point);

	inline uint32_t GetWindowWidth() const { return m_window->GetWidth(); }
	inline uint32_t GetWindowHeight() const { return m_window->GetHeight(); }
	inline float GetWindowViewsize() const { return m_window->GetViewsize(); }

private:
	Window* m_window = nullptr;
};
