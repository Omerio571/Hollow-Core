#include "Game.hpp"
#include "Config.hpp"

int main()
{
    Game game{};

    if (!game.Initialize())
    {
        TraceLog(LOG_ERROR, "%s could not initialize!", Config::gameName);
        return 1;
    }

    game.Run();
    game.ShutDown();

    return 0;
}
