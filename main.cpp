#include "Engine.h"
#include "Game.h"
#include <memory>

// Windowsアプリのエントリーポイント(main関数)
int MAIN
{
	
	std::unique_ptr<Game> game(new Game);
	bool success = game->Initalize();
	if (success) {
		game->Run();
	}
	game->Finalize();

	return 0;
}