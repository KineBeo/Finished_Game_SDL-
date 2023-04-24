#ifndef FIRE_BALL_H
#define FIRE_BALL_H
#include "LTexture.h"
#include "Constants.h"
#include "Tile.h"
#include "Global.h"
class FireBall : public LTexture
{
public:
    // Fireball size and speed
    static const int FIRE_WIDTH = 64;
    static const int FIRE_HEIGHT = 64;
    static const int FIRE_SPEED = 20;

    // Initialize
    FireBall();
    // Load fireball texture
    bool LoadFireBall();

    // Set position for fireball
    void SetPosition(int x, int y);

    // Set speed
    void SetVelocity(int velX, int velY);

    // Set active status
    void SetActive(bool active);

    // Get status of fireballs
    bool IsActive();

    void Disable();

    // Move fireball
    void Move(Tile* tiles[]);

    // Get collision box
    SDL_Rect GetBoxFireball();

    // Render fireball
    void RenderFireball(SDL_Rect& camera, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    // Fireball collision box
    SDL_Rect mBox;

    // Fireball velocity
    int mVelX, mVelY;

    // Start position of each fireball
    int mStartX, mStartY;

    // fireball flag
    bool mActive;

    // Fireball clip
    SDL_Rect Fireball_clip[3];

    // Fireball frame
    int Fireball_frame;
};
#endif // FIRE_BALL_H
