#include "pch.h"

App::App()
	: m_wnd(800, 600, "Pacman?")
	, m_filesystem(FileSystem::Get())
	, m_atlas(TextureAtlas::Get())
	, m_level(&m_renderer)
	, m_ui(&m_renderer)
{
	RandomGenerator::SetSeed(0);

	m_wnd.Open();

	m_renderer.Init(&m_wnd);

	if (!AudioManager::Init())
		LOG("Failed to initialize Audio Manager");

	m_level.Init((m_filesystem.GetAssetsPath() / "Maze2.txt").string());
	m_wnd.SetViewsize(m_level.GetMaze()->GetViewsize());

	m_ui.Init();
}

App::~App()
{
	AudioManager::Deinit();
}

int App::Go()
{
	Timer timer;
	while (!m_wnd.ShouldClose())
	{
		m_wnd.PollEvents();
		m_wnd.PollInput();
		const float timestep = timer.Mark();
		DoFrame(timestep);
		HandleInput(timestep);
	}
	return 0;
}

void App::DoFrame(float timestep)
{
	FrameDesc frameDesc;
	frameDesc.clearcolor[0] = 0.0f;
	frameDesc.clearcolor[1] = 0.0f;
	frameDesc.clearcolor[2] = 0.0f;
	frameDesc.clearcolor[3] = 1.0f;

	m_renderer.BeginFrame(frameDesc);
	m_renderer.SetViewport(Vec2(0.1f, 0.0f), Vec2(0.9f, 0.8f));
	m_level.OnUpdate(timestep);

	m_renderer.SetViewport(Vec2(0.1f, 0.8f), Vec2(0.9f, 1.0f));
	m_ui.SetLevelInfo({ m_level.GetPlayer()->GetCollectedCoins(), m_level.GetOverallCoinsNumber(), m_level.GetPlayer()->GetHealth() });
	m_ui.OnUpdate(timestep);

	m_renderer.EndFrame();
}

void App::HandleInput(float timestep)
{
	while (const auto key = m_wnd.m_keyboard.ReadKey())
	{
		if (!key->isPressed())
		{
			continue;
		}

		switch (key->GetCode())
		{
		case sf::Keyboard::Key::Escape:
			break;
		case sf::Keyboard::Key::W:
			if (m_level.GetPlayer()->CanMove())
			{
				m_level.m_playerController->OnMoveUp(timestep);
			}
			break;
		case sf::Keyboard::Key::A:
			if (m_level.GetPlayer()->CanMove())
			{
				m_level.m_playerController->OnMoveLeft(timestep);
			}
			break;
		case sf::Keyboard::Key::S:
			if (m_level.GetPlayer()->CanMove())
			{
				m_level.m_playerController->OnMoveDown(timestep);
			}
			break;
		case sf::Keyboard::Key::D:
			if (m_level.GetPlayer()->CanMove())
			{
				m_level.m_playerController->OnMoveRight(timestep);
			}
			break;
		default:
			break;
		}
	}
}
