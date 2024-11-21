#include "GameManager/GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	std::unique_ptr<GameManager> gameManager =
		std::make_unique<GameManager>(new DebugScene);
	gameManager->Run();
	return 0;
}
