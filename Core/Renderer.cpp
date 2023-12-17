#include "pch.h"
#include <SFML/Graphics.hpp>

bool Renderer::Init(Window* window)
{
	if (!window)
	{
		LOG("(Renderer) Provided window is nullptr");
		return false;
	}
	m_window = window;
	return true;
}

void Renderer::BeginFrame(const FrameDesc& framedesc)
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
	sf::Uint8 r = static_cast<sf::Uint8>(framedesc.clearcolor[0] * 255.0f);
	sf::Uint8 g = static_cast<sf::Uint8>(framedesc.clearcolor[1] * 255.0f);
	sf::Uint8 b = static_cast<sf::Uint8>(framedesc.clearcolor[2] * 255.0f);
	sf::Uint8 a = static_cast<sf::Uint8>(framedesc.clearcolor[3] * 255.0f);
	rw->clear(sf::Color(r, g, b, a));
}

void Renderer::EndFrame()
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
	rw->display();
}

void Renderer::SetViewport(const Vec2& topLeft, const Vec2& bottomRight)
{
	m_window->SetViewport(topLeft.x, topLeft.y, bottomRight.y, bottomRight.x);
}

static sf::PrimitiveType GetSFMLPrimitiveType(PrimitiveType type)
{
	switch (type)
	{
	case PrimitiveType::POINTS: return sf::PrimitiveType::Points;
	case PrimitiveType::LINES: return sf::PrimitiveType::Lines;
	case PrimitiveType::TRIANGLES: return sf::PrimitiveType::Triangles;
	default: ASSERT(false && "Cannot determine primitive type"); return sf::PrimitiveType::Triangles;
	}
}

void Renderer::Draw(const Vertex* vertices, uint32_t numVertices, PrimitiveType primitive)
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
	rw->draw(vertices, numVertices, GetSFMLPrimitiveType(primitive));
}

void Renderer::Draw(const Sprite* sprite)
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
	rw->draw(sprite->m_sprite);
}

void Renderer::Draw(const TextComponent* text)
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
	const sf::Text& sftext = *reinterpret_cast<const sf::Text*>(text->GetHandle());
	rw->draw(sftext);
}

#define KABANCHIKOM 1
void Renderer::DebugDraw(const Vec2& min, const Vec2& max)
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
#if KABANCHIKOM == 1
	Vertex vertices[5];
	vertices[0].position = min;
	vertices[1].position = Vec2(min.x, max.y);
	vertices[2].position = max;
	vertices[3].position = Vec2(max.x, min.y);
	vertices[4].position = min;
	rw->draw(vertices, 5, sf::LineStrip);
#elif KABANCHIKOM == 2
	Vertex vertices[2];
	vertices[0].position = min;
	vertices[1].position = max;
	rw->draw(vertices, 2, sf::Points);
#endif
}

void Renderer::DebugDraw(const Vec2& point)
{
	sf::RenderWindow* rw = reinterpret_cast<sf::RenderWindow*>(m_window->GetHandle());
	Vertex p;
	p.position = point;
	rw->draw(&p, 1, sf::Points);
}

Color ColorOf(const Vec3& rgb, float alpha)
{
	sf::Uint8 r = static_cast<sf::Uint8>(rgb.x * 255.0f);
	sf::Uint8 g = static_cast<sf::Uint8>(rgb.y * 255.0f);
	sf::Uint8 b = static_cast<sf::Uint8>(rgb.z * 255.0f);
	sf::Uint8 a = static_cast<sf::Uint8>(alpha * 255.0f);
	return Color(r, g, b, a);
}
