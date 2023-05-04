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
    stringstream Score_string;
    stringstream Tutorial_string;
    stringstream Tutorial_string2;
    stringstream Tutorial_string3;
    stringstream Objective_string;
    stringstream BossDieMessageToPlayer_string;
    stringstream VictoryMessage_string;

    Uint32 Timer;
    const int tick_per_frame = 1000 / 240;

    game_status = 0; // 0: Menu, 1: Tutorial, 2: Play, 3: GameOver, 4: Win.

    // Event handle
    SDL_Event event;

    // The lever camera
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // Set game lever
    current_level = 1;

    // Set full heath
    FoxHealth = 133;

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

    // Lever 2 monster load texture
    for (int i = 0; i < LEVER2_TOTAL_EAGLE; i++)
    {
        Lever2_mEagles[i].LoadMonster();
    }
    for (int i = 0; i < 4; i++)
    {
        Lever2_mDog[i].LoadMonster();
    }

    // Boss load texture
    mBoss.LoadMonster();
    // Set entity position
    fox.SetPosition(0, 1000);

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
    // Lever 2 monster load

    Lever2_mEagles[0].SetPosition(9984, 896);
    Lever2_mEagles[1].SetPosition(10304, 768);
    Lever2_mEagles[2].SetPosition(18240, 704);
    Lever2_mEagles[3].SetPosition(21952, 640);

    Lever2_mDog[0].SetPosition(8320, 960);
    Lever2_mDog[1].SetPosition(15744, 640);
    Lever2_mDog[2].SetPosition(17536, 704);
    Lever2_mDog[3].SetPosition(24128, 1024);
    mBoss.SetPosition(228 * 64, 1088);

    // Game loop
    while (!quit)
    {

        // Game Menu
        if (game_status == 0)
        {
            RenderGameStart();
            Mix_PlayMusic(gSoundTrack, -1);
            gStartButton.LoadButton("img/Button/Button.png", 160, 80);
            gStartButton.SetPosition((SCREEN_WIDTH - 160) / 2, 300);

            gExitButton.LoadButton("img/Button/ExitButton.png", 160, 80);
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
            FoxCurrentHeart = 3 - fox.GetDeathCount();
            Timer = SDL_GetTicks();
            // The HealthBar
            SDL_Rect HealthBar = {46, 22, FoxHealth, 14};
            SDL_Rect BossHealthBar = {(SCREEN_WIDTH - gBossHealthBar.GetWidth()) / 2 + 8, 58, BossHealth, 16};
            // HighScore
            Score_string.str("");
            Score_string << "Score:" << Score;
            gScoreText.LoadFromRenderedText(Score_string.str().c_str(), TextColor);

            gResumeButton.LoadButton("img/Button/ResumeButton.png", 96, 96);
            gResumeButton.SetPosition((SCREEN_WIDTH - 96) / 2, 190);

            gPauseButton.LoadButton("img/Button/PauseButton.png", 64, 64);
            gPauseButton.SetPosition((SCREEN_WIDTH - 64) - 20, 20);

            gHomeButton.LoadButton("img/Button/HomeButton.png", 96, 96);
            gHomeButton.SetPosition((SCREEN_WIDTH - 96) /2, 430);

            gRestartButton.LoadButton("img/Button/RestartButton.png", 96, 96);
            gRestartButton.SetPosition((SCREEN_WIDTH - 96) / 2, 310);

            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                gPauseButton.HandlePauseButton(&event);
                gResumeButton.HandleResumeButton(&event);
                gHomeButton.HandleHomeButton(&event);
                gRestartButton.HandleRestartButton(&event);
                // Handle Event
                fox.HandleEvent(event);
            }
            if (!GamePause)
            {
                // Fox and enemy move
                fox.Move(tileSet);
                // Lever 1 monster move
                if (current_level == 1)
                {
                    for (int i = 0; i < LEVER1_TOTAL_PIG; i++)
                    {
                        Lever1_mPigs[i].MonsterMove(tileSet);
                    }
                    for (int i = 0; i < LEVER1_TOTAL_EAGLE; i++)
                    {
                        Lever1_mEagles[i].MonsterMove(tileSet);
                    }
                }

                // Lever 2 monster move
                if (current_level == 2)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        Lever2_mEagles[i].MonsterMove(tileSet);
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        Lever2_mDog[i].MonsterMove(tileSet);
                    }
                }

                // Lever 3 monster move
                if (current_level == 3)
                {
                    mBoss.MonsterMove(tileSet, camera);
                }
                // Get fox current position
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
                    if (current_level >= 4)
                    {
                        current_level = 3;
                    }
                    LoadMap(tileSet, current_level);
                }
                if (!GamePause)
                {
                    // Render Background
                    RenderBackGround();
                }

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
                gScoreText.Render(SCREEN_WIDTH - 290, 40, NULL);

                // Render heart count in state bar
                for (int i = 1; i <= FoxCurrentHeart; i++)
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
                // Lever 1 monster render
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
                // Lever 2 monster render
                if (current_level == 2)
                {
                    for (int i = 0; i < LEVER2_TOTAL_EAGLE; i++)
                    {
                        Lever2_mEagles[i].RenderMonster(camera);
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        Lever2_mDog[i].RenderMonster(camera);
                    }

                }
                // Lever 3 monster render
                if (current_level == 3)
                {
                    mBoss.RenderMonster(camera);
                    if (!mBoss.IsDie())
                    {
                        gBossHealthBar.Render((SCREEN_WIDTH - gBossHealthBar.GetWidth()) / 2, 50, NULL);
                    }
                    else if (mBoss.IsDie())
                    {
                        SDL_Color BossDieMessageTextColor = {255, 255, 255, 255};
                        BossDieMessageToPlayer_string.str("");
                        BossDieMessageToPlayer_string << "Boss has been defeated, enter the door to win the game";
                        BossDieMessageToPlayer_Text.LoadFromRenderedText(BossDieMessageToPlayer_string.str().c_str(), BossDieMessageTextColor);
                        BossDieMessageToPlayer_Text.Render((SCREEN_WIDTH - BossDieMessageToPlayer_Text.GetWidth()) / 2, 110, NULL);
                        if (fox.GetBox().x > SCREEN_WIDTH - Fox::FOX_WIDTH - 20)
                        {
                            // Set win
                            game_status = 4;
                        }
                    }
                    SDL_SetRenderDrawColor(g_screen, 255, 0, 0, 255);
                    SDL_RenderFillRect(g_screen, &BossHealthBar);
                }
                // RenderEnemy(camera);
                gPauseButton.ButtonRender();
                // Fox death handle
                if (fox.GetDeathCount() > 2)
                {
                    Score = 0;
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
            else if (GamePause)
            {
                PauseBar.Render((SCREEN_WIDTH - PauseBar.GetWidth()) / 2, (SCREEN_HEIGHT - PauseBar.GetHeight()) / 2, NULL);
                gHomeButton.ButtonRender();
                gResumeButton.ButtonRender();
                gRestartButton.ButtonRender();
                SDL_RenderPresent(g_screen);
            }

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

            gYesButton.LoadButton("img/Button/YesButton.png", 96, 96);
            gYesButton.SetPosition(536, 520);

            gNoButton.LoadButton("img/Button/NoButton.png", 96, 96);
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
        // Win
        if (game_status == 4)
        {
            RenderGameWin();
            SDL_Color PlayAgainColor = {255, 255, 255, 255};
            SDL_Color WinColor = {0, 0, 0, 255};

            VictoryMessage_string.str("");
            VictoryMessage_string << "YOU HAVE WON THIS GAME!!!! :vvv";
            PlayAgain_string.str("");
            PlayAgain_string << "PLAY AGAIN?";

            VictoryMessage_Text.LoadFromRenderedText(VictoryMessage_string.str().c_str(), WinColor);
            VictoryMessage_Text.Render((SCREEN_WIDTH - VictoryMessage_Text.GetWidth()) / 2, 100, NULL);

            PlayAgain.LoadFromRenderedText(PlayAgain_string.str().c_str(), PlayAgainColor);
            PlayAgain.Render((SCREEN_WIDTH - PlayAgain.GetWidth()) / 2, 480, NULL);

            gYesButton.LoadButton("img/Button/YesButton.png", 96, 96);
            gYesButton.SetPosition(536, 520);

            gNoButton.LoadButton("img/Button/NoButton.png", 96, 96);
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
