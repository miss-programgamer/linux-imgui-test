#ifndef IMGUI_GUARD
#define IMGUI_GUARD

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "font.h"

namespace imgui {
    using Rect = SDL_Rect;

    class TextBuffer {
    public:
        char* buffer;
        int size;
        int cursor;

        TextBuffer(int size);
        ~TextBuffer();

        void Push(char c);
        void Back();
    };

    class Context {
    public:
        SDL_Renderer* renderer;
        Font* font;

        TextBuffer* focus;
        int mouseX, mouseY;
        bool mouseClick;
    };

    class Container {
    protected:
        Rect size;
        int nextX;
        int nextY;

        Container() {}

    public:
        void Text(const char* text);
        bool Button(const char* text);
        bool TextField(TextBuffer* textBuffer);
    };

    class Window : public Container {
    public:
        Window(int width, int height);
    };

    extern Context context;
}

#endif