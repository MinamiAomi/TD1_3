#include "Game.h"
#include "WinApp.h"

// Windows�A�v���̃G���g���[�|�C���g(main�֐�)
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