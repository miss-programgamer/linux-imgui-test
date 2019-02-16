#include "imgui.h"

namespace imgui {
    TextBuffer::TextBuffer(int size) {
        this->size = size;
        buffer = new char[size + 1];
        cursor = 0;

        buffer[0] = '\0';
        buffer[size] = '\0';
    }

    TextBuffer::~TextBuffer() {
        delete[] buffer;
    }

    void TextBuffer::Push(char c) {
        for (int index = 0; index < size; ++index) {
            if (buffer[index] == '\0') {
                ++cursor;
                buffer[index] = c;
                buffer[index + 1] = '\0';
                break;
            }
        }
    }

    void TextBuffer::Back() {
        if (buffer[0] == '\0') { return; }

        for (int index = 1; index <= size; ++index) {
            if (buffer[index] == '\0') {
                --cursor;
                buffer[index - 1] = '\0';
                break;
            }
        }
    }

    void Container::Text(const char* text) {
        // -= Determine size =-
        int len = strlen(text);
        Rect bg { nextX, nextY, len * context.font->glyphWidth + 4, context.font->glyphHeight + 4 };

        // -= Draw =-
        SDL_SetRenderDrawColor(context.renderer, 127, 127, 255, 255);
        SDL_RenderFillRect(context.renderer, &bg);
        context.font->Draw(text, nextX + 2, nextY + 2);

        // -= Advance =-
        nextY += context.font->glyphHeight + 6;
    }

    bool Container::Button(const char* text) {
        // -= Determine size and state =-
        int len = strlen(text);
        Rect bg { nextX, nextY, len * context.font->glyphWidth + 4, context.font->glyphHeight + 4 };
        bool hover = (context.mouseX >= bg.x) && (context.mouseX <= bg.x + bg.w) && (context.mouseY >= bg.y) && (context.mouseY <= bg.y + bg.h);

        // -= Draw =-
        if (hover) {
            if (context.mouseClick) {
                SDL_SetRenderDrawColor(context.renderer, 63, 63, 127, 255);
            }
            else {
                SDL_SetRenderDrawColor(context.renderer, 255, 255, 255, 255);
            }
        }
        else {
            SDL_SetRenderDrawColor(context.renderer, 127, 127, 255, 255);
        }
        SDL_RenderFillRect(context.renderer, &bg);
        context.font->Draw(text, nextX + 2, nextY + 2);

        // -= Advance =-
        nextY += context.font->glyphHeight + 6;

        // -= Return state =-
        return hover && context.mouseClick;
    }

    bool Container::TextField(TextBuffer* buffer) {
        // -= Determine size and state =-
        Rect bg { nextX, nextY, buffer->size * context.font->glyphWidth + 4, context.font->glyphHeight + 4 };
        bool hover = (context.mouseX >= bg.x) && (context.mouseX <= bg.x + bg.w) && (context.mouseY >= bg.y) && (context.mouseY <= bg.y + bg.h);

        // -= Draw =-
        SDL_SetRenderDrawColor(context.renderer, 127, 127, 255, 255);
        SDL_RenderFillRect(context.renderer, &bg);
        context.font->Draw(buffer->buffer, nextX + 2, nextY + 2);
        if (context.focus != nullptr) {
            context.font->Draw("_", nextX + 2 + buffer->cursor * context.font->glyphWidth, nextY + 2);
        }

        // -= Advance =-
        nextY += context.font->glyphHeight + 6;

        // -= Return state =-
        return hover && context.mouseClick;
    }

    Window::Window(int width, int height) {
        size = { 0, 0, width, height };
        nextX = 0;
        nextY = 0;
    }

    Context context;
}