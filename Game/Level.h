#pragma once

#include <memory>
#include <vector>
#include "../Core/Renderer.h"
#include "Entity.h"
#include "Maze.h"
#include "Player.h"
#include "PlayerController.h"

class Level
{
public:
    Level(Renderer* renderer);
    
    bool Init(const std::string& filepath);
    void OnUpdate(float timestep);
    inline Maze* GetMaze() { return m_maze.get(); }
    inline Player* GetPlayer() { return (Player*) m_entityFactory->GetEntities<ENTITY_PLAYER>().front(); }
    inline uint32_t GetOverallCoinsNumber() const { return m_overallCoinsNumber; }
    inline void SetOverallCoinsNumber(uint32_t coinsNumber) { m_overallCoinsNumber = coinsNumber; }
    inline bool GameIsOver() const { return m_gameIsOver; }

private:
    Renderer* m_renderer;
    Pathfinder m_pathfinder;
    bool m_isOver = false;
    std::unique_ptr<Maze> m_maze;
    std::unique_ptr<EntityFactory> m_entityFactory = nullptr;
    std::unique_ptr<PlayerController> m_playerController;
    uint32_t m_overallCoinsNumber;
    bool m_gameIsOver;
};
