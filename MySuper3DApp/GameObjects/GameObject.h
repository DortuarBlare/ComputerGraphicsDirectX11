#pragma once
#include "Components/GameObjectComponent.h"

class GameObjectComponent;

class GameObject {
public:
	std::shared_ptr<DirectX::SimpleMath::Vector4> position; // Move to Transform class later

	float velocity = 0.25f; // Move to the rigidbody later
	std::shared_ptr<DirectX::SimpleMath::Vector4> direction; // Move to the rigidbody later

	std::vector<std::shared_ptr<GameObjectComponent>> components;


	bool wantsToMoveLeft = false;
	bool wantsToMoveRight = false;
	bool wantsToMoveUp = false;
	bool wantsToMoveDown = false;

	GameObject();
	GameObject(DirectX::SimpleMath::Vector4 translation, DirectX::SimpleMath::Vector4 direction);
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

	virtual void SetPosition(DirectX::SimpleMath::Vector4 newPosition);
	virtual void Translate(DirectX::SimpleMath::Vector4 translation);
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
