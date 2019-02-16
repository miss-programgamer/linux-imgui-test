#include "main.h"

#define SDL_PRINT_ERROR { const char* err = SDL_GetError(); if (err != nullptr) { printf(err); printf("\n"); } }

using std::printf;
using imgui::context;
using imgui::Window;

App::App() : buffer(32)
{
    // -= Create window and renderer =-
    window = SDL_CreateWindow("My App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

    // -= Configure renderer =-
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // -= Init =-
    font = new Font("resources/fonts/font.bmp", renderer, 12, 16);
    running = true;
    start = SDL_GetTicks();
    context.focus = nullptr;
}

App::~App() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

int App::Run()
{
    // -= Main Loop =-
    while (running)
    {
        // -= Events =-
        if (context.mouseClick) { context.mouseClick = false; }

        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            switch (evt.type) {
            case SDL_KEYDOWN:
                if (SDL_IsTextInputActive()) {
                    switch (evt.key.keysym.sym) {
                    case SDLK_RETURN:
                        SDL_StopTextInput();
                        context.focus = nullptr;
                    break;
                    case SDLK_BACKSPACE:
                        buffer.Back();
                    break;
                    }
                }
            break;
            case SDL_TEXTINPUT:
                if (context.focus != nullptr) {
                    char& in = evt.text.text[0];
                    if (in >= 32 && in < 128) {
                        buffer.Push(in);
                    }
                }
            break;
            case SDL_TEXTEDITING:
                printf("[Text editing event]\n - Cursor: %i\n - Selection: %i\n - Composition: %s\n", evt.edit.start, evt.edit.length, evt.edit.text);
            break;
            case SDL_MOUSEMOTION:
                context.mouseX = evt.motion.x;
                context.mouseY = evt.motion.y;
            break;
            case SDL_MOUSEBUTTONDOWN:
                context.mouseClick = true;
            break;
            case SDL_QUIT:
                running = false;
            break;
            }
        }

        // -= Update =-
        // TODO: Write update code

        // -= Draw =-
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        context.renderer = renderer;
        context.font = font;

        Window window(600, 400);
        window.Text("Some Text");
        window.Text("Some More Text");
        window.Text("Still Text");
        window.Text("This is not a pipe");
        if (window.Button("Print Message")) {
            printf("Hello World!\n");
        }
        if (window.TextField(&buffer)) {
            SDL_StartTextInput();
            context.focus = &buffer;
        }

        SDL_RenderPresent(renderer);
    }

    // -= Return Normally =-
    return 0;
}