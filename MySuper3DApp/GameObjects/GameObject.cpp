#include "GameObject.h"

GameObject::GameObject() {
	position = std::make_shared<DirectX::SimpleMath::Vector4>();
	direction = std::make_shared<DirectX::SimpleMath::Vector4>();
}

GameObject::GameObject(DirectX::SimpleMath::Vector4 position, DirectX::SimpleMath::Vector4 direction) {
	this->position = std::make_shared<DirectX::SimpleMath::Vector4>(position);
	this->direction = std::make_shared<DirectX::SimpleMath::Vector4>(direction);
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
	for (auto& gameObject : Game::instance->gameObjects) {
		if (gameObject.get() == this)
			component->owner = gameObject;
	}

	components.push_back(component);
}

void GameObject::SetPosition(DirectX::SimpleMath::Vector4 newPosition) {
	*position = newPosition;
}

/*
* Moves the position in the direction and distance of "translation"
*/
void GameObject::Translate(DirectX::SimpleMath::Vector4 translation) {
	*position += translation;
}
