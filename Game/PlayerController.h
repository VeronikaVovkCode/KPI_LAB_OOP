#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"

class PlayerController
{
public:
    PlayerController(Player* player);

    void OnUpdate(float timestep);
    void OnMoveUp(float timestep);
    void OnMoveDown(float timestep);
    void OnMoveLeft(float timestep);
    void OnMoveRight(float timestep);

private:
    Player* m_player;
    float m_speed = 200.0f;
};
