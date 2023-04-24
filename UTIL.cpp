#include "UTIL.h"
#include "Constants.h"
#include "LTexture.h"
#include "Global.h"
#include "Fox.h"
#include <fstream>
bool Init()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if ( ret < 0 )
    {
        success = false;
    }
    else
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        // create window
        g_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
        if (g_window == NULL)
        {
            success = false;
        }
        else
        {
            // create renderer for window
            g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (g_screen == NULL)
            {
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

                // Initialize PNG loading (SDL_image initialize)
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) && imgFlags))
                {
                    success = false;
                }
                // Initialize TTF
                if (TTF_Init() == -1)
                {
                    success = false;
                }
                // Initialize Mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    success = false;
                }
            }
        }
    }
    return success;
}
bool LoadBackGround()
{
    bool success = true;
    if(!g_background.LoadImageFromFile("img/Background/background.png"))
    {
        cout << "Failed to load background! \n";
        success = false;
    }
    if (!g_middle_background.LoadImageFromFile("img/Background/middle.png"))
    {
        cout << "Failed to load middle background! \n";
        success = false;
    }
    if (!g_tutorial.LoadImageFromFile("img/Background/Tutorial.png"))
    {
        success = false;
    }
    if (!PressEnter.LoadImageFromFile("img/Background/PressEnter.png"))
    {
        success = false;
    }
    if (!StateBar.LoadImageFromFile("img/StateBar.png"))
    {
        success = false;
    }
    if (!Heart.LoadImageFromFile("img/Heart.png"))
    {
        success = false;
    }
    if (!NumFireballInStateBar.LoadImageFromFile("img/FireballBonus.png"))
    {
        success = false;
    }
    return success;

}
bool LoadMap(Tile* tiles[], int& current_level)
{
    // Load Tile map
    bool success = true;

    // Load TileSet image
    if ( !g_TileTexure.LoadImageFromFile("img/Tiles.png"))
    {
        cout << "Failed to load tile map sheet! \n";
        success = false;
    }

    // Load tiles map
    string path = "map/CompleteMap" + to_string(current_level) + ".map";
    if (!SetTiles(tiles, path.c_str()))
    {
        cout << "Failed to load tile map! \n";
        success = false;
    }

    return success;
}
bool LoadFont()
{
    bool success = true;
    // Open the font
    gFont = TTF_OpenFont("font/Font.ttf", 30);
    if (gFont == NULL)
    {
        success = false;
    }
    return success;
}

bool LoadMusic()
{
    bool success = true;
    gSoundTrack = Mix_LoadMUS("sound/SpyXFamily.mp3");
    gButtonClick = Mix_LoadWAV("sound/ButtonClick.wav");
    gFootStepOnGrass = Mix_LoadWAV("sound/FootStepOnGrass.wav");
    gFireBallWhoosh = Mix_LoadWAV("sound/Fireball.wav");
    gExplosion = Mix_LoadWAV("sound/Explosion.wav");
    gCoin = Mix_LoadWAV("sound/Cherry.wav");
    if (gButtonClick == NULL)
    {
        success = false;
    }
    if (gSoundTrack == NULL)
    {
        success = false;
    }
    if (gFootStepOnGrass == NULL)
    {
        success = false;
    }
    if (gFireBallWhoosh == NULL)
    {
        success = false;
    }
    if (gExplosion == NULL)
    {
        success = false;
    }
    if (gCoin == NULL)
    {
        success = false;
    }
    return success;
}
void LoadAllCharacter()
{

}
void SetEnemyPosition()
{

}
void RenderEnemy(SDL_Rect& camera)
{

}
void CharacterMove(Tile* tileSet[])
{

}
void Close(Tile* tiles[])
{
    // Deallocates tiles
    for (int i = 1; i <= TOTAL_TILE_SPRITES; i++)
    {
        if ( tiles[i] != NULL)
        {
            delete tiles[i];
            tiles[i] = NULL;
        }
    }
    // Free loaded image
    g_background.Free();
    g_middle_background.Free();
    g_TileTexure.Free();
    g_FoxRunTexture.Free();
    g_FoxJumpTexture.Free();
    g_FoxHurtTexture.Free();
    g_FoxIdleTexture.Free();
    game_over.Free();
    g_Death_count.Free();

    // Destroy window
    SDL_DestroyWindow(g_window);
    SDL_DestroyRenderer(g_screen);
    g_window = NULL;
    g_screen = NULL;

    // Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;

    // Free sound effect
    Mix_FreeChunk(gButtonClick);
    Mix_FreeChunk(gExplosion);
    Mix_FreeChunk(gFootStepOnGrass);
    Mix_FreeChunk(gFireBallWhoosh);
    Mix_FreeMusic(gSoundTrack);
    Mix_FreeChunk(gCoin);
    gButtonClick = NULL;
    gExplosion = NULL;
    gFootStepOnGrass = NULL;
    gFireBallWhoosh = NULL;
    gSoundTrack = NULL;
    gCoin = NULL;

    // Quit SDL
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}
bool CheckCollision(SDL_Rect a, SDL_Rect b)
{
    // The sides of rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // if any of sides from A are outside of B
    if ( bottomA <= topB )
    {
        return false;
    }

    if ( topA >= bottomB )
    {
        return false;
    }

    if ( rightA <= leftB )
    {
        return false;
    }

    if ( leftA >= rightB)
    {
        return false;
    }
    return true;
}
bool SetTiles(Tile* tiles[], string path)
{
    bool TilesLoad = true;

    // the tile offsets
    int x = 0, y = 0;

    // open the map
    ifstream map(path.c_str());

    // if map couldn't be loaded
    if ( map.fail())
    {
        cout << "Unable to load map file! \n";
        TilesLoad = false;
    }
    else
    {
        // Initialize tiles
        for (int i = 0; i < TOTAL_TILES ; i++)
        {
            // Determine what kind of tile will be made
            int TileType = -1;

            // Read tile from map tile
            map >> TileType;

            // if the was a problem in reading the map
            if (map.fail())
            {
                // stop loading map
                cout << "Error: Unexpected end of file! \n";
                TilesLoad = false;
                break;
            }

            // if the number is a valid tile number
            if ( (TileType >= 0) && (TileType <= TOTAL_TILE_SPRITES))
            {
                tiles[i] = new Tile(x, y, TileType);
            }
            // if we don't recognize the tile type
            else
            {
                cout << "Error loading map: Invalid tile type! \n";
                TilesLoad = false;
                break;
            }
            // Move to next tile spot
            x += TILE_WIDTH;

            // if we're gone too far
            if ( x >= LEVER_WIDTH )
            {
                // move back
                x = 0;

                // move the next row
                y += TILE_HEIGHT;
            }
        }
        // clip the sprite sheet
        if ( TilesLoad )
        {
            // Row 1 Texture
            for (int i = TILE_GRASS_TOP_LEFT; i <= TILE_TOP_RIGHT_CONCRETE; i++)
            {
                gTileClips[i] = {(i-TILE_GRASS_TOP_LEFT) * 64, 0, TILE_WIDTH, TILE_HEIGHT };
            }

            // Row 2 Texture
            for (int i = TILE_LEFT_DIRT; i <= TILE_RIGHT_CONCRETE; i++)
            {
                gTileClips[i] = {(i-TILE_LEFT_DIRT) * 64, 64, TILE_WIDTH, TILE_HEIGHT };
            }

            // Row 3 Texture
            for (int i = TILE_BOTTOM_LEFT_DIRT; i <= TILE_BOTTOM_RIGHT_CONCRETE; i++)
            {
                gTileClips[i] = {(i-TILE_BOTTOM_LEFT_DIRT) * 64, 128, TILE_WIDTH, TILE_HEIGHT };
            }

            // Row 4 Texture
            for (int i = TILE_VERTICAL_BRIDGE; i <= TILE_RIGHT_LEAVES; i++)
            {
                gTileClips[i] = {(i-TILE_VERTICAL_BRIDGE) * 64, 192, TILE_WIDTH, TILE_HEIGHT};
            }

            // Row 5 Texture
            for (int i = TILE_MUSHROOM; i <= TILE_CAVE_BRICK; i++)
            {
                gTileClips[i] = {(i-TILE_MUSHROOM) * 64, 256, TILE_WIDTH, TILE_HEIGHT};
            }

            // Row 6 Texture
            for (int i = TILE_DIAGONAL_DIRT_TYPE_RIGHT_1; i <= TILE_CAVE_LEAVES_2; i++)
            {
                gTileClips[i] = {(i-TILE_DIAGONAL_DIRT_TYPE_RIGHT_1) * 64, 320, TILE_WIDTH, TILE_HEIGHT};
            }

            // Row 7 Texture
            for (int i = TILE_BIG_RIGHT_DIRT_1; i <= TILE_RIGHT_STICK_ATTACH_GROUND_2; i++)
            {
                gTileClips[i] = {(i-TILE_BIG_RIGHT_DIRT_1) * 64, 384, TILE_WIDTH, TILE_HEIGHT};
            }

            // Row 8 Texture
            for (int i = TILE_SPIKE; i <= TILE_BIG_LEFT_DIRT_7; i++)
            {
                gTileClips[i] = {(i-TILE_SPIKE) * 64, 448, TILE_WIDTH, TILE_HEIGHT};
            }

            // Row 9 Texture
            for (int i = TILE_BIG_GRASS_1; i <= TILE_BIG_WOODEN_BOX_2; i++)
            {
                gTileClips[i] = {(i-TILE_BIG_GRASS_1) * 64, 512, TILE_WIDTH, TILE_HEIGHT};
            }

            // Row 10 Texture
            for (int i = TILE_BIG_GRASS_4; i <= TILE_BIG_WOODEN_BOX_4; i++)
            {
                gTileClips[i] = {(i-TILE_BIG_GRASS_4) * 64, 576, TILE_WIDTH, TILE_HEIGHT};
            }

            // Row 11 Texture
            for (int i = TILE_BLACK_STICK_1; i <= TILE_TWIN_WOODEN_BOX_2; i++)
            {
                gTileClips[i] = {(i-TILE_BLACK_STICK_1) * 64, 640, TILE_WIDTH, TILE_HEIGHT};
            }

            // Row 12 Texture
            for (int i = TILE_GEM; i <= TILE_FIREBALL_BONUS; i++)
            {
                gTileClips[i] = {(i-TILE_GEM) * 64, 704, TILE_WIDTH, TILE_HEIGHT};
            }
        }
        // close the file
        map.close();
    }
    // if the is loaded
    return TilesLoad;
}
bool TouchesWall(SDL_Rect box, Tile* tiles[])
{
    // go through the tiles
    for (int i = 0; i  < TOTAL_TILES; i++)
    {
        // if tile is solid block
        if (tiles[i]->CheckSolidTile(tiles[i]->GetTileType()))
        {
            // check character's collision with solid box
            if (CheckCollision(box, tiles[i]->GetBox()))
            {
                return true;
            }
        }
    }
    return false;
}
void RenderBackGround()
{
    // Render main background image
    g_background.Render(0, 0, NULL);
    for (int i = 0; i < LEVER_WIDTH; i+=300)
    {
        g_middle_background.Render(i, 250, NULL);
    }

}
void PigRespawn()
{
    for (int i = 0; i < LEVER1_TOTAL_PIG; i++)
    {
        Lever1_mPigs[i].Respawn();
    }
}
void EagleRespawn()
{
    for (int i = 0; i < LEVER1_TOTAL_EAGLE; i++)
    {
        Lever1_mEagles[i].Respawn();
    }
    for (int i = 0; i < LEVER2_TOTAL_EAGLE; i++)
    {
        Lever2_mEagles[i].Respawn();
    }
}
void RenderGameStart()
{
    LTexture game_start;
    game_start.LoadImageFromFile("img/Background/Start.png");
    game_start.Render(0, 0, NULL);
}

void RenderGameOver()
{
    LTexture game_over_texture;
    game_over_texture.LoadImageFromFile("img/Background/GameOver.png");
    game_over_texture.Render(0, 0, NULL);
}

void ResetGamePlay()
{
    Highscore = FireballEnergy = NumFireBalls = 0;
    Health = 133;
    current_level = 1;
    PigRespawn();
    EagleRespawn();
}

