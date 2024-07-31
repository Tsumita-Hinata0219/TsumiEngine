#include "Project/GameManager/GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	std::unique_ptr<GameManager> gameManager = 
		std::make_unique<GameManager>(new ResultScene);
	gameManager->Run();
	return 0;
}
