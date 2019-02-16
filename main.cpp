#include "main.h"

int main(int argCount, char* argList[])
{
    // -= Init SDL =-
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_EVERYTHING);

    // -= Run the application =-
    App app;
    int result = app.Run();

    // -= Quit SDL =-
    SDL_Quit();

    // -= Return =-
    return result;
}