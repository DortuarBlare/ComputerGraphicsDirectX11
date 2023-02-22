#pragma once
#include "Components/GameObjectComponent.h"

class GameObjectComponent;

class GameObject {
public:
	std::shared_ptr<DirectX::SimpleMath::Vector4> position; // In the future move to Transform class
	std::vector<std::shared_ptr<GameObjectComponent>> components;

	GameObject();
	GameObject(DirectX::SimpleMath::Vector4 position);
	virtual ~GameObject() = default;

	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Draw();
	virtual void Reload();
	virtual void DestroyResources();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
};
