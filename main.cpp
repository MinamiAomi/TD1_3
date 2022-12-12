#include "Engine.h"
#include "Game.h"
#include <memory>

// Windows�A�v���̃G���g���[�|�C���g(main�֐�)
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