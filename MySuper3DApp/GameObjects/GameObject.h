#pragma once
#include "Components/GameObjectComponent.h"

class GameObjectComponent;

class GameObject {
public:
	std::shared_ptr<DirectX::SimpleMath::Vector4> position; // In the future move to Transform class
	std::vector<std::shared_ptr<GameObjectComponent>> components;

	bool wantsToMoveLeft = false;
	bool wantsToMoveRight = false;
	bool wantsToMoveUp = false;
	bool wantsToMoveDown = false;

	bool canMoveLeft = false;
	bool canMoveRight = false;
	bool canMoveUp = false;
	bool canMoveDown = false;

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
	std::optional<T> getComponent();

	/*void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();*/
};

template<typename T>
inline std::optional<T> GameObject::getComponent() {
	for (auto& component : components) {
		T* result = dynamic_cast<T*>(component.get());

		if (result)
			return *result;
	}

	return {};
}
