#include "pch.h"
#include "Maze.h"

Maze::Maze(EntityFactory* entityFactory, Renderer* renderer)
    : m_entityFactory(entityFactory)
    , m_renderer(renderer)
    , m_width(0)
    , m_height(0)
{
}

bool Maze::Init(const std::string& filepath)
{
    m_grid.clear();
    m_textureWidth = TextureAtlas::Get().GetTextureWidth();
    m_textureHeight = TextureAtlas::Get().GetTextureHeight();
    ParseMazeImage(filepath);
    return true;
}

Tile* Maze::GetTile(uint32_t x, uint32_t y){
    return m_grid[x][y];
}

void Maze::Draw()
{
    for (uint32_t x = 0; x < m_width; ++x)
    {
        for (uint32_t y = 0; y < m_height; ++y)
        {
            Sprite* sprite = m_grid[x][y]->GetSprite();
            sprite->SetPosition(Vec2(static_cast<float>(x * m_textureWidth), static_cast<float>(y * m_textureHeight)));
            m_renderer->Draw(sprite);
        }
    }

    //// TODO: remove temp
    //for (auto [x, y] : m_path)
    //{
    //    const Tile* tile = this->At(x, y);
    //    m_renderer->DebugDraw(tile->GetAABB().min, tile->GetAABB().max);
    //}
}

Vec2 Maze::GetPosition(uint32_t x, uint32_t y) const
{
    return Vec2(static_cast<float>(x * m_textureWidth), static_cast<float>(y * m_textureHeight));
}

Vec2 Maze::GetCenterPosition() const
{
    return GetPosition(m_width / 2, m_height / 2);
}

float Maze::GetViewsize() const
{
    float viewsize = std::min(static_cast<float>(m_width) * m_textureWidth, static_cast<float>(m_height) * m_textureHeight);
    return viewsize;
}

void Maze::ParseMazeImage(const std::string& filepath)
{
    std::ifstream mazeImageFile(filepath);

    if (!mazeImageFile.is_open())
    {
        LOG("Failed to open maze image file");
        return;
    }

    std::ostringstream oss;
    std::string line;

    while (std::getline(mazeImageFile, line))
        oss << line;

    std::string mazeString = oss.str();

    m_width = static_cast<uint32_t>(line.size());
    m_height = static_cast<uint32_t>(mazeString.size()) / m_width;

    // Resize the grid
    m_grid.resize(m_width);
    for (auto& col : m_grid)
        col.resize(m_height);

    for (uint32_t x = 0; x < m_width; ++x)
    {
        for (uint32_t y = 0; y < m_height; ++y)
        {
            Vec2 pos = this->GetPosition(x, y);
            size_t index = x + m_width * y;
            bool isWall = mazeString[index] == '0';
            uint32_t i = RandomGenerator::GenerateNumber(0, 2);
            TextureType type = isWall ? TextureType(TEXTURE_DUNGEON_WALL1 + i) : TextureType(TEXTURE_DUNGEON_TILE2 + i);
            Tile* tile = m_entityFactory->RegisterEntity<Tile>(pos, BoundingBox(pos, static_cast<float>(m_textureWidth), static_cast<float>(m_textureHeight)), type, isWall);
            m_grid[x][y] = tile;
        }
    }

    mazeImageFile.close();
}
