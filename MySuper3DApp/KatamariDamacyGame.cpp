#include "pch.h"
#include "KatamariDamacyGame.h"
#include "TransformComponent.h"

KatamariDamacyGame::KatamariDamacyGame(LPCWSTR name) : Game(name) {
	ground = std::make_shared<GameObject>();
	player = std::make_shared<KatamariDamacyGameObject>();
	testObject = std::make_shared<KatamariDamacyGameObject>();
}

void KatamariDamacyGame::CreateInstance(LPCWSTR name) {
	if (!instance)
		instance = std::unique_ptr<KatamariDamacyGame>(new KatamariDamacyGame(name));
}

void KatamariDamacyGame::Initialize() {
	gameObjects.push_back(ground);
	gameObjects.push_back(player);
	gameObjects.push_back(testObject);


	std::shared_ptr<RectangleRenderComponent> groundMesh =
		std::make_shared< RectangleRenderComponent>(
			L"Textures/Carpet.jpg",
			D3D11_FILL_SOLID,
			XMFLOAT3(100.0f, 100.0f, 0.0f)
		);

	ground->AddComponent(groundMesh);


	Game::Initialize();


	*ground->transform->localRotation *= Quaternion::CreateFromAxisAngle(Vector3::Right, XM_PIDIV2);

	player->velocity = 4.0f;
	*player->transform->localPosition += {0.0f, 1.5f, 0.0f};

	*testObject->transform->localPosition += {3.0f, 1.5f, 0.0f};
	testObject->AttachTo(*player);

	camera->AttachTo(player->transform);
	*camera->transform->localPosition += {0.0f, 15.0f, 20.0f};
}

void KatamariDamacyGame::Update() {
	Game::Update();

	if (inputDevice->IsKeyDown(Keys::W)) {
		// Player translation and rotation
		player->transform->Translate(camera->OrbitForwardXZ() * camera->velocity * Time::DeltaTime());
		*player->transform->localRotation *= Quaternion::CreateFromAxisAngle(camera->OrbitRightXZ(), player->velocity * Time::DeltaTime());
	}
}
