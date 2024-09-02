#include "Project/GameManager/GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	std::unique_ptr<GameManager> gameManager = 
		std::make_unique<GameManager>(new TitleScene);
	gameManager->Run();
	return 0;
}
