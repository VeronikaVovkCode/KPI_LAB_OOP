#include "pch.h"

// Define a map to store the top and left positions of textures in the atlas
static constexpr std::array g_atlasPositions = {
    std::pair<uint32_t, uint32_t>{0, 0},
    std::pair<uint32_t, uint32_t>{0, 1},
    std::pair<uint32_t, uint32_t>{0, 2},
    std::pair<uint32_t, uint32_t>{0, 3},
    std::pair<uint32_t, uint32_t>{1, 0},
    std::pair<uint32_t, uint32_t>{1, 1},
    std::pair<uint32_t, uint32_t>{1, 2},
    std::pair<uint32_t, uint32_t>{1, 3},
    std::pair<uint32_t, uint32_t>{2, 0},
    std::pair<uint32_t, uint32_t>{2, 1},
    std::pair<uint32_t, uint32_t>{2, 2}, // hearth
    std::pair<uint32_t, uint32_t>{2, 3}, // wand
    std::pair<uint32_t, uint32_t>{3, 0},
    std::pair<uint32_t, uint32_t>{3, 1},
    std::pair<uint32_t, uint32_t>{3, 2},
    std::pair<uint32_t, uint32_t>{3, 3},
    std::pair<uint32_t, uint32_t>{4, 0},
    std::pair<uint32_t, uint32_t>{4, 1},
    std::pair<uint32_t, uint32_t>{4, 2},
    std::pair<uint32_t, uint32_t>{4, 3},
    std::pair<uint32_t, uint32_t>{5, 0},
    std::pair<uint32_t, uint32_t>{5, 1},
    std::pair<uint32_t, uint32_t>{5, 2},
    std::pair<uint32_t, uint32_t>{5, 3},
    std::pair<uint32_t, uint32_t>{6, 0}, // skull
    std::pair<uint32_t, uint32_t>{6, 1}, // flor2
    std::pair<uint32_t, uint32_t>{6, 2}, // flor3
    std::pair<uint32_t, uint32_t>{6, 3},  // flor4
    std::pair<uint32_t, uint32_t>{7, 0}, // pimmune
    std::pair<uint32_t, uint32_t>{7, 1}, // pimmune
    std::pair<uint32_t, uint32_t>{7, 2}, // pimmune
    std::pair<uint32_t, uint32_t>{7, 3}, // pimmune
};

TextureAtlas::TextureAtlas()
    : m_textureWidth(32)
    , m_textureHeight(32)
{
    static std::string filepath = (FileSystem::Get().GetAssetsPath() / "atlas.png").string();
    TextureLibrary& library = TextureLibrary::Get();

    for (auto [top, left] : g_atlasPositions)
        m_textures.push_back(library.CreateTexture(filepath, top * m_textureHeight, left * m_textureWidth, m_textureWidth, m_textureHeight));
}

TextureAtlas& TextureAtlas::Get()
{
    static TextureAtlas instance;
    return instance;
}

Texture* TextureAtlas::GetTexture(TextureType textureType)
{
    ASSERT(textureType < g_atlasPositions.size());
    if (textureType >= g_atlasPositions.size())
        return nullptr;

    return m_textures.at(textureType);
}
