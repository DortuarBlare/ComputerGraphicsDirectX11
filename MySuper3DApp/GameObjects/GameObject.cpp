#include "GameObject.h"

GameObject::GameObject() {
	position = std::make_shared<DirectX::SimpleMath::Vector4>();
}

GameObject::GameObject(DirectX::SimpleMath::Vector4 position) {
	this->position = std::make_shared<DirectX::SimpleMath::Vector4>(position);
}

void GameObject::Initialize() {
	for (auto& component : components)
		component->Initialize();
}

/*
* For logic
*/
void GameObject::Update() {
	for (auto& component : components)
		component->Update();
}

/*
* For physics
*/
void GameObject::FixedUpdate() {
	for (auto& component : components)
		component->FixedUpdate();
}

/*
* For rendering
*/
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
