#include "Game.h"
#include "WinApp.h"

// Windowsアプリのエントリーポイント(main関数)
int MAIN
{

	Game* game = new Game;
	bool success = game->Initalize();
	if (success) {
		game->Run();
	}
	game->Finalize();
	delete game;

	return 0;
}