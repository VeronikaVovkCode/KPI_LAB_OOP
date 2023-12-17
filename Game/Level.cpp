#include "Level.h"

#include <cstdlib>
#include "../Audio/AudioManager.h"
#include "AnimationManager.h"
#include "Coin.h"
#include "Slimes.h"
#include "Tile.h"
#include "../Utility/Logger.h"
#include "../Utility/RandomGenerator.h"

Level::Level(Renderer* renderer)
    : m_renderer(renderer), m_overallCoinsNumber(10), m_gameIsOver(false)
{
}

bool Level::Init(const std::string& filepath)
{
    m_entityFactory.reset(new EntityFactory());

    m_maze.reset(new Maze(m_entityFactory.get(), m_renderer));
    m_maze->Init(filepath);

    Vec2 playerPos = m_maze->GetCenterPosition();
    Player* player = m_entityFactory->RegisterEntity<Player>(playerPos, BoundingBox(playerPos, 16.0f, 16.0f));
    m_playerController.reset(new PlayerController(player));

    Vec2 topLeft = m_maze->GetPosition(1, 1);
    Vec2 bottomRight = m_maze->GetPosition(m_maze->GetWidth() - 2, m_maze->GetHeight() - 2);

    Vec2 slimes[4];
    slimes[0] = topLeft;
    slimes[1] = Vec2(topLeft.x, bottomRight.y);
    slimes[2] = bottomRight;
    slimes[3] = Vec2(bottomRight.x, topLeft.y);
    for (uint32_t i = 0; i < 4; ++i)
    {
        Slime* slime = m_entityFactory->RegisterEntity<Slime>(slimes[i], BoundingBox(slimes[i], 16.0f, 16.0f));
        uint32_t rx = static_cast<uint32_t>(slimes[i].x / m_maze->GetTextureWidth());
        uint32_t ry = static_cast<uint32_t>(slimes[i].y / m_maze->GetTextureHeight());
        uint32_t gx = RandomGenerator::GenerateNumber(0, m_maze->GetWidth() - 1);
        uint32_t gy = RandomGenerator::GenerateNumber(0, m_maze->GetHeight() - 1);
        while (m_maze->At(gx, gy)->IsCollider())
        {
            gx = RandomGenerator::GenerateNumber(0, m_maze->GetWidth() - 1);
            gy = RandomGenerator::GenerateNumber(0, m_maze->GetHeight() - 1);
        }
        m_pathfinder.Init(m_maze->GetGrid(), rx, ry, gx, gy);

        auto& r = m_pathfinder.GetPath();
        std::vector<Vec2> path;
        path.reserve(r.size());
        for (auto [x, y] : r)
            path.push_back(m_maze->GetPosition(x, y));

        slime->SetPath(path);
        uint32_t rf = RandomGenerator::GenerateNumber(0, 5);
        float factor = rf / 10.0f;
        slime->SetTilesPerSec(4.0f * (1.0f + factor));
    }

    uint32_t w = m_maze->GetWidth();
    uint32_t h = m_maze->GetHeight();
    for (uint32_t i = 0; i < m_overallCoinsNumber;)
    {
        uint32_t x = RandomGenerator::GenerateNumber(0, w - 1);
        uint32_t y = RandomGenerator::GenerateNumber(0, h - 1);
        Vec2 pos = m_maze->GetPosition(x, y);
        if (!m_maze->At(x, y)->IsCollider())
        {
            m_entityFactory->RegisterEntity<Coin>(pos, BoundingBox(pos, 16.0f, 16.0f));
            ++i;
        }
    }

    //EventBus::Get().subscribe(this, &Level::OnWindowResize);

    AudioManager::Get().PlaySound(AUDIO_DUBSTEP, 1.5f, 5.0f);
    return true;
}

void Level::OnUpdate(float timestep)
{
    AnimationManager::Get().OnUpdate(timestep);
    m_maze->Draw();

    if (m_gameIsOver)
    {
        return;
    }

    Player* player = (Player*) m_entityFactory->GetEntities<ENTITY_PLAYER>().front();
    player->OnUpdate(timestep);

    // Player-Tile collisions and Tile drawing
    for (Entity* entity : m_entityFactory->GetEntities<ENTITY_TILE>())
    {
        Tile* tile = (Tile*)entity;
        // tile->OnUpdate(timestep);
        if (tile->IsCollider() && tile->Collide(player))
        {
            tile->OnEntityCollision(player);
            player->OnEntityCollision(tile);
            break;
        }
    }
    
    m_renderer->Draw(player->GetSprite());
    if (player->CanMove()) // Only update player controller if the player can move
        m_playerController->OnUpdate(timestep);

    // Player-Coin collisions and coin drawing
    for (Entity* e : m_entityFactory->GetEntities<ENTITY_COIN>())
    {
        e->OnUpdate(timestep);
        if (player->Collide(e))
        {
            player->OnEntityCollision(e);
            e->OnEntityCollision(player); // Actually coin does nothing here
            m_entityFactory->DestroyEntity(e);
        }
        m_renderer->Draw(e->GetSprite());
    }

    for (Entity* e : m_entityFactory->GetEntities<ENTITY_ENEMY>())
    {
        Slime* slime = (Slime*)e;
        slime->OnUpdate(timestep);
        if (slime->IsArrived())
        {            
            Vec2 slimepos = slime->GetPosition();
            uint32_t rx = static_cast<uint32_t>(slimepos.x / m_maze->GetTextureWidth());
            uint32_t ry = static_cast<uint32_t>(slimepos.y / m_maze->GetTextureHeight());

            Vec2 playerpos = player->GetCenterPos();
            uint32_t gx = static_cast<uint32_t>(playerpos.x / m_maze->GetTextureWidth());
            uint32_t gy = static_cast<uint32_t>(playerpos.y / m_maze->GetTextureHeight());
            m_pathfinder.Init(m_maze->GetGrid(), rx, ry, gx, gy);

            auto& r = m_pathfinder.GetPath();
            std::vector<Vec2> path;
            path.reserve(r.size());
            for (auto [x, y] : r)
                path.push_back(m_maze->GetPosition(x, y));

            slime->SetPath(path);
        }

        if (player->Collide(slime))
        {
            if (!player->IsImmune())
                player->SetPosition(m_maze->GetCenterPosition());

            slime->OnEntityCollision(player);
            player->OnEntityCollision(slime);
            
            if (player->GetHealth() == 0)
            {
                // End the game
                //m_isOver = true;
            }
        }
        m_renderer->Draw(slime->GetSprite());
    }

    m_gameIsOver = player->GetHealth() == 0 || player->GetCollectedCoins() == m_overallCoinsNumber;
}
