#include "Window.h"

#include "../Utility/Logger.h"

Window::Window(uint32_t width, uint32_t height, const std::string& title)
	: m_width(width)
	, m_height(height)
	, m_title(title)
{
}

Window::~Window()
{
}

bool Window::Open()
{
	bool creationResult = false;
	// If window was never created before - we allocate it
	if (!m_window)
	{
		m_window.reset(new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_title));
		LOG("Allocating a window {}", m_title);
	}
	else
	{
		m_window->close();
		m_window->create(sf::VideoMode(m_width, m_height), m_title);
		creationResult = true;
	}

	return creationResult;
}

bool Window::Close()
{
	if (!m_window)
	{
		LOG("Cannot close the window {} as it is not opened", m_title);
		return false;
	}

	m_window->close();
	return true;
}

void Window::PollEvents()
{
	if (!m_window)
		return;

	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
			m_window->close();

		// catch the resize events
		if (event.type == sf::Event::Resized)
		{
			m_width = static_cast<uint32_t>(event.size.width);
			m_height = static_cast<uint32_t>(event.size.height);
			EventBus::Get().Publish(WindowResizedEvent(this, m_width, m_height, m_viewsize));

			float zoom = m_viewsize / std::min(m_width, m_height);
			float scaledWidth = m_width * zoom;
			float scaledHeight = m_height * zoom;
			m_view.setSize(scaledWidth, scaledHeight);
			m_window->setView(m_view);
		}
	}
}

bool Window::ShouldClose() const
{
	if (!m_window)
		return true;

	return !m_window->isOpen();
}

void Window::SetViewport(float left, float top, float bottom, float right)
{
	sf::FloatRect rect;
	rect.left = left;
	rect.top = top;
	rect.width = right - left;
	rect.height = bottom - top;
	m_view.setViewport(rect);
	m_window->setView(m_view);
}

void Window::SetViewsize(float viewsize)
{
	m_viewsize = viewsize;
	float zoom = viewsize / std::min(m_width, m_height);
	float scaledWidth = m_width * zoom;
	float scaledHeight = m_height * zoom;
	m_view.setSize(scaledWidth, scaledHeight);
	m_view.setCenter(viewsize / 2.0f, viewsize / 2.0f);
	m_window->setView(m_view);
}
