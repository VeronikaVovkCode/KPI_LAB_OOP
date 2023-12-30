#pragma once

#include <vector>
#include "../Core/Texture.h"

enum TextureType // Changed to enum class for stronger typing
{
    TEXTURE_DUNGEON_TILE,
    TEXTURE_DUNGEON_WALL1,
    TEXTURE_DUNGEON_WALL2,
    TEXTURE_DUNGEON_WALL3,
    TEXTURE_SLIME_GREEN_IDLE,
    TEXTURE_SLIME_GREEN_JUMPING,
    TEXTURE_SLIME_BLUE_IDLE,
    TEXTURE_SLIME_BLUE_JUMPING,
    TEXTURE_SLIME_RED_IDLE,
    TEXTURE_SLIME_RED_JUMPING,
    TEXTURE_SLIME_YELLOW_IDLE,
    TEXTURE_SLIME_YELLOW_JUMPING,
    TEXTURE_SLIME_PURPLE_IDLE,
    TEXTURE_SLIME_PURPLE_JUMPING,
    TEXTURE_HEART,
    TEXTURE_WAND,
    TEXTURE_PLAYER_FRONT,
    TEXTURE_PLAYER_BACK,
    TEXTURE_PLAYER_LEFT,
    TEXTURE_PLAYER_RIGHT,
    TEXTURE_COIN1,
    TEXTURE_COIN2,
    TEXTURE_COIN3,
    TEXTURE_COIN4,
    TEXTURE_SKULL,
    TEXTURE_DUNGEON_TILE2,
    TEXTURE_DUNGEON_TILE3,
    TEXTURE_DUNGEON_TILE4,
    TEXTURE_PLAYER_IMMUNE_FRONT,
    TEXTURE_PLAYER_IMMUNE_BACK,
    TEXTURE_PLAYER_IMMUNE_LEFT,
    TEXTURE_PLAYER_IMMUNE_RIGHT,
    NUM_TEXTURES,
};

class TextureAtlas
{
private:
    TextureAtlas();

public:
    TextureAtlas(const TextureAtlas&) = delete;
    TextureAtlas& operator=(const TextureAtlas&) = delete;

    static TextureAtlas& Get();

    Texture* GetTexture(TextureType textureType);
    inline uint32_t GetTextureWidth() const { return m_textureWidth; }
    inline uint32_t GetTextureHeight() const { return m_textureHeight; }

private:
    std::vector<Texture*> m_textures;
    uint32_t m_textureWidth;
    uint32_t m_textureHeight;
};
