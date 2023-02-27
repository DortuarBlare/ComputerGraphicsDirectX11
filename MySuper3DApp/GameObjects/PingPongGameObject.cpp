#include "PingPongGameObject.h"

PingPongGameObject::PingPongGameObject() : GameObject() {}

PingPongGameObject::PingPongGameObject(DirectX::SimpleMath::Vector4 position) : GameObject(position, {}) {}


void PingPongGameObject::FixedUpdate() {
	if (wantsToMoveLeft) {
		if (!collider->Intersects(DirectX::SimpleMath::Vector3::Left)) {
			DirectX::SimpleMath::Vector4 translateDirection = DirectX::SimpleMath::Vector4::UnitX;
			translateDirection *= -1;
			Translate(translateDirection * velocity * Game::instance->deltaTime);
		}
	}
	if (wantsToMoveRight) {
		if (!collider->Intersects(DirectX::SimpleMath::Vector3::Right)) {
			DirectX::SimpleMath::Vector4 translateDirection = DirectX::SimpleMath::Vector4::UnitX;
			Translate(translateDirection * velocity * Game::instance->deltaTime);
		}
	}
	if (wantsToMoveUp) {
		if (!collider->Intersects(DirectX::SimpleMath::Vector3::Up)) {
			DirectX::SimpleMath::Vector4 translateDirection = DirectX::SimpleMath::Vector4::UnitY;
			Translate(translateDirection * velocity * Game::instance->deltaTime);
		}
	}
	if (wantsToMoveDown) {
		if (!collider->Intersects(DirectX::SimpleMath::Vector3::Down)) {
			DirectX::SimpleMath::Vector4 translateDirection = DirectX::SimpleMath::Vector4::UnitY;
			translateDirection *= -1;
			Translate(translateDirection * velocity * Game::instance->deltaTime);
		}
	}
}


void PingPongGameObject::Reflect(BoxColliderComponent boxCollider) {
	DirectX::SimpleMath::Vector4 normalVector = {};

	// Collider is located on the right
	if (boxCollider.GetCenter().x > position->x) {
		normalVector = {
		position->x + (boxCollider.GetCenter().x + boxCollider.GetExtents().x * 2),
		boxCollider.GetCenter().y,
		0.0f,
		0.0f
		};
	}
	// Collider is located on the left
	else if (boxCollider.GetCenter().x < position->x) {
		normalVector = {
			position->x - (boxCollider.GetCenter().x + boxCollider.GetExtents().x * 2),
			boxCollider.GetCenter().y,
			0.0f,
			0.0f
		};
		//normalVector *= -1;
	}
	normalVector.Normalize();
	std::cout << "Reflect normal: " << normalVector.x << ' ' << normalVector.y << std::endl;
	*direction = DirectX::SimpleMath::Vector4::Reflect(*direction, normalVector);
}

void PingPongGameObject::SetPosition(DirectX::SimpleMath::Vector4 newPosition) {
	GameObject::SetPosition(newPosition);
	collider->GetCenter().x = position->x;
	collider->GetCenter().y = position->y;
}

void PingPongGameObject::Translate(DirectX::SimpleMath::Vector4 translation) {
	float distanceToCollision = 0.0f;
	DirectX::SimpleMath::Vector3 direction = { translation.x, translation.y, 0.0f };

	if (collider->Intersects(direction, distanceToCollision)) {
		if (distanceToCollision <= 0.01f && distanceToCollision > 0.0f) {
			/*translation.Normalize();
			translation *= 0.01f;
			GameObject::Translate(translation);
			collider->GetCenter().x = position->x;
			collider->GetCenter().y = position->y;*/
			return;
		}
	}

	//std::cout << "Translation: " << translation.x << ' ' << translation.y << std::endl;
	GameObject::Translate(translation);
	collider->GetCenter().x = position->x;
	collider->GetCenter().y = position->y;
}
