#include "LTexture.h"
#include "Constants.h"
#include "Global.h"
using namespace std;
LTexture::LTexture()
{
    // Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    Free();
}

bool LTexture::LoadImageFromFile(string path)
{
    // get rid of preexisting texture
    Free();

    // The final texture
    SDL_Texture* new_texture = NULL;

    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface != NULL)
    {
        // Set color key
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR));

        // create texture from surface
        new_texture = SDL_CreateTextureFromSurface(g_screen, loaded_surface);
        if ( new_texture != NULL)
        {
            // Get image dimensions
            mWidth = loaded_surface->w;
            mHeight = loaded_surface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(loaded_surface);
    }
    mTexture = new_texture;
    return mTexture != NULL;
}
bool LTexture::LoadFromRenderedText(string TextTexture, SDL_Color color)
{
    Free();

    SDL_Surface* TextSurface = TTF_RenderText_Solid(gFont, TextTexture.c_str(), color);
    if (TextSurface != NULL)
    {
        mTexture = SDL_CreateTextureFromSurface(g_screen, TextSurface);
        if (mTexture != NULL)
        {
            mWidth = TextSurface->w;
            mHeight = TextSurface->h;
        }
        SDL_FreeSurface(TextSurface);
    }
    return mTexture != NULL;
}
void LTexture::Free()
{
    // Free texture if it exist
    if ( mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::SetBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::SetAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::Render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    // Set rendering space and render screen
    SDL_Rect renderquad = {x, y, mWidth, mHeight};

    // Set rendering clip dimensions
    if (clip != NULL)
    {
        renderquad.w = clip->w;
        renderquad.h = clip->h;
    }

    // Render texture
    SDL_RenderCopyEx(g_screen, mTexture, clip, &renderquad, angle, center, flip);
}

int LTexture::GetHeight()
{
    return mHeight;
}

int LTexture::GetWidth()
{
    return mWidth;
}
