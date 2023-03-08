#include "pch.h"
#include "PingPongGame.h"
#include "TransformComponent.h"

PingPongGame::PingPongGame(LPCWSTR name) : Game(name) {
	leftPlayerScore = 0;
	rightPlayerScore = 0;
	leftPlayer = std::make_shared<PingPongRacket>();
	leftPlayer->velocity = 0.75f;
	rightPlayer = std::make_shared<PingPongRacket>();
	rightPlayer->velocity = 0.75f;
	ball = std::make_shared<PingPongBall>();
	centralInvisibleWall = std::make_shared<PingPongGameObject>();
	upInvisibleWall = std::make_shared<PingPongGameObject>();
	downInvisibleWall = std::make_shared<PingPongGameObject>();
	leftInvisibleWall = std::make_shared<PingPongGameObject>();
	rightInvisibleWall = std::make_shared<PingPongGameObject>();
}

void PingPongGame::Initialize() {
	Game::Initialize();

	*leftPlayer->transform->localPosition -= {0.5f, 0.0f, 0.0f};
	*rightPlayer->transform->localPosition += {0.5f, 0.0f, 0.0f};
	leftPlayer->GetComponent<BoxColliderComponent>().value().GetCenter().x -= 0.5f;
	rightPlayer->GetComponent<BoxColliderComponent>().value().GetCenter().x += 0.5f;

	ball->direction->x = -1.0f;

	*upInvisibleWall->transform->localPosition += {0.0f, 1.0f, 0.0f};
	upInvisibleWall->GetComponent<BoxColliderComponent>().value().GetCenter().y += 1.0f;

	*downInvisibleWall->transform->localPosition -= {0.0f, 1.0f, 0.0f};
	downInvisibleWall->GetComponent<BoxColliderComponent>().value().GetCenter().y -= 1.0f;

	*leftInvisibleWall->transform->localPosition -= {1.0f, 0.0f, 0.0f};
	leftInvisibleWall->GetComponent<BoxColliderComponent>().value().GetCenter().x -= 1.0f;

	*rightInvisibleWall->transform->localPosition += {1.0f, 0.0f, 0.0f};
	rightInvisibleWall->GetComponent<BoxColliderComponent>().value().GetCenter().x += 1.0f;
}

/*
* Call Game::Update() for base logic
* Handle input player here because of better time control
*/
void PingPongGame::Update() {
	Game::Update();


	// Left player handle input
	*leftPlayer->translateDirection = DirectX::SimpleMath::Vector3::Zero;

	if (inputDevice->IsKeyDown(Keys::A))
		*leftPlayer->translateDirection += DirectX::SimpleMath::Vector3::Left;

	if (inputDevice->IsKeyDown(Keys::D))
		*leftPlayer->translateDirection += DirectX::SimpleMath::Vector3::Right;

	if (inputDevice->IsKeyDown(Keys::W))
		*leftPlayer->translateDirection += DirectX::SimpleMath::Vector3::Up;

	if (inputDevice->IsKeyDown(Keys::S))
		*leftPlayer->translateDirection += DirectX::SimpleMath::Vector3::Down;


	// Right player handle input
	*rightPlayer->translateDirection = DirectX::SimpleMath::Vector3::Zero;

	if (inputDevice->IsKeyDown(Keys::Left))
		*rightPlayer->translateDirection += DirectX::SimpleMath::Vector3::Left;

	if (inputDevice->IsKeyDown(Keys::Right))
		*rightPlayer->translateDirection += DirectX::SimpleMath::Vector3::Right;

	if (inputDevice->IsKeyDown(Keys::Up))
		*rightPlayer->translateDirection += DirectX::SimpleMath::Vector3::Up;

	if (inputDevice->IsKeyDown(Keys::Down))
		*rightPlayer->translateDirection += DirectX::SimpleMath::Vector3::Down;

	
	if (ball->transform->localPosition->x < -1.0f) {
		rightPlayerScore++;
		RestartRound();
	}
	else if (ball->transform->localPosition->x > 1.0f) {
		leftPlayerScore++;
		RestartRound();
	}
}

/*
* Call Game::FixedUpdate() for base physics
* Handle some unique physics here
*/
void PingPongGame::FixedUpdate() {
	Game::FixedUpdate();

	if (ball->GetComponent<BoxColliderComponent>().value().Intersects(DirectX::SimpleMath::Vector3::Left)) {
		ball->velocity *= 1.1f;
		ball->Reflect(*leftPlayer->collider);
	}
	else if (ball->GetComponent<BoxColliderComponent>().value().Intersects(DirectX::SimpleMath::Vector3::Right)) {
		ball->velocity *= 1.1f;
		ball->Reflect(*rightPlayer->collider);
	}
	else if (ball->GetComponent<BoxColliderComponent>().value().Intersects(DirectX::SimpleMath::Vector3::Up))
		ball->Reflect(*upInvisibleWall->collider);
	else if (ball->GetComponent<BoxColliderComponent>().value().Intersects(DirectX::SimpleMath::Vector3::Down))
		ball->Reflect(*downInvisibleWall->collider);

	ball->Translate(*ball->direction * ball->velocity * Time::DeltaTime());
}

/*
* There is no public access to constructor because of "Singleton" pattern
* Need to use this method to create Game::instance (PingPongGame)
*/
void PingPongGame::CreateInstance(LPCWSTR name) {
	if (!instance)
		instance = std::unique_ptr<PingPongGame>(new PingPongGame(name));
}

/*
* Configure game objects before run
* Call Game::Run() for basic logic
*/
void PingPongGame::Run(int screenWidth, int screenHeight, bool fullscreen) {
	ConfigureGameObjects();
	Game::Run(screenWidth, screenHeight, fullscreen);
}

/*
* Set default values of all dynamic game objects
*/
void PingPongGame::RestartRound() {
	leftPlayer->velocity = 0.75f;
	rightPlayer->velocity = 0.75f;
	ball->velocity = 0.25f;
	ball->SetPosition({ 0.0f, 0.0f, 0.0f });

	WCHAR text[100];
	swprintf_s(text, TEXT("Left player score: %i ||| Right player score: %i"), leftPlayerScore, rightPlayerScore);
	SetWindowText(renderSystem->display->GetHWnd(), text);
}

/*
* Configure all ping pong game objects
* Need to call before PingPongGame::Initialize()
*/
void PingPongGame::ConfigureGameObjects() {
	DirectX::SimpleMath::Color racketColor(0.67f, 0.9f, 0.76f, 1.0f);
	DirectX::SimpleMath::Color ballColor(0.67f, 0.9f, 0.76f, 1.0f);
	DirectX::SimpleMath::Color debugColor(1.0f, 0.0f, 0.0f, 1.0f);

	std::shared_ptr<RectangleRenderComponent> leftPlayerMesh =
		std::make_shared<RectangleRenderComponent>(
			racketColor,
			D3D11_FILL_SOLID,
			DirectX::XMFLOAT3(0.05f, 0.25f, 0.0f)
		);

	std::shared_ptr<BoxColliderComponent> leftPlayerRacketCollision =
		std::make_shared<BoxColliderComponent>(
			DirectX::XMFLOAT3(leftPlayer->transform->localPosition->x, leftPlayer->transform->localPosition->y, 0.0f),
			DirectX::XMFLOAT3(0.05f, 0.25f, 0.0f)
		);

	std::shared_ptr<RectangleRenderComponent> leftPlayerRacketDebugCollision =
		std::make_shared<RectangleRenderComponent>(
			debugColor,
			D3D11_FILL_WIREFRAME,
			leftPlayerRacketCollision->GetExtents()
		);


	std::shared_ptr<RectangleRenderComponent> rightPlayerMesh =
		std::make_shared<RectangleRenderComponent>(
			racketColor,
			D3D11_FILL_SOLID,
			DirectX::XMFLOAT3(0.05f, 0.25f, 0.0f)
		);

	std::shared_ptr<BoxColliderComponent> rightPlayerRacketCollision =
		std::make_shared<BoxColliderComponent>(
			DirectX::XMFLOAT3(rightPlayer->transform->localPosition->x, rightPlayer->transform->localPosition->y, 0.0f),
			DirectX::XMFLOAT3(0.05f, 0.25f, 0.0f)
		);

	std::shared_ptr<RectangleRenderComponent> rightPlayerRacketDebugCollision =
		std::make_shared<RectangleRenderComponent>(
			debugColor,
			D3D11_FILL_WIREFRAME,
			rightPlayerRacketCollision->GetExtents()
		);


	std::shared_ptr<CircleRenderComponent> ballMesh =
		std::make_shared<CircleRenderComponent>(
			ballColor,
			D3D11_FILL_SOLID,
			0.025f, // Radius
			30 // Points amount
		);

	std::shared_ptr<BoxColliderComponent> ballCollision =
		std::make_shared<BoxColliderComponent>(
			DirectX::XMFLOAT3(ball->transform->localPosition->x, ball->transform->localPosition->y, 0.0f),
			DirectX::XMFLOAT3(0.025f, 0.025f, 0.0f)
		);

	std::shared_ptr<RectangleRenderComponent> ballDebugCollision =
		std::make_shared<RectangleRenderComponent>(
			debugColor,
			D3D11_FILL_WIREFRAME,
			ballCollision->GetExtents()
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

	leftPlayer->mesh = leftPlayerMesh;
	leftPlayer->AddComponent(leftPlayerMesh);
	leftPlayer->collider = leftPlayerRacketCollision;
	leftPlayer->AddComponent(leftPlayerRacketCollision);
	leftPlayer->AddComponent(leftPlayerRacketDebugCollision);

	rightPlayer->mesh = rightPlayerMesh;
	rightPlayer->AddComponent(rightPlayerMesh);
	rightPlayer->collider = rightPlayerRacketCollision;
	rightPlayer->AddComponent(rightPlayerRacketCollision);
	rightPlayer->AddComponent(rightPlayerRacketDebugCollision);

	ball->mesh = ballMesh;
	ball->AddComponent(ballMesh);
	ball->collider = ballCollision;
	ball->AddComponent(ballCollision);
	ball->AddComponent(ballDebugCollision);
	ball->collider->noCollisionGameObjects.push_back(centralInvisibleWall);
	ball->collider->noCollisionGameObjects.push_back(leftInvisibleWall);
	ball->collider->noCollisionGameObjects.push_back(rightInvisibleWall);

	centralInvisibleWall->AddComponent(centralInvisibleWallCollision);
	centralInvisibleWall->collider = centralInvisibleWallCollision;
	centralInvisibleWall->AddComponent(centralInvisibleWallDebugCollision);

	upInvisibleWall->AddComponent(upInvisibleWallCollision);
	upInvisibleWall->collider = upInvisibleWallCollision;
	upInvisibleWall->AddComponent(upInvisibleWallDebugCollision);

	downInvisibleWall->AddComponent(downInvisibleWallCollision);
	downInvisibleWall->collider = downInvisibleWallCollision;
	downInvisibleWall->AddComponent(downInvisibleWallDebugCollision);

	leftInvisibleWall->AddComponent(leftInvisibleWallCollision);
	leftInvisibleWall->collider = leftInvisibleWallCollision;
	leftInvisibleWall->AddComponent(leftInvisibleWallDebugCollision);

	rightInvisibleWall->AddComponent(rightInvisibleWallCollision);
	rightInvisibleWall->collider = rightInvisibleWallCollision;
	rightInvisibleWall->AddComponent(rightInvisibleWallDebugCollision);
}
