#pragma once
#include "Window.h"
#include "Renderer.h"
#include "../Utility/FileSystem.h"
#include "../Game/TextureAtlas.h"
#include "../Game/Level.h"
#include "../UI/UI.h"

class App
{
public:
    App();
    ~App();
    int Go();
private:
    void DoFrame(float timestep);
    void HandleInput(float timestep);
private:
    Window m_wnd;
    Renderer m_renderer;
    FileSystem& m_filesystem;
    TextureAtlas& m_atlas;
    Level m_level;
    UI m_ui;
};
