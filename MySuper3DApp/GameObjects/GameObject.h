#pragma once
#include "Components/GameObjectComponent.h"

class GameObjectComponent;

class GameObject {
public:
	std::shared_ptr<DirectX::SimpleMath::Vector4> position; // In the future move to Transform class
	std::vector<std::shared_ptr<GameObjectComponent>> components;
	float velocity = 0.25f; // In the future move to Rigidbody class

	bool wantsToMoveLeft = false;
	bool wantsToMoveRight = false;
	bool wantsToMoveUp = false;
	bool wantsToMoveDown = false;

	GameObject();
	GameObject(DirectX::SimpleMath::Vector4 position);
	virtual ~GameObject() = default;

	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Draw();
	virtual void Reload();
	virtual void DestroyResources();

	void AddComponent(std::shared_ptr<GameObjectComponent> component);

	template<typename T>
	std::optional<T> GetComponent();

	virtual void Translate(DirectX::SimpleMath::Vector4 newPosition);
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
