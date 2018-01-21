#include "fssimplewindow.h"
#include "Game.h"
#include <stdlib.h>
#include <time.h>

int main(void)
{
	srand((unsigned int)time(NULL));

	FsOpenWindow(16, 16, 500, 700, 1);

	Game game;
	game.Run();
	
	return 0;
}