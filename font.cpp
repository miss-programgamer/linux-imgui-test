#include "font.h"

Font::Font(const char* filename, SDL_Renderer* renderer, int glyphWidth, int glyphHeight) {
    this->renderer = renderer;
    this->glyphWidth = glyphWidth;
    this->glyphHeight = glyphHeight;

    SDL_Surface* glyphSurface = SDL_LoadBMP(filename);
    SDL_SetColorKey(glyphSurface, true, SDL_MapRGB(glyphSurface->format, 255, 255, 255));
    glyphs = SDL_CreateTextureFromSurface(renderer, glyphSurface);
}

void Font::Draw(const char* text, int x, int y) {
    const int left = x;
    for (int index = 0; text[index] != '\0'; ++index) {
        unsigned char c = text[index];
        if (c == '\n' || c == '\r') {
            x = left;
            y += glyphHeight;
        }
        else if (c >= ' ' && c <= '~') {
            SDL_Rect source { (c % 16) * glyphWidth, (c / 16) * glyphHeight, glyphWidth, glyphHeight };
            SDL_Rect dest { x, y, glyphWidth, glyphHeight };
            SDL_RenderCopy(renderer, glyphs, &source, &dest);
            x += glyphWidth;
        }
    }
}