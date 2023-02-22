#include "PingPongGame.h"

PingPongGame::PingPongGame(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) :
	Game(name, screenWidth, screenHeight, windowed) {
	leftPlayer = std::make_shared<GameObject>();
	rightPlayer = std::make_shared<GameObject>();
	ball = std::make_shared<GameObject>();
}

/*
* Call Game::Update() for base logic
* Handle input player here because of better time control
*/
void PingPongGame::Update() {
	Game::Update();

	// Input of left player
	// Change on internal logic in future
	if (inputDevice->IsKeyDown(Keys::A))
		*leftPlayer->position -= {0.25f * deltaTime, 0.0f, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::D))
		*leftPlayer->position += {0.25f * deltaTime, 0.0f, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::W))
		*leftPlayer->position += {0.0f, 0.5f * deltaTime, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::S))
		*leftPlayer->position -= {0.0f, 0.5f * deltaTime, 0.0f, 0.0f};

	/*std::cout
		<< "Left player position: "
		<< leftPlayer->position->x << " "
		<< leftPlayer->position->y << " "
		<< leftPlayer->position->z <<
		std::endl;*/

	// Input of right player
	// Change on internal logic in future
	if (inputDevice->IsKeyDown(Keys::Left))
		*rightPlayer->position -= {0.25f * deltaTime, 0.0f, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::Right))
		*rightPlayer->position += {0.25f * deltaTime, 0.0f, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::Up))
		*rightPlayer->position += {0.0f, 0.5f * deltaTime, 0.0f, 0.0f};
	if (inputDevice->IsKeyDown(Keys::Down))
		*rightPlayer->position -= {0.0f, 0.5f * deltaTime, 0.0f, 0.0f};

	/*std::cout
		<< "Right player position: "
		<< rightPlayer->position->x << " "
		<< rightPlayer->position->y << " "
		<< rightPlayer->position->z <<
		std::endl;*/
}

/*
* There is no public access to constructor because of "Singleton" pattern
* Need to use this method to create Game::instance (PingPongGame)
*/
void PingPongGame::CreateInstance(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) {
	if (!instance)
		instance = new PingPongGame(name, screenWidth, screenHeight, windowed);
}

/*
* Configure game objects before run
* Call Game::Run() for basic logic
*/
void PingPongGame::Run() {
	ConfigureGameObjects();
	Game::Run();
}

/*
* Configure players game objects
* Configure ball game object
* Configure score game objects
*/
void PingPongGame::ConfigureGameObjects() {
	std::shared_ptr<SquareRenderComponent> leftPlayerRacket = std::make_shared<SquareRenderComponent>(D3D11_FILL_SOLID, leftPlayer->position);
	std::shared_ptr<SquareRenderComponent> rightPlayerRacket = std::make_shared<SquareRenderComponent>(D3D11_FILL_SOLID, rightPlayer->position);
	std::shared_ptr<SquareRenderComponent> ballMesh = std::make_shared<SquareRenderComponent>();
	DirectX::XMFLOAT4 racketColor(0.67f, 0.9f, 0.76f, 1.0f);
	DirectX::XMFLOAT4 ballColor(0.67f, 0.9f, 0.76f, 1.0f);

	leftPlayerRacket->points.insert(leftPlayerRacket->points.end(),
		{
			/* Vertex position						    */ /* Vertex color */
			DirectX::XMFLOAT4( 0.05f,  0.25f, 0.5f, 1.0f), racketColor,
			DirectX::XMFLOAT4(-0.05f, -0.25f, 0.5f, 1.0f), racketColor,
			DirectX::XMFLOAT4( 0.05f, -0.25f, 0.5f, 1.0f), racketColor,
			DirectX::XMFLOAT4(-0.05f,  0.25f, 0.5f, 1.0f), racketColor
		}
	);

	rightPlayerRacket->points.insert(rightPlayerRacket->points.end(),
		{
			/* Vertex position						    */ /* Vertex color */
			DirectX::XMFLOAT4( 0.05f,  0.25f, 0.5f, 1.0f), racketColor,
			DirectX::XMFLOAT4(-0.05f, -0.25f, 0.5f, 1.0f), racketColor,
			DirectX::XMFLOAT4( 0.05f, -0.25f, 0.5f, 1.0f), racketColor,
			DirectX::XMFLOAT4(-0.05f,  0.25f, 0.5f, 1.0f), racketColor
		}
	);

	ballMesh->points.insert(ballMesh->points.end(),
		{
			/* Vertex position						      */  /* Vertex color */
			DirectX::XMFLOAT4( 0.025f,  0.025f, 0.5f, 1.0f),  ballColor,
			DirectX::XMFLOAT4(-0.025f, -0.025f, 0.5f, 1.0f),  ballColor,
			DirectX::XMFLOAT4( 0.025f, -0.025f, 0.5f, 1.0f),  ballColor,
			DirectX::XMFLOAT4(-0.025f,  0.025f, 0.5f, 1.0f),  ballColor
		}
	);

	leftPlayer->AddComponent(leftPlayerRacket);
	rightPlayer->AddComponent(rightPlayerRacket);
	ball->AddComponent(ballMesh);

	// Adding all game objects to Game::gameObjects for their initialization
	PingPongGame::instance->gameObjects.push_back(leftPlayer.get());
	PingPongGame::instance->gameObjects.push_back(rightPlayer.get());
	PingPongGame::instance->gameObjects.push_back(ball.get());
}
