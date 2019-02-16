#ifndef FONT_GUARD
#define FONT_GUARD

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

class Font {
public:
    SDL_Renderer* renderer;
    SDL_Texture* glyphs;
    int glyphWidth, glyphHeight;

    Font(const char* filename, SDL_Renderer* renderer, int glyphWidth, int glyphHeight);

    void Draw(const char* text, int x, int y);
};

#endif