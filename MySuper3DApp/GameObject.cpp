#include "pch.h"
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "TransformComponent.h"

GameObject::GameObject() {
	transform = std::make_shared<TransformComponent>();
	direction = std::make_shared<DirectX::SimpleMath::Vector3>();
}


void GameObject::Initialize() {
	for (auto& component : components)
		component->Initialize();
}

void GameObject::Update() {
	for (auto& component : components)
		component->Update();
}

void GameObject::FixedUpdate() {
	for (auto& component : components)
		component->FixedUpdate();
}

void GameObject::Draw() {
	for (auto& component : components)
		component->Draw();
}

void GameObject::Reload() {
	for (auto& component : components)
		component->Reload();
}

void GameObject::DestroyResources() {
	for (auto& component : components)
		component->DestroyResources();
}


void GameObject::AddComponent(std::shared_ptr<GameObjectComponent> component) {
	for (auto& gameObject : Game::Instance()->gameObjects) {
		if (gameObject.get() == this)
			component->owner = gameObject;
	}

	components.push_back(component);
}


void GameObject::SetPosition(DirectX::SimpleMath::Vector3 newPosition) {
	*transform->localPosition = newPosition;
}

/*
* Moves the position in the direction and distance of "translation"
*/
void GameObject::Translate(DirectX::SimpleMath::Vector3 translation) {
	*transform->localPosition += translation;
}
