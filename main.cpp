#include "Project/GameManager/GameManager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	GameManager* gameManager = new GameManager(new GameScene);
	gameManager->Run();
	delete gameManager;
	return 0;
}
