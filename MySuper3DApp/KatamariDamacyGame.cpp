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

	std::shared_ptr<KatamariDamacyGameObject> testObject1 = std::make_shared<KatamariDamacyGameObject>();
	std::shared_ptr<KatamariDamacyGameObject> testObject2 = std::make_shared<KatamariDamacyGameObject>();
	std::shared_ptr<KatamariDamacyGameObject> testObject3 = std::make_shared<KatamariDamacyGameObject>();
	gameObjects.push_back(testObject1);
	gameObjects.push_back(testObject2);
	gameObjects.push_back(testObject3);


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

	*testObject1->transform->localPosition += {10.0f, 1.5f, 10.0f};
	*testObject2->transform->localPosition += {20.0f, 1.5f, 20.0f};
	*testObject3->transform->localPosition += {30.0f, 1.5f, 30.0f};

	camera->AttachTo(player->transform);
	*camera->transform->localPosition += {0.0f, 15.0f, 20.0f};
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
						secondKatamari->AttachTo(*player);
						*player->transform->localPosition += {0.0f, secondKatamari->collider->boundingSphere->Radius * 2, 0.0f};
						*player->transform->scale *= secondKatamari->collider->boundingSphere->Radius * 2;
						player->collider->boundingSphere->Radius *= secondKatamari->collider->boundingSphere->Radius * 2;
						player->velocity *= secondKatamari->collider->boundingSphere->Radius * 2;
					}
				}
			}
		}
	}

	if (inputDevice->IsKeyDown(Keys::W)) {
		// Player translation and rotation
		player->transform->Translate(camera->OrbitForwardXZ() * player->velocity * Time::DeltaTime());
		*player->transform->localRotation *= Quaternion::CreateFromAxisAngle(camera->OrbitRightXZ(), camera->velocity * Time::DeltaTime());
	}
}
