#include "Game.h"
#include "TriangleComponent.h"

int main() {
	Game* game = Game::CreateInstance(L"My Game", 800, 800);
	game->components.push_back(new TriangleComponent());
	game->Run();

	delete game;
}
