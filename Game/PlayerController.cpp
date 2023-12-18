#include "PlayerController.h"
#include "Player.h"

PlayerController::PlayerController(Player* player)
    : m_player(player)
{
}

void PlayerController::OnUpdate(float timestep)
{
    if (!m_player)
        return;

    using namespace sf;
    if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
    {
        OnMoveUp(timestep);
    }
    else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
    {
        OnMoveDown(timestep);
    }
    else if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
    {
        OnMoveLeft(timestep);
    }
    else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
    {
        OnMoveRight(timestep);
    }
}

void PlayerController::OnMoveUp(float timestep)
{
    m_player->SetDirection(DIRECTION_UP);
    Vec2 offset(0.0f, -timestep * m_speed);
    m_player->AddPosition(offset);
}

void PlayerController::OnMoveDown(float timestep)
{
    m_player->SetDirection(DIRECTION_DOWN);
    Vec2 offset(0.0f, timestep * m_speed);
    m_player->AddPosition(offset);
}

void PlayerController::OnMoveLeft(float timestep)
{
    m_player->SetDirection(DIRECTION_LEFT);
    Vec2 offset(-timestep * m_speed, 0.0f);
    m_player->AddPosition(offset);
}

void PlayerController::OnMoveRight(float timestep)
{
    m_player->SetDirection(DIRECTION_RIGHT);
    Vec2 offset(timestep * m_speed, 0.0f);
    m_player->AddPosition(offset);
}
