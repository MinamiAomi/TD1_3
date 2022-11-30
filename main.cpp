#include "Game.h"

// Windowsアプリのエントリーポイント(main関数)
int MAIN
{

	Game* game = new Game;

	game.get()->Initalize();
	game.get()->Run();
	game.get()->Finalize();

	delete game;

	return 0;
}