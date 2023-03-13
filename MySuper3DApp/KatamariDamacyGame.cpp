#include "pch.h"
#include "KatamariDamacyGame.h"
#include "TransformComponent.h"

KatamariDamacyGame::KatamariDamacyGame(LPCWSTR name) : Game(name) {
	player = std::make_shared<KatamariDamacyGameObject>(
		"Models/Player.fbx",
		L"Textures/Player.png",
		1.5f,
		0.04
	);
}

void KatamariDamacyGame::CreateInstance(LPCWSTR name) {
	if (!instance)
		instance = std::unique_ptr<KatamariDamacyGame>(new KatamariDamacyGame(name));
}

void KatamariDamacyGame::Initialize() {
	std::shared_ptr<KatamariDamacyGameObject> legoBoyLittle = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoBoy.obj",
		L"Textures/LegoBoy.jpg",
		1.0f,
		0.1f,
		Vector3(0.0f, -0.75f, 0.0f)
	);

	std::shared_ptr<KatamariDamacyGameObject> legoBoyMedium = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoBoy.obj",
		L"Textures/LegoBoy.jpg",
		2.0f,
		0.2f,
		Vector3(0.0f, -1.5f, 0.0f)
	);

	std::shared_ptr<KatamariDamacyGameObject> legoBoyLarge = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoBoy.obj",
		L"Textures/LegoBoy.jpg",
		2.5f,
		0.275f,
		Vector3(0.0f, -2.0f, 0.0f)
	);

	std::shared_ptr<KatamariDamacyGameObject> legoBrickLittle = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoBrick.fbx",
		L"Textures/LegoBrick.png",
		0.6f,
		50.0f
	);

	std::shared_ptr<KatamariDamacyGameObject> legoBrickMedium = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoBrick.fbx",
		L"Textures/LegoBrick.png",
		0.7f,
		55.0f
	);

	std::shared_ptr<KatamariDamacyGameObject> legoBrickLarge = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoBrick.fbx",
		L"Textures/LegoBrick.png",
		0.9f,
		70.0f
	);

	std::shared_ptr<KatamariDamacyGameObject> legoHomerLittle = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoHomer.obj",
		L"Textures/LegoHomer.jpg",
		1.0f,
		0.04f,
		Vector3(-5.0f, -0.25f, 0.0f)
	);

	std::shared_ptr<KatamariDamacyGameObject> legoHomerMedium = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoHomer.obj",
		L"Textures/LegoHomer.jpg",
		1.4f,
		0.06f,
		Vector3(-7.4f, -0.4f, 0.0f)
	);

	std::shared_ptr<KatamariDamacyGameObject> legoHomerLarge = std::make_shared<KatamariDamacyGameObject>(
		"Models/LegoHomer.obj",
		L"Textures/LegoHomer.jpg",
		2.0f,
		0.08f,
		Vector3(-9.5f, -0.6f, 0.0f)
	);


	gameObjects.push_back(std::make_shared<GameObject>()); // Ground
	gameObjects.push_back(std::make_shared<GameObject>()); // Ground
	gameObjects.push_back(std::make_shared<GameObject>()); // Ground
	gameObjects.push_back(std::make_shared<GameObject>()); // Ground
	gameObjects.push_back(std::make_shared<GameObject>()); // Ground
	gameObjects.push_back(std::make_shared<GameObject>()); // Ground
	gameObjects.push_back(std::make_shared<GameObject>()); // Ground
	gameObjects.push_back(std::make_shared<GameObject>()); // Ground
	gameObjects.push_back(std::make_shared<GameObject>()); // Ground
	gameObjects.push_back(player);

	gameObjects.push_back(legoBoyLittle);
	gameObjects.push_back(legoBoyMedium);
	gameObjects.push_back(legoBoyLarge);

	gameObjects.push_back(legoBrickLittle);
	gameObjects.push_back(legoBrickMedium);
	gameObjects.push_back(legoBrickLarge);

	gameObjects.push_back(legoHomerLittle);
	gameObjects.push_back(legoHomerMedium);
	gameObjects.push_back(legoHomerLarge);


	gameObjects[0]->AddComponent(std::make_shared<MeshRenderComponent>("Models/Carpet.glb", L"Textures/Carpet.jpeg"));
	gameObjects[1]->AddComponent(std::make_shared<MeshRenderComponent>("Models/Carpet.glb", L"Textures/Carpet.jpeg"));
	gameObjects[2]->AddComponent(std::make_shared<MeshRenderComponent>("Models/Carpet.glb", L"Textures/Carpet.jpeg"));
	gameObjects[3]->AddComponent(std::make_shared<MeshRenderComponent>("Models/Carpet.glb", L"Textures/Carpet.jpeg"));
	gameObjects[4]->AddComponent(std::make_shared<MeshRenderComponent>("Models/Carpet.glb", L"Textures/Carpet.jpeg"));
	gameObjects[5]->AddComponent(std::make_shared<MeshRenderComponent>("Models/Carpet.glb", L"Textures/Carpet.jpeg"));
	gameObjects[6]->AddComponent(std::make_shared<MeshRenderComponent>("Models/Carpet.glb", L"Textures/Carpet.jpeg"));
	gameObjects[7]->AddComponent(std::make_shared<MeshRenderComponent>("Models/Carpet.glb", L"Textures/Carpet.jpeg"));
	gameObjects[8]->AddComponent(std::make_shared<MeshRenderComponent>("Models/Carpet.glb", L"Textures/Carpet.jpeg"));


	Game::Initialize();

	// Move and scale ground
	float xOffsetCarpet = 57.75f;
	float zOffsetCarpet = 75.0f;
	*gameObjects[0]->transform->localPosition += {0.0f, -0.2f, 0.0f}; // Central carpet
	*gameObjects[0]->transform->scale *= 50;
	
	*gameObjects[1]->transform->localPosition += {0.0f, -0.2f, zOffsetCarpet};
	*gameObjects[1]->transform->scale *= 50;
	*gameObjects[2]->transform->localPosition += {0.0f, -0.2f, -zOffsetCarpet};
	*gameObjects[2]->transform->scale *= 50;
	*gameObjects[3]->transform->localPosition += {xOffsetCarpet, -0.2f, 0.0f};
	*gameObjects[3]->transform->scale *= 50;
	*gameObjects[4]->transform->localPosition += {-xOffsetCarpet, -0.2f, 0.0f};
	*gameObjects[4]->transform->scale *= 50;

	*gameObjects[5]->transform->localPosition += {xOffsetCarpet, -0.2f, zOffsetCarpet};
	*gameObjects[5]->transform->scale *= 50;
	*gameObjects[6]->transform->localPosition += {-xOffsetCarpet, -0.2f, zOffsetCarpet};
	*gameObjects[6]->transform->scale *= 50;
	*gameObjects[7]->transform->localPosition += {xOffsetCarpet, -0.2f, -zOffsetCarpet};
	*gameObjects[7]->transform->scale *= 50;
	*gameObjects[8]->transform->localPosition += {-xOffsetCarpet, -0.2f, -zOffsetCarpet};
	*gameObjects[8]->transform->scale *= 50;


	player->velocity = 4.0f;
	player->transform->localPosition->y = player->collider->boundingSphere->Radius;

	*legoBoyLittle->transform->localPosition += {0.0f, legoBoyLittle->collider->boundingSphere->Radius, 10.0f};
	*legoBoyMedium->transform->localPosition += {10.0f, legoBoyMedium->collider->boundingSphere->Radius, 0.0f};
	*legoBoyLarge->transform->localPosition += {0.0f, legoBoyLarge->collider->boundingSphere->Radius, 30.0f};

	*legoBrickLittle->transform->localPosition += {-5.0f, legoBrickLittle->collider->boundingSphere->Radius, 5.0f};
	*legoBrickLittle->transform->localRotation = Quaternion::CreateFromAxisAngle(Vector3::Right, XM_PIDIV2);

	*legoBrickMedium->transform->localPosition += {10.0f, legoBrickMedium->collider->boundingSphere->Radius, 5.0f};
	*legoBrickMedium->transform->localRotation = Quaternion::CreateFromAxisAngle(Vector3::Right, XM_PIDIV2);

	*legoBrickLarge->transform->localPosition += {20.0f, legoBrickLarge->collider->boundingSphere->Radius, 0.0f};
	*legoBrickLarge->transform->localRotation = Quaternion::CreateFromAxisAngle(Vector3::Right, XM_PIDIV2);

	*legoHomerLittle->transform->localPosition += {0.0f, legoHomerLittle->collider->boundingSphere->Radius, -10.0f};
	*legoHomerMedium->transform->localPosition += {-10.0f, legoHomerMedium->collider->boundingSphere->Radius, 0.0f};
	*legoHomerLarge->transform->localPosition += {20.0f, legoHomerLarge->collider->boundingSphere->Radius, -5.0f};

	camera->AttachTo(player->transform);
}

void KatamariDamacyGame::Update() {
	Game::Update();

	for (auto& gameObject : Game::Instance()->gameObjects) {
		if (player != gameObject) {
			std::optional<SphereColliderComponent> secondSphere = gameObject->GetComponent<SphereColliderComponent>();

			if (secondSphere.has_value()) {
				if (player->collider->Intersects(*secondSphere) && 
					player->collider->boundingSphere->Radius >= secondSphere->boundingSphere->Radius) {
					KatamariDamacyGameObject* secondKatamari = dynamic_cast<KatamariDamacyGameObject*>(gameObject.get());

					if (secondKatamari) {
						secondKatamari->AttachTo(player->transform);

						player->collider->boundingSphere->Radius += secondKatamari->collider->boundingSphere->Radius;
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
