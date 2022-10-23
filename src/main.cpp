#include "Game.h"
#include "Miscs/Exception.h"

#include <SDL.h>

int WinMain(int argc, char* argv[])
{
    Game game;

    try
    {
        game.Initialize();
        game.Run();
    }
    catch (Exception& e)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error !", e.ToString().c_str(), game.GetWindow());
    }
    catch (std::exception& e)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error !", e.what(), game.GetWindow());
    }
    catch (...)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unknown error !!!", "Unknown error !!!", game.GetWindow());
    }

    game.Exit();

    return 0;
}