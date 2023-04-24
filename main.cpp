#include <bits/stdc++.h>
#include "LTexture.h"
#include "UTIL.h"
#include "Global.h"
#include "Tile.h"
#include "Fox.h"
#include "Button.h"
using namespace std;
int main(int argc, char* argv[])
{

    SDL_Color TextColor = {252, 104, 6, 255};
    stringstream DeathCount_string;
    stringstream PlayAgain_string;
    stringstream HighScore_string;
    stringstream Tutorial_string;
    stringstream Tutorial_string2;
    stringstream Tutorial_string3;
    stringstream Objective_string;

    Uint32 Timer;
    const int tick_per_frame = 1000 / 240;

    game_status = 0; // 0: Start, 1: Play, 2: GameOver

    // Event handle
    SDL_Event event;

    // The lever camera
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // Set game lever
    current_level = 1;

    // Set full heath
    Health = 133;

    // Initialize SDL
    Init();

    // Load background
    LoadBackGround();

    Tile* tileSet[TOTAL_TILES];

    // Load map
    LoadMap(tileSet, current_level);

    // Load font
    LoadFont();

    // Load sound
    LoadMusic();

    // Load fox and enemy texture
    // LoadAllCharacter();
    fox.LoadCharacter();

    // Lever 1 monster load texture
    for (int i = 0; i < LEVER1_TOTAL_PIG ; i++)
    {
        Lever1_mPigs[i].LoadMonster();
    }
    for (int i = 0; i < LEVER1_TOTAL_EAGLE; i++)
    {
        Lever1_mEagles[i].LoadMonster();
    }
    for (int i = 0; i < LEVER2_TOTAL_EAGLE; i++)
    {
        Lever2_mEagles[i].LoadMonster();
    }

    // Set entity position
    fox.SetPosition(0, 1050);

    // Lever 1 monster set position
    Lever1_mPigs[0].SetPosition(768, 1280);
    Lever1_mPigs[1].SetPosition(5824, 1088);
    Lever1_mPigs[2].SetPosition(8064, 832);
    Lever1_mPigs[3].SetPosition(12736, 1088);
    Lever1_mPigs[4].SetPosition(15744, 256);
    Lever1_mPigs[5].SetPosition(17920, 896);
    Lever1_mEagles[0].SetPosition(14016, 576);
    Lever1_mEagles[1].SetPosition(3904, 1408);
    Lever1_mEagles[2].SetPosition(3648, 1280);
    Lever1_mEagles[3].SetPosition(8000, 832);
    Lever1_mEagles[4].SetPosition(12976, 256);
    Lever1_mEagles[5].SetPosition(18368, 832);
    SetEnemyPosition();
    // Lever 2 monster load

    Lever2_mEagles[0].SetPosition(9984, 896);
    Lever2_mEagles[1].SetPosition(10304, 768);
    Lever2_mEagles[2].SetPosition(18240, 704);
    Lever2_mEagles[3].SetPosition(21952, 640);


    // Game loop
    while (!quit)
    {

        // Game Menu
        if (game_status == 0)
        {
            RenderGameStart();
            Mix_PlayMusic(gSoundTrack, -1);
            gStartButton.LoadButton("img/Button.png", 160, 80);
            gStartButton.SetPosition((SCREEN_WIDTH - 160) / 2, 300);

            gExitButton.LoadButton("img/ExitButton.png", 160, 80);
            gExitButton.SetPosition((SCREEN_WIDTH - 160) / 2, 400);


            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                gStartButton.HandleStartButton(&event);
                gExitButton.HandleExitButton(&event);
            }
            gStartButton.ButtonRender();
            gExitButton.ButtonRender();
            SDL_RenderPresent(g_screen);
        }
        if (game_status == 1)
        {
            SDL_Color Tutorial_color = {230, 216, 13, 255};
            Tutorial_string.str("");
            Tutorial_string << "Move with A,D key";
            gTutorialText.LoadFromRenderedText(Tutorial_string.str().c_str(), Tutorial_color);

            Tutorial_string2.str("");
            Tutorial_string2 << "Jump with Spacebar";
            gTutorialText2.LoadFromRenderedText(Tutorial_string2.str().c_str(), Tutorial_color);

            Tutorial_string3.str("");
            Tutorial_string3 << "Shoot fireball with J key";
            gTutorialText3.LoadFromRenderedText(Tutorial_string3.str().c_str(), Tutorial_color);

            Objective_string.str("");
            Objective_string << "Kill mob, eat cherry and win^^";
            gObjectiveText.LoadFromRenderedText(Objective_string.str().c_str(), Tutorial_color);

            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_RETURN:
                        game_status = 2;
                        break;
                    }
                }
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
            g_background.Render(0, 0, NULL);
            g_tutorial.Render((SCREEN_WIDTH - g_tutorial.GetWidth()) / 2, (SCREEN_HEIGHT - g_tutorial.GetHeight()) / 2, NULL);
            gTutorialText.Render((SCREEN_WIDTH - gTutorialText.GetWidth()) / 2 + 5, 260, NULL);
            gTutorialText2.Render((SCREEN_WIDTH - gTutorialText2.GetWidth()) / 2 + 5, 300, NULL);
            gTutorialText3.Render((SCREEN_WIDTH - gTutorialText3.GetWidth()) / 2 + 5, 340, NULL);
            gObjectiveText.Render((SCREEN_WIDTH - gObjectiveText.GetWidth()) / 2 + 30, 450, NULL);
            PressEnter.Render((SCREEN_WIDTH - PressEnter.GetWidth()) / 2 + 5, 590, NULL);
            SDL_RenderPresent(g_screen);
        }
        // GamePlay
        if (game_status == 2)
        {
            Timer = SDL_GetTicks();
            // The HealthBar
            SDL_Rect HealthBar = {46, 22, Health, 14};

            // HighScore
            HighScore_string.str("");
            HighScore_string << "HIGHSCORE: " << Highscore;
            gHighScoreText.LoadFromRenderedText(HighScore_string.str().c_str(), TextColor);

            // Heart of fox
            int current_heart = 3 - fox.GetDeathCount();

            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                // Handle Event
                fox.HandleEvent(event);
            }
            // Fox and enemy move

            // CharacterMove(tileSet);
            fox.Move(tileSet);
            for (int i = 0; i < LEVER1_TOTAL_PIG; i++)
            {
                Lever1_mPigs[i].MonsterMove(tileSet);
            }
            for (int i = 0; i < LEVER1_TOTAL_EAGLE; i++)
            {
                Lever1_mEagles[i].MonsterMove(tileSet);
            }
            for (int i = 0; i < LEVER2_TOTAL_EAGLE; i++)
            {
                Lever2_mEagles[i].MonsterMove(tileSet);
            }

            FoxPosX = fox.GetBox().x;
            FoxPosY = fox.GetBox().y;

            // Camera
            fox.SetCamera(camera);

            // Switch lever
            if (fox.GetBox().x > LEVER_WIDTH - Fox::FOX_WIDTH)
            {
                fox.ResetDeathCount();
                fox.NewLeverSpawn();
                current_level++;
                if (current_level >= 3)
                {
                    current_level = 2;
                }
                LoadMap(tileSet, current_level);
            }

            // Render Background
            RenderBackGround();

            // Render lever ( Map )
            for (int i = 0 ; i < TOTAL_TILES; i++)
            {
                tileSet[i]->Tile_Render(camera);
            }

            // State Bar
            StateBar.Render(0, 0, NULL);
            // Render HealthBar
            SDL_SetRenderDrawColor(g_screen, 255, 0, 0, 255);
            SDL_RenderFillRect(g_screen, &HealthBar);

            // Render Highscore
            gHighScoreText.Render(SCREEN_WIDTH - 290, 0, NULL);

            // Render heart count in state bar
            for (int i = 1; i <= current_heart; i++)
            {
                Heart.Render(46 * i, 46, NULL);
            }

            // Render fireball set in state bar
            for (int i = 1; i <= MAXIMUM_NUMBER_OF_FIREBALL - NumFireBalls; i++)
            {
                NumFireballInStateBar.Render(30 * i, 75, NULL);
            }

            // Render entity of game
            fox.FoxRender(camera);
            if (current_level == 1)
            {
                for (int i = 0; i < LEVER1_TOTAL_PIG; i++)
                {
                    Lever1_mPigs[i].RenderMonster(camera);
                }
                for (int i = 0; i < LEVER1_TOTAL_EAGLE; i++)
                {
                    Lever1_mEagles[i].RenderMonster(camera);
                }
            }
            if (current_level == 2)
            {
                for (int i = 0; i < LEVER2_TOTAL_EAGLE; i++)
                {
                    Lever2_mEagles[i].RenderMonster(camera);
                }
            }
            // RenderEnemy(camera);

            // Fox death handle
            if (fox.GetDeathCount() > 2)
            {
                Highscore = 0;
                game_status = 3;
                fox.ResetSpeed();
                fox.ResetDeathCount();
            }

            // Fps handle
            int tick = SDL_GetTicks() - Timer;
            if (tick < tick_per_frame)
            {
                SDL_Delay(tick_per_frame - tick);
            }

            // Update screen
            SDL_RenderPresent(g_screen);
        }
        // GameOver
        if (game_status == 3)
        {
            RenderGameOver();
            PlayAgain_string.str("");
            PlayAgain_string << "PLAY AGAIN?";
            SDL_Color PlayAgainColor = {0, 0, 0, 255};
            PlayAgain.LoadFromRenderedText(PlayAgain_string.str().c_str(), PlayAgainColor);
            PlayAgain.Render((SCREEN_WIDTH - PlayAgain.GetWidth()) / 2, 480, NULL);

            gYesButton.LoadButton("img/YesButton.png", 96, 96);
            gYesButton.SetPosition(536, 520);

            gNoButton.LoadButton("img/NoButton.png", 96, 96);
            gNoButton.SetPosition(728, 520);
            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                gYesButton.HandleYesButton(&event);
                gNoButton.HandleNoButton(&event);
            }
            if (playagain)
            {
                LoadMap(tileSet, current_level);
            }
            gYesButton.ButtonRender();
            gNoButton.ButtonRender();
            SDL_RenderPresent(g_screen);
        }
    }
    Close(tileSet);
    return 0;
}
