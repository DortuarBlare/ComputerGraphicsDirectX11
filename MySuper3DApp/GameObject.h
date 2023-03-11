#pragma once
#include "pch.h"

class GameObjectComponent;
class TransformComponent;

class GameObject {
public:
	std::shared_ptr<TransformComponent> transform;

	float velocity = 0.25f; // Move to the rigidbody later
	std::shared_ptr<DirectX::SimpleMath::Vector3> direction; // Move to the rigidbody later

	std::vector<std::shared_ptr<GameObjectComponent>> components;

	GameObject();

	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
	virtual void Reload();
	virtual void DestroyResources();

	void AddComponent(std::shared_ptr<GameObjectComponent> component);

	template<typename T>
	std::optional<T> GetComponent();

};

template<typename T>
inline std::optional<T> GameObject::GetComponent() {
	for (auto& component : components) {
		T* result = dynamic_cast<T*>(component.get());

		if (result)
			return *result;
	}

	return std::nullopt;
}
