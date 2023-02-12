#include "Game.h"
#include "TriangleComponent.h"

int main() {
	Game* game = Game::CreateInstance(L"My Game");
	game->components.push_back(new TriangleComponent());
	std::shared_ptr<Game> gamee;
	game->Run(800, 800);

	delete game;
}
