#include "PingPongGame.h"

PingPongGame::PingPongGame(LPCWSTR name, int screenWidth, int screenHeight, bool windowed) :
	Game(name, screenWidth, screenHeight, windowed) {
	leftPlayer = std::make_shared<GameObject>();
	rightPlayer = std::make_shared<GameObject>();
	ball = std::make_shared<GameObject>();
	centralInvisibleWall = std::make_shared<GameObject>();
	upInvisibleWall = std::make_shared<GameObject>();
	downInvisibleWall = std::make_shared<GameObject>();
	leftInvisibleWall = std::make_shared<GameObject>();
	rightInvisibleWall = std::make_shared<GameObject>();
}

void PingPongGame::Initialize() {
	Game::Initialize();

	*leftPlayer->position -= {0.5f, 0.0f, 0.0f, 0.0f};
	*rightPlayer->position += {0.5f, 0.0f, 0.0f, 0.0f};
	leftPlayer->getComponent<BoxColliderComponent>().value().GetCenter().x -= 0.5f;
	rightPlayer->getComponent<BoxColliderComponent>().value().GetCenter().x += 0.5f;

	*upInvisibleWall->position += {0.0f, 1.0f, 0.0f, 0.0f};
	upInvisibleWall->getComponent<BoxColliderComponent>().value().GetCenter().y += 1.0f;

	*downInvisibleWall->position -= {0.0f, 1.0f, 0.0f, 0.0f};
	downInvisibleWall->getComponent<BoxColliderComponent>().value().GetCenter().y -= 1.0f;

	*leftInvisibleWall->position -= {1.0f, 0.0f, 0.0f, 0.0f};
	leftInvisibleWall->getComponent<BoxColliderComponent>().value().GetCenter().x -= 1.0f;

	*rightInvisibleWall->position += {1.0f, 0.0f, 0.0f, 0.0f};
	rightInvisibleWall->getComponent<BoxColliderComponent>().value().GetCenter().x += 1.0f;
}

/*
* Call Game::Update() for base logic
* Handle input player here because of better time control
*/
void PingPongGame::Update() {
	Game::Update();

	// Left player handle input
	if (inputDevice->IsKeyDown(Keys::A))
		leftPlayer->wantsToMoveLeft = true;
	else 
		leftPlayer->wantsToMoveLeft = false;

	if (inputDevice->IsKeyDown(Keys::D))
		leftPlayer->wantsToMoveRight = true;
	else
		leftPlayer->wantsToMoveRight = false;

	if (inputDevice->IsKeyDown(Keys::W))
		leftPlayer->wantsToMoveUp = true;
	else
		leftPlayer->wantsToMoveUp = false;

	if (inputDevice->IsKeyDown(Keys::S))
		leftPlayer->wantsToMoveDown = true;
	else
		leftPlayer->wantsToMoveDown = false;


	// Right player handle input
	if (inputDevice->IsKeyDown(Keys::Left))
		rightPlayer->wantsToMoveLeft = true;
	else
		rightPlayer->wantsToMoveLeft = false;

	if (inputDevice->IsKeyDown(Keys::Right))
		rightPlayer->wantsToMoveRight = true;
	else
		rightPlayer->wantsToMoveRight = false;

	if (inputDevice->IsKeyDown(Keys::Up))
		rightPlayer->wantsToMoveUp = true;
	else
		rightPlayer->wantsToMoveUp = false;

	if (inputDevice->IsKeyDown(Keys::Down))
		rightPlayer->wantsToMoveDown = true;
	else
		rightPlayer->wantsToMoveDown = false;
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
* Before PingPongGame::Initialize()
*/
void PingPongGame::ConfigureGameObjects() {
	DirectX::XMFLOAT4 racketColor(0.67f, 0.9f, 0.76f, 1.0f);
	DirectX::XMFLOAT4 ballColor(0.67f, 0.9f, 0.76f, 1.0f);
	DirectX::XMFLOAT4 debugColor(1.0f, 0.0f, 0.0f, 1.0f);

	std::shared_ptr<RectangleRenderComponent> leftPlayerRacket =
		std::make_shared<RectangleRenderComponent>(
			racketColor,
			D3D11_FILL_SOLID,
			leftPlayer->position,
			DirectX::XMFLOAT3(0.05f, 0.25f, 0.0f)
		);

	std::shared_ptr<BoxColliderComponent> leftPlayerRacketCollision =
		std::make_shared<BoxColliderComponent>(
			DirectX::XMFLOAT3(leftPlayer->position->x, leftPlayer->position->y, 0.0f),
			DirectX::XMFLOAT3(0.05f, 0.25f, 0.0f)
		);

	std::shared_ptr<RectangleRenderComponent> leftPlayerRacketDebugCollision = 
		std::make_shared<RectangleRenderComponent>(
			debugColor,
			D3D11_FILL_WIREFRAME,
			leftPlayer->position,
			leftPlayerRacketCollision->GetExtents()
		);


	std::shared_ptr<RectangleRenderComponent> rightPlayerRacket =
		std::make_shared<RectangleRenderComponent>(
			racketColor,
			D3D11_FILL_SOLID,
			rightPlayer->position,
			DirectX::XMFLOAT3(0.05f, 0.25f, 0.0f)
		);

	std::shared_ptr<BoxColliderComponent> rightPlayerRacketCollision =
		std::make_shared<BoxColliderComponent>(
			DirectX::XMFLOAT3(rightPlayer->position->x, rightPlayer->position->y, 0.0f),
			DirectX::XMFLOAT3(0.05f, 0.25f, 0.0f)
		);

	std::shared_ptr<RectangleRenderComponent> rightPlayerRacketDebugCollision =
		std::make_shared<RectangleRenderComponent>(
			debugColor,
			D3D11_FILL_WIREFRAME,
			rightPlayer->position,
			rightPlayerRacketCollision->GetExtents()
		);


	std::shared_ptr<RectangleRenderComponent> ballMesh =
		std::make_shared<RectangleRenderComponent>(
			ballColor,
			D3D11_FILL_SOLID,
			ball->position,
			DirectX::XMFLOAT3(0.025f, 0.025f, 0.0f)
		);


	std::shared_ptr<BoxColliderComponent> centralInvisibleWallCollision =
		std::make_shared<BoxColliderComponent>(
			DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT3(0.025f, 1.5f, 0.0f)
		);

	std::shared_ptr<RectangleRenderComponent> centralInvisibleWallDebugCollision =
		std::make_shared<RectangleRenderComponent>(
			debugColor,
			D3D11_FILL_WIREFRAME,
			centralInvisibleWall->position,
			centralInvisibleWallCollision->GetExtents()
		);


	std::shared_ptr<BoxColliderComponent> upInvisibleWallCollision =
		std::make_shared<BoxColliderComponent>(
			DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT3(1.5f, 0.025f, 0.0f)
		);

	std::shared_ptr<RectangleRenderComponent> upInvisibleWallDebugCollision =
		std::make_shared<RectangleRenderComponent>(
			debugColor,
			D3D11_FILL_WIREFRAME,
			upInvisibleWall->position,
			upInvisibleWallCollision->GetExtents()
		);

	std::shared_ptr<BoxColliderComponent> downInvisibleWallCollision =
		std::make_shared<BoxColliderComponent>(
			DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT3(1.5f, 0.025f, 0.0f)
		);

	std::shared_ptr<RectangleRenderComponent> downInvisibleWallDebugCollision =
		std::make_shared<RectangleRenderComponent>(
			debugColor,
			D3D11_FILL_WIREFRAME,
			downInvisibleWall->position,
			downInvisibleWallCollision->GetExtents()
		);

	std::shared_ptr<BoxColliderComponent> leftInvisibleWallCollision =
		std::make_shared<BoxColliderComponent>(
			DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT3(0.025f, 1.5f, 0.0f)
		);

	std::shared_ptr<RectangleRenderComponent> leftInvisibleWallDebugCollision =
		std::make_shared<RectangleRenderComponent>(
			debugColor,
			D3D11_FILL_WIREFRAME,
			leftInvisibleWall->position,
			leftInvisibleWallCollision->GetExtents()
		);

	std::shared_ptr<BoxColliderComponent> rightInvisibleWallCollision =
		std::make_shared<BoxColliderComponent>(
			DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
			DirectX::XMFLOAT3(0.025f, 1.5f, 0.0f)
		);

	std::shared_ptr<RectangleRenderComponent> rightInvisibleWallDebugCollision =
		std::make_shared<RectangleRenderComponent>(
			debugColor,
			D3D11_FILL_WIREFRAME,
			rightInvisibleWall->position,
			rightInvisibleWallCollision->GetExtents()
		);
	

	// Adding all game objects to Game::gameObjects for their initialization
	PingPongGame::instance->gameObjects.push_back(leftPlayer);
	PingPongGame::instance->gameObjects.push_back(rightPlayer);
	PingPongGame::instance->gameObjects.push_back(ball);
	PingPongGame::instance->gameObjects.push_back(centralInvisibleWall);
	PingPongGame::instance->gameObjects.push_back(upInvisibleWall);
	PingPongGame::instance->gameObjects.push_back(downInvisibleWall);
	PingPongGame::instance->gameObjects.push_back(leftInvisibleWall);
	PingPongGame::instance->gameObjects.push_back(rightInvisibleWall);

	leftPlayer->AddComponent(leftPlayerRacket);
	leftPlayer->AddComponent(leftPlayerRacketCollision);
	leftPlayer->AddComponent(leftPlayerRacketDebugCollision);

	rightPlayer->AddComponent(rightPlayerRacket);
	rightPlayer->AddComponent(rightPlayerRacketCollision);
	rightPlayer->AddComponent(rightPlayerRacketDebugCollision);

	ball->AddComponent(ballMesh);

	centralInvisibleWall->AddComponent(centralInvisibleWallCollision);
	centralInvisibleWall->AddComponent(centralInvisibleWallDebugCollision);

	upInvisibleWall->AddComponent(upInvisibleWallCollision);
	upInvisibleWall->AddComponent(upInvisibleWallDebugCollision);

	downInvisibleWall->AddComponent(downInvisibleWallCollision);
	downInvisibleWall->AddComponent(downInvisibleWallDebugCollision);

	leftInvisibleWall->AddComponent(leftInvisibleWallCollision);
	leftInvisibleWall->AddComponent(leftInvisibleWallDebugCollision);

	rightInvisibleWall->AddComponent(rightInvisibleWallCollision);
	rightInvisibleWall->AddComponent(rightInvisibleWallDebugCollision);
}
