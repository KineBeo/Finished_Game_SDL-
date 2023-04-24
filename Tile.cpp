#include "Tile.h"
#include "Constants.h"
#include "Global.h"
#include "UTIL.h"

Tile::Tile(int x, int y, int TileType)
{
    mBox.x = x;
    mBox.y = y;

    // Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    // Get the tile type
    mType = TileType;
    IsSolid = false;
}

void Tile::Tile_Render(SDL_Rect &camera)
{
    // if the tile is on screen
    if (CheckCollision(camera, mBox))
    {
        // Show the tile
        g_TileTexure.Render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[ mType ]);
        if (CheckSolidTile(mType))
        {
            IsSolid = true;
        }
        else
        {
            IsSolid = false;
        }
    }
}

int Tile::GetTileType()
{
    return mType;
}

int Tile::SetType(int type)
{
    mType = type;
}
SDL_Rect Tile::GetBox()
{
    return mBox;
}

bool Tile::CheckSolidTile(int type)
{
    switch (type)
    {
    // Simple dirt
    case TILE_GRASS_TOP_LEFT:
    case TILE_GRASS_TOP:
    case TILE_GRASS_TOP_RIGHT:
    case TILE_LEFT_DIRT:
    case TILE_CENTER_DIRT:
    case TILE_RIGHT_DIRT:
    case TILE_BOTTOM_LEFT_DIRT:
    case TILE_BOTTOM_DIRT:
    case TILE_BOTTOM_RIGHT_DIRT:

    // Concrete block
    case TILE_TOP_LEFT_CONCRETE:
    case TILE_TOP_CONCRETE:
    case TILE_TOP_RIGHT_CONCRETE:
    case TILE_LEFT_CONCRETE:
    case TILE_CENTER_CONCRETE:
    case TILE_RIGHT_CONCRETE:
    case TILE_BOTTOM_LEFT_CONCRETE:
    case TILE_BOTTOM_CONCRETE:
    case TILE_BOTTOM_RIGHT_CONCRETE:

    // Decoration and support block
    case TILE_WOODEN_BOX:
    case TILE_COARSE_DIRT:
    case TILE_HORIZONTAL_BRIDGE:
    case TILE_LEFT_FLOATING_DIRT:
    case TILE_CENTER_FLOATING_DIRT:
    case TILE_RIGHT_FLOATING_DIRT:
    case TILE_G_BLOCK:

    // Stick block
    case TILE_STICK_ATTACH_GROUND_1:
    case TILE_STICK_ATTACH_GROUND_2:
    case TILE_RIGHT_STICK_ATTACH_GROUND_1:
    case TILE_RIGHT_STICK_ATTACH_GROUND_2:
    case TILE_BLACK_STICK_1:
    case TILE_BLACK_STICK_2:
    case TILE_BLACK_STICK_3:
    case TILE_BLACK_STICK_4:

    // Big block
    case TILE_BIG_WOODEN_BOX_1:
    case TILE_BIG_WOODEN_BOX_2:
    case TILE_BIG_WOODEN_BOX_3:
    case TILE_BIG_WOODEN_BOX_4:
    case TILE_DEMON_BLOCK_1:
    case TILE_DEMON_BLOCK_2:
    case TILE_DEMON_BLOCK_3:
    case TILE_DEMON_BLOCK_4:
    case TILE_TWIN_WOODEN_BOX_1:
    case TILE_TWIN_WOODEN_BOX_2:

        return true;
    default:
        return false;
    }
}

bool Tile::IsSpikeBlock(int type)
{
    if (type == TILE_SPIKE || type == TILE_TOP_SPIKE || type == TILE_BLACK_SPIKE_BLOCK)
    {
        return true;
    }
    return false;
}

bool Tile::IsMoneyBlock(int type)
{
    if (type == TILE_GEM || type == TILE_CHERRY)
    {
        return true;
    }
    return false;
}
bool Tile::IsBlackMoneyBlock(int type)
{
    if (type == TILE_BLACK_CHERRY || type == TILE_BLACK_GEM)
    {
        return true;
    }
    return false;
}

bool Tile::IsGrassBlock(int type)
{
    if (type == TILE_GRASS_TOP || type == TILE_GRASS_TOP_LEFT || type == TILE_GRASS_TOP_RIGHT)
    {
        return true;
    }
    return false;
}
