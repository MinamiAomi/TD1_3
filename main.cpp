#include "Game.h"

// Windows�A�v���̃G���g���[�|�C���g(main�֐�)
int MAIN
{

	Game* game = new Game;

	game.get()->Initalize();
	game.get()->Run();
	game.get()->Finalize();

	delete game;

	return 0;
}