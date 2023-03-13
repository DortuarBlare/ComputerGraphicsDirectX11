#include "pch.h"
#include "KatamariDamacyGame.h"
#include "TransformComponent.h"

KatamariDamacyGame::KatamariDamacyGame(LPCWSTR name) : Game(name) {
	ground = std::make_shared<GameObject>();
	player = std::make_shared<KatamariDamacyGameObject>(
		"Models/Player.fbx",
		L"Textures/Player.png",
		2,
		0.0575
	);
}

void KatamariDamacyGame::CreateInstance(LPCWSTR name) {
	if (!instance)
		instance = std::unique_ptr<KatamariDamacyGame>(new KatamariDamacyGame(name));
}

void KatamariDamacyGame::Initialize() {
	gameObjects.push_back(ground);
	gameObjects.push_back(player);

	std::shared_ptr<KatamariDamacyGameObject> testObject1 = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoBoy.obj",
		L"Textures/LegoBoy.jpg",
		1.0f,
		0.1f,
		Vector3(0.0f, -0.75f, 0.0f)
	);

	std::shared_ptr<KatamariDamacyGameObject> testObject2 = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoBoy.obj",
		L"Textures/LegoBoy.jpg",
		1.0f,
		0.1f
	);

	std::shared_ptr<KatamariDamacyGameObject> testObject3 = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoBoy.obj",
		L"Textures/LegoBoy.jpg",
		1.0f,
		0.1f
	);

	std::shared_ptr<KatamariDamacyGameObject> testObject4 = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoBoy.obj",
		L"Textures/LegoBoy.jpg",
		1.0f,
		0.1f
	);

	gameObjects.push_back(testObject1);
	gameObjects.push_back(testObject2);
	gameObjects.push_back(testObject3);
	gameObjects.push_back(testObject4);


	std::shared_ptr<MeshRenderComponent> groundMesh =
		std::make_shared<MeshRenderComponent>(
			"Models/Carpet.glb",
			L"Textures/Carpet.jpeg"
		);

	ground->AddComponent(groundMesh);


	Game::Initialize();

	// Move and scale ground
	ground->transform->localPosition->y -= 0.2f;
	*ground->transform->scale *= 50;

	player->velocity = 4.0f;
	player->transform->localPosition->y = player->collider->boundingSphere->Radius;

	*testObject1->transform->localPosition += {0.0f, testObject1->collider->boundingSphere->Radius, 10.0f};
	*testObject2->transform->localPosition += {0.0f, testObject2->collider->boundingSphere->Radius, 17.5f};
	*testObject3->transform->localPosition += {0.0f, testObject3->collider->boundingSphere->Radius, 40.0f};
	*testObject4->transform->localPosition += {0.0f, testObject4->collider->boundingSphere->Radius, 50.0f};

	camera->AttachTo(player->transform);
}

void KatamariDamacyGame::Update() {
	Game::Update();

	for (auto& gameObject : Game::Instance()->gameObjects) {
		if (player != gameObject) {
			std::optional<SphereColliderComponent> secondSphere = gameObject->GetComponent<SphereColliderComponent>();

			if (secondSphere.has_value()) {
				if (player->collider->Intersects(*secondSphere)) {
					KatamariDamacyGameObject* secondKatamari = dynamic_cast<KatamariDamacyGameObject*>(gameObject.get());

					if (secondKatamari) {
						secondKatamari->AttachTo(player->transform);

						player->collider->boundingSphere->Radius += secondKatamari->collider->boundingSphere->Radius * 2;
						player->colliderDebugSphere->ChangeRadius(player->collider->boundingSphere->Radius);
						player->transform->localPosition->y = player->collider->boundingSphere->Radius;
					}
				}
			}
		}
	}

	if (inputDevice->IsKeyDown(Keys::W)) {
		// Player translation and rotation
		player->transform->SetPosition(player->transform->GetPosition() + camera->OrbitForwardXZ() * camera->velocity * Time::DeltaTime());
		player->transform->SetRotation(
			player->transform->GetRotation() *
			Quaternion::CreateFromAxisAngle(camera->OrbitRightXZ(), camera->velocity * Time::DeltaTime())
		);
	}
}
