#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <fstream>
#include <string>
using namespace std;
class LTexture
{
public:
    // Initialize
    LTexture();

    // Deallocates memory
    ~LTexture();

    // Load image from specified path
    bool LoadImageFromFile(string path);

    bool LoadFromRenderedText(string TextTexture, SDL_Color color);

    // Deallocates texture
    void Free();

    // color modulate
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);

    // Set blending function
    void SetBlendMode(SDL_BlendMode blending);

    // alpha modulate
    void SetAlpha(Uint8 alpha);

    // Render texture at given point
    void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Get image dimensions
    int GetWidth();
    int GetHeight();

protected:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;

};
#endif // LTEXTURE_H
