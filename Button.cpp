#include "Global.h"
#include "UTIL.h"
#include "Button.h"
#include "LTexture.h"
#include "Constants.h"
Button::Button()
{
    mPosition.x = mPosition.y = 0;
    Current_clip = BUTTON_OUT;
}
void Button::SetPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}
bool Button::LoadButton(string path, int bWidth, int bHeight)
{
    // Start button
    if (!LTexture::LoadImageFromFile(path.c_str()))
    {
        return false;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            Button_clips[i] = {i * bWidth, 0, bWidth, bHeight};
        }
    }
    return true;
}
void Button::HandleStartButton(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEMOTION)
    {
        bool inside = true;
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < (SCREEN_WIDTH - 160) / 2 || x > (SCREEN_WIDTH - 160) / 2 + 160 || y < 300 || y > 300 + 80)
        {
            inside = false;
        }
        if (inside)
        {
            switch (event->type)
            {
            case SDL_MOUSEMOTION:
                Current_clip = BUTTON_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                Current_clip = BUTTON_PRESS;
                game_status = 1;
                ResetGamePlay();
                Mix_PlayChannel(-1, gButtonClick, 0);
                break;
            case SDL_MOUSEBUTTONUP:
                Current_clip = BUTTON_UP;
                break;
            }
        }
        else
        {
            Current_clip = BUTTON_OUT;
        }
    }
}
void Button::HandleExitButton(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEMOTION)
    {
        if (gExitButton.IsInside(event, 160, 80))
        {
            switch (event->type)
            {
            case SDL_MOUSEMOTION:
                Current_clip = BUTTON_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                Current_clip = BUTTON_PRESS;
                quit = true;
                Mix_PlayChannel(-1, gButtonClick, 0);
                break;
            case SDL_MOUSEBUTTONUP:
                Current_clip = BUTTON_UP;
                break;
            }
        }
        else
        {
            Current_clip = BUTTON_OUT;
        }
    }
}

void Button::HandleYesButton(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEMOTION)
    {
        bool inside = true;
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < 536 || x > 536 + 96 || y < 520 || y > 520 + 96)
        {
            inside = false;
        }
        if (inside)
        {
            switch (event->type)
            {
            case SDL_MOUSEMOTION:
                Current_clip = BUTTON_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                Current_clip = BUTTON_PRESS;
                game_status = 2;
                ResetGamePlay();
                fox.SetPosition(0, 1000);
                current_level = 1;
                playagain = true;
                Mix_PlayChannel(-1, gButtonClick, 0);
                break;
            case SDL_MOUSEBUTTONUP:
                Current_clip = BUTTON_UP;
                break;
            }
        }
        else
        {
            Current_clip = BUTTON_OUT;
        }
    }
}

void Button::HandleNoButton(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEMOTION)
    {
        bool inside = true;
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < 728 || x > 728 + 96 || y < 520 || y > 520 + 96)
        {
            inside = false;
        }
        if (inside)
        {
            switch (event->type)
            {
            case SDL_MOUSEMOTION:
                Current_clip = BUTTON_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                Current_clip = BUTTON_PRESS;
                Mix_PlayChannel(-1, gButtonClick, 0);
                quit = true;
                break;
            case SDL_MOUSEBUTTONUP:
                Current_clip = BUTTON_UP;
                break;
            }
        }
        else
        {
            Current_clip = BUTTON_OUT;
        }
    }
}
void Button::HandleResumeButton(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEMOTION)
    {
        bool inside = true;
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < (SCREEN_WIDTH - 96) / 2 || x > (SCREEN_WIDTH - 96) / 2 + 96 || y < 190 || y > 286)
        {
            inside = false;
        }
        if (inside)
        {
            switch(event->type)
            {
            case SDL_MOUSEMOTION:
                Current_clip = BUTTON_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                Mix_PlayChannel(-1, gButtonClick, 0);
                GamePause = false;
                Current_clip = BUTTON_PRESS;
                break;
            case SDL_MOUSEBUTTONUP:
                Current_clip = BUTTON_UP;
                break;
            }
        }
        else
        {
            Current_clip = BUTTON_OUT;
        }
    }
}
void Button::HandlePauseButton(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEMOTION)
    {
        bool inside = true;
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < (SCREEN_WIDTH - 64) - 20 || x > SCREEN_WIDTH - 20 || y < 20 || y > 84)
        {
            inside = false;
        }
        if (inside)
        {
            switch (event->type)
            {
            case SDL_MOUSEMOTION:
                Current_clip = BUTTON_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                Mix_PlayChannel(-1, gButtonClick, 0);
                GamePause = true;
                Current_clip = BUTTON_PRESS;
                break;
            case SDL_MOUSEBUTTONUP:
                Current_clip = BUTTON_UP;
                break;
            }
        }
        else
        {
            Current_clip = BUTTON_OUT;
        }
    }
}
void Button::HandleHomeButton(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEMOTION)
    {
        bool inside = true;
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < (SCREEN_WIDTH - 96) / 2 || x > (SCREEN_WIDTH - 96) / 2 + 96 || y < 430 || y > 526)
        {
            inside = false;
        }
        if (inside)
        {
            switch (event->type)
            {
            case SDL_MOUSEMOTION:
                Current_clip = BUTTON_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                Mix_PlayChannel(-1, gButtonClick, 0);
                game_status = 0;
                GamePause = false;
                Current_clip = BUTTON_PRESS;
                break;
            case SDL_MOUSEBUTTONUP:
                Current_clip = BUTTON_UP;
                break;
            }
        }
        else
        {
            Current_clip = BUTTON_OUT;
        }
    }
}
void Button::HandleRestartButton(SDL_Event* event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEMOTION)
    {
        bool inside = true;
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < (SCREEN_WIDTH - 96) / 2 || x > (SCREEN_WIDTH - 96) / 2 + 96 || y < 310 || y > 406)
        {
            inside = false;
        }
        if (inside)
        {
            switch (event->type)
            {
            case SDL_MOUSEMOTION:
                Current_clip = BUTTON_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                Mix_PlayChannel(-1, gButtonClick, 0);
                game_status = 2;
                GamePause = false;
                playagain = true;
                Score = FireballEnergy = NumFireBalls = 0;
                fox.ResetDeathCount();
                FoxHealth = 133;
                if (current_level == 1)
                {
                    for (int i = 0; i < LEVER1_TOTAL_PIG; i++)
                    {
                        Lever1_mPigs[i].Respawn();
                    }
                    for (int i = 0; i < LEVER1_TOTAL_EAGLE; i++)
                    {
                        Lever1_mEagles[i].Respawn();
                    }
                }
                else if (current_level == 2)
                {
                    for (int i = 0; i < LEVER2_TOTAL_EAGLE; i++)
                    {
                        Lever2_mEagles[i].Respawn();
                    }
                }
                else if (current_level == 3)
                {
                    mBoss.Respawn();
                }
                fox.SetPosition(0, 1000);
                Current_clip = BUTTON_PRESS;
                break;
            case SDL_MOUSEBUTTONUP:
                Current_clip = BUTTON_UP;
                break;
            }
        }
        else
        {
            Current_clip = BUTTON_OUT;
        }
    }
}
void Button::ButtonRender()
{
    Render(mPosition.x, mPosition.y, &Button_clips[Current_clip]);
}

bool Button::IsInside(SDL_Event* event, int bWidth, int bHeight)
{
    bool check = true;
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEMOTION)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x < mPosition.x)
        {
            check = false;
        }
        if (x > mPosition.x + bWidth)
        {
            check = false;
        }
        if (y < mPosition.y)
        {
            check = false;
        }
        if (y > mPosition.y + bHeight)
        {
            check = false;
        }
    }
    return check;
}
