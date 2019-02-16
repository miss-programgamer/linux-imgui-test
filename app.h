#ifndef APP_GUARD
#define APP_GUARD

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

// Main application
class App
{
private:
    SDL_Window* window; // Main app window
    SDL_Renderer* renderer; // Main app renderer
    Font* font; // Main app font

    bool running;
    unsigned int start;

    imgui::TextBuffer buffer;

public:
    App();
    ~App();

    // Runs the application, blocks until app is closed
    int Run();
};

#endif