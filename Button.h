#ifndef BUTTON_H_
#define BUTTON_H_
#include "LTexture.h"
class Button : public LTexture
{
public:
    enum BUTTON_STATUS
    {
        BUTTON_OUT = 0,
        BUTTON_OVER_MOTION = 1,
        BUTTON_PRESS = 2,
        BUTTON_UP = 3
    };

    Button();

    void SetPosition(int x, int y);

    bool LoadButton(string path, int bWidth, int bHeight);

    void HandleStartButton(SDL_Event* event);

    void HandleExitButton(SDL_Event* event);

    void HandleYesButton(SDL_Event* event);

    void HandleNoButton(SDL_Event* event);

    void ButtonRender();

    bool IsInside(SDL_Event* event, int bWidth, int bHeight);
private:
    SDL_Rect mPosition;
    SDL_Rect Button_clips[4];
    BUTTON_STATUS Current_clip;
};
#endif // BUTTON_H_
