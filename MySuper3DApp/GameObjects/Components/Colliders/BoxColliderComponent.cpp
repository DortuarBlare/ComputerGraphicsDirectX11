#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent() {
	boundingBox = std::make_shared<DirectX::BoundingBox>();
}

BoxColliderComponent::BoxColliderComponent(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents) {
	boundingBox = std::make_shared<DirectX::BoundingBox>(center, extents);
}

void BoxColliderComponent::Initialize() {

}

void BoxColliderComponent::Update() {

}

void BoxColliderComponent::FixedUpdate() {
	/*std::cout <<
		"Object: " << this << " ||| " <<
		"BoundingBox position: " << 
		boundingBox->Center.x << " " <<
		boundingBox->Center.y << " " <<
		boundingBox->Center.z <<
		std::endl;*/

	if (owner->wantsToMoveLeft && !Intersects(DirectX::SimpleMath::Vector3::Left)) {
		*owner->position -= {0.25f * Game::instance->deltaTime, 0.0f, 0.0f, 0.0f};
		boundingBox->Center.x -= 0.25f * Game::instance->deltaTime;
	}
	if (owner->wantsToMoveRight && !Intersects(DirectX::SimpleMath::Vector3::Right)) {
		*owner->position += {0.25f * Game::instance->deltaTime, 0.0f, 0.0f, 0.0f};
		boundingBox->Center.x += 0.25f * Game::instance->deltaTime;
	}
	if (owner->wantsToMoveUp && !Intersects(DirectX::SimpleMath::Vector3::Up)) {
		*owner->position += {0.0f, 0.25f * Game::instance->deltaTime, 0.0f, 0.0f};
		boundingBox->Center.y += 0.25f * Game::instance->deltaTime;
	}
	if (owner->wantsToMoveDown && !Intersects(DirectX::SimpleMath::Vector3::Down)) {
		*owner->position -= {0.0f, 0.25f * Game::instance->deltaTime, 0.0f, 0.0f};
		boundingBox->Center.y -= 0.25f * Game::instance->deltaTime;
	}
}

void BoxColliderComponent::Draw() {

}

void BoxColliderComponent::Reload() {

}

void BoxColliderComponent::DestroyResources() {

}

bool BoxColliderComponent::Intersects(DirectX::SimpleMath::Vector3 direction) {
	bool intersectsOnce = false;
	DirectX::SimpleMath::Vector3 point(boundingBox->Center);
	DirectX::SimpleMath::Ray ray(point, direction);

	if (direction == DirectX::SimpleMath::Vector3::Left)
		point.x -= boundingBox->Extents.x / 2;
	else if (direction == DirectX::SimpleMath::Vector3::Right)
		point.x += boundingBox->Extents.x / 2;
	else if (direction == DirectX::SimpleMath::Vector3::Up)
		point.y += boundingBox->Extents.y / 2;
	else if (direction == DirectX::SimpleMath::Vector3::Down)
		point.y -= boundingBox->Extents.y / 2;
	

	for (auto& gameObject : Game::instance->gameObjects) {
		if (gameObject != owner) {
			for (auto& collider : gameObject->components) {
				BoxColliderComponent* bcc = dynamic_cast<BoxColliderComponent*>(collider.get());
				float outDistance;

				if (bcc) {
					if (ray.Intersects(*bcc->boundingBox, outDistance)) {
						if (outDistance <= 0.01f) {
							std::cout <<
								"Object: " << this << " ||| " <<
								"Intersects distance: " <<
								outDistance <<
								std::endl;
							intersectsOnce = true;
							owner->canMoveLeft = false;
							return true;
						}
					}
				}
			}
		}
	}

	if (!intersectsOnce)
		return false;
}

DirectX::XMFLOAT3 BoxColliderComponent::GetCenter() {
	return boundingBox->Center;
}

DirectX::XMFLOAT3 BoxColliderComponent::GetExtents() {
	return boundingBox->Extents;
}
