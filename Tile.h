#ifndef TILE_H_
#define TILE_H_
#include "LTexture.h"
class Tile
{
public:

    // Initialize position and type of tile
    Tile(int x, int y, int TileType);

    // Show the tiles ( Render )
    void Tile_Render( SDL_Rect& camera);

    // Get tile type
    int GetTileType();

    int SetType(int type);

    // Get the collision box
    SDL_Rect GetBox();

    // Solid block check
    bool CheckSolidTile(int type);

    // Spike block check
    bool IsSpikeBlock(int type);

    bool IsMoneyBlock(int type);

    bool IsBlackMoneyBlock(int type);

    bool IsGrassBlock(int type);

private:
    // The attributes of the tile
    SDL_Rect mBox;

    // The tile type
    int mType;

    // Solid block check flag
    bool IsSolid;
};
#endif // TILE_H_
