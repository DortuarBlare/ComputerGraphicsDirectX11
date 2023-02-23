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
	/*std::cout << std::endl <<
		"---------------------------------------------------------------------------------------" << std::endl <<
		"GameObject: " << owner << " ||| "
		"GameObject Position: " << owner->position->x << " " << owner->position->y << " " << owner->position->z << " " <<
		std::endl;*/
	
	if (owner->wantsToMoveLeft) {
		if (!Intersects(DirectX::SimpleMath::Vector3::Left)) {
			*owner->position -= {owner->velocity * Game::instance->deltaTime, 0.0f, 0.0f, 0.0f};
			boundingBox->Center.x -= owner->velocity * Game::instance->deltaTime;
		}
	}
	if (owner->wantsToMoveRight) {
		if (!Intersects(DirectX::SimpleMath::Vector3::Right)) {
			*owner->position += {owner->velocity * Game::instance->deltaTime, 0.0f, 0.0f, 0.0f};
			boundingBox->Center.x += owner->velocity * Game::instance->deltaTime;
		}
	}
	if (owner->wantsToMoveUp) {
		if (!Intersects(DirectX::SimpleMath::Vector3::Up)) {
			*owner->position += {0.0f, owner->velocity * 2.0f * Game::instance->deltaTime, 0.0f, 0.0f};
			boundingBox->Center.y += owner->velocity * 2.0f * Game::instance->deltaTime;
		}
	}
	if (owner->wantsToMoveDown) {
		if (!Intersects(DirectX::SimpleMath::Vector3::Down)) {
			*owner->position -= {0.0f, owner->velocity * 2.0f * Game::instance->deltaTime, 0.0f, 0.0f};
			boundingBox->Center.y -= owner->velocity * 2.0f * Game::instance->deltaTime;
		}
	}
}

void BoxColliderComponent::Draw() {

}

void BoxColliderComponent::Reload() {

}

void BoxColliderComponent::DestroyResources() {

}

bool BoxColliderComponent::Intersects(DirectX::SimpleMath::Vector3 direction) {
	//DirectX::SimpleMath::Vector3 point(boundingBox->Center);
	//
	//if (direction == DirectX::SimpleMath::Vector3::Left)
	//	point.x -= boundingBox->Extents.x;
	//else if (direction == DirectX::SimpleMath::Vector3::Right)
	//	point.x += boundingBox->Extents.x;
	//else if (direction == DirectX::SimpleMath::Vector3::Up)
	//	point.y += boundingBox->Extents.y;
	//else if (direction == DirectX::SimpleMath::Vector3::Down)
	//	point.y -= boundingBox->Extents.y;
	//
	//DirectX::SimpleMath::Ray ray(point, direction);
	//
	//for (auto& gameObject : Game::instance->gameObjects) {
	//	if (gameObject != owner) {
	//		for (auto& collider : gameObject->components) {
	//			BoxColliderComponent* bcc = dynamic_cast<BoxColliderComponent*>(collider.get());
	//			float outDistance;
	//
	//			if (bcc) {
	//				if (ray.Intersects(*bcc->boundingBox, outDistance)) {
	//					if (outDistance <= 0.005f) {
	//						/*std::cout <<
	//							"BoxColliderComponent: " << this << " ||| " <<
	//							"BoundingBox position: " << boundingBox->Center.x << " " << boundingBox->Center.y << " " << boundingBox->Center.z <<" ||| " <<
	//							"BoundingBox extents: " << boundingBox->Extents.x << " " << boundingBox->Extents.y << " " << boundingBox->Extents.z << std::endl <<
	//
	//							"Ray position: " << ray.position.x << " " << ray.position.y << " " << ray.position.z << " ||| " <<
	//							"Ray direction: " << ray.direction.x << " " << ray.direction.y << " " << ray.direction.z << " ||| " <<
	//							"Intersects distance: " << outDistance << std::endl <<
	//
	//							"BoxColliderComponent2: " << bcc << " ||| " <<
	//							"BoundingBox2 position: " << bcc->boundingBox->Center.x << " " << bcc->boundingBox->Center.y << " " << bcc->boundingBox->Center.z << " ||| " <<
	//							"BoundingBox2 extents: " << bcc->boundingBox->Extents.x << " " << bcc->boundingBox->Extents.y << " " << bcc->boundingBox->Extents.z << std::endl <<
	//							"---------------------------------------------------------------------------------------" << std::endl <<
	//							std::endl;*/
	//						return true;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	for (auto& gameObject : Game::instance->gameObjects) {
		if (gameObject != owner) {
			std::optional<BoxColliderComponent> secondBox = gameObject->getComponent<BoxColliderComponent>();

			if (secondBox.has_value()) {
				DirectX::BoundingBox boundingBoxWithOffset(boundingBox->Center, boundingBox->Extents);
				boundingBoxWithOffset.Center.x += direction.x / 100;
				boundingBoxWithOffset.Center.y += direction.y / 100;

				if (boundingBoxWithOffset.Intersects(*secondBox.value().boundingBox)) {
					/*std::cout <<
							"BoxColliderComponent: " << this << " ||| " <<
							"BoundingBox position: " << boundingBox->Center.x << " " << boundingBox->Center.y << " " << boundingBox->Center.z <<" ||| " <<
							"BoundingBox extents: " << boundingBox->Extents.x << " " << boundingBox->Extents.y << " " << boundingBox->Extents.z << std::endl <<

							"BoxColliderComponent2: " << bcc << " ||| " <<
							"BoundingBox2 position: " << bcc->boundingBox->Center.x << " " << bcc->boundingBox->Center.y << " " << bcc->boundingBox->Center.z << " ||| " <<
							"BoundingBox2 extents: " << bcc->boundingBox->Extents.x << " " << bcc->boundingBox->Extents.y << " " << bcc->boundingBox->Extents.z << std::endl <<
							"---------------------------------------------------------------------------------------" << std::endl <<
							std::endl;*/
					return true;
				}
			}
		}
	}

	return false;
}

DirectX::XMFLOAT3& BoxColliderComponent::GetCenter() {
	return boundingBox->Center;
}

DirectX::XMFLOAT3& BoxColliderComponent::GetExtents() {
	return boundingBox->Extents;
}
