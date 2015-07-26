#include <SDL.h>
#include "game.h"

GameData game; 

int main(int argv, char *args[])
{
	if (game.Setup() < 0)
		return -1;
	game.Run();
	game.Shutdown();
	return 0;
}