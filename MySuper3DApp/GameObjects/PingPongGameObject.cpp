#include "PingPongGameObject.h"

PingPongGameObject::PingPongGameObject() : GameObject() {}

PingPongGameObject::PingPongGameObject(DirectX::SimpleMath::Vector4 position) : GameObject(position) {}

void PingPongGameObject::Translate(DirectX::SimpleMath::Vector4 newPosition) {
	GameObject::Translate(newPosition);
	collider->GetCenter().x = position->x;
	collider->GetCenter().y = position->y;
}
