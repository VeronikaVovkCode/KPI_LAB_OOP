#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

#include "../Utility/EventBus.h"

class Window
{
public:
	Window(uint32_t width, uint32_t height, const std::string& title);
	~Window();

	bool Open();
	bool Close();
	void PollEvents();
	bool ShouldClose() const;
	void SetViewport(float left, float top, float bottom, float right);
	void SetViewsize(float viewsize);
	float GetViewsize() const { return m_viewsize; }

	constexpr uint32_t GetWidth() const { return m_width; }
	constexpr uint32_t GetHeight() const { return m_height; }
	const std::string& GetTitle() const { return m_title; }

	void* GetHandle() { return m_window.get(); }

private:
	float m_viewsize = 0.0f;	
	uint32_t m_width;
	uint32_t m_height;
	std::string m_title;
	std::unique_ptr<sf::RenderWindow> m_window;
	sf::View m_view;
};

struct WindowResizedEvent
	: Event
{
	Window* window;
	uint32_t width;
	uint32_t height;
	float viewsize;

	WindowResizedEvent(Window* windowHandle, uint32_t uWidth, uint32_t uHeight, float fViewsize)
		: window(windowHandle), width(uWidth), height(uHeight), viewsize(fViewsize) {}
};
