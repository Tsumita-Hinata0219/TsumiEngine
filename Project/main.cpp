#include "GameManager/GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	std::unique_ptr<GameManager> gameManager =
		std::make_unique<GameManager>(std::make_unique<SelectScene>());
	gameManager->Run();
	return 0;
}
