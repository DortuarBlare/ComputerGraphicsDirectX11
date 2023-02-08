#include "Game.h"

int main() {
	Game::GetInstance()->Initialize();
	Game::GetInstance()->Run();
}
