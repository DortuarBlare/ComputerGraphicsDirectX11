#include "pch.h"
#include "KatamariDamacyGame.h"
#include "TransformComponent.h"

KatamariDamacyGame::KatamariDamacyGame(LPCWSTR name) : Game(name) {
	ground = std::make_shared<GameObject>();
	player = std::make_shared<KatamariDamacyGameObject>();
}

void KatamariDamacyGame::CreateInstance(LPCWSTR name) {
	if (!instance)
		instance = std::unique_ptr<KatamariDamacyGame>(new KatamariDamacyGame(name));
}

void KatamariDamacyGame::Initialize() {
	gameObjects.push_back(ground);
	gameObjects.push_back(player);

	std::shared_ptr<RectangleRenderComponent> groundMesh =
		std::make_shared< RectangleRenderComponent>(
			L"Textures/Grass.jpg",
			Color(0.13f, 0.55f, 0.13f),
			D3D11_FILL_SOLID,
			XMFLOAT3(50.0f, 50.0f, 0.0f)
		);

	ground->AddComponent(groundMesh);

	Game::Initialize();

	*ground->transform->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::Right, XM_PIDIV2);

	*player->transform->localPosition += {0.0f, 1.5f, 0.0f};

	camera->AttachTo(player->transform);
	*camera->transform->localPosition += {0.0f, 15.0f, 20.0f};
}

void KatamariDamacyGame::Update() {
	Game::Update();
	
	if (inputDevice->IsKeyDown(Keys::W))
		player->Translate(camera->Forward() * camera->velocity * Time::DeltaTime());
}

void KatamariDamacyGame::FixedUpdate() {
	Game::FixedUpdate();
}

void KatamariDamacyGame::Run(int screenWidth, int screenHeight, bool fullscreen) {
	Game::Run(screenWidth, screenHeight, fullscreen);
}
