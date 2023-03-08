#include "pch.h"
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
	
}

void BoxColliderComponent::Draw() {

}

void BoxColliderComponent::Reload() {

}

void BoxColliderComponent::DestroyResources() {

}

bool BoxColliderComponent::Intersects(DirectX::SimpleMath::Vector3 translation) {
	translation.Normalize();

	for (auto& gameObject : Game::Instance()->gameObjects) {
		std::shared_ptr<GameObject> noCollisionGameObject = nullptr;
		auto it = std::find(noCollisionGameObjects.begin(), noCollisionGameObjects.end(), gameObject);

		if (it != noCollisionGameObjects.end())
			noCollisionGameObject = *it;

		if (gameObject != owner && gameObject != noCollisionGameObject) {
			std::optional<BoxColliderComponent> secondBox = gameObject->GetComponent<BoxColliderComponent>();

			if (secondBox.has_value()) {
				DirectX::BoundingBox boundingBoxWithOffset(boundingBox->Center, boundingBox->Extents);
				boundingBoxWithOffset.Center.x += translation.x / 100;
				boundingBoxWithOffset.Center.y += translation.y / 100;

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

bool BoxColliderComponent::Intersects(DirectX::SimpleMath::Vector3 direction, float outDistance) {
	direction.Normalize();
	DirectX::SimpleMath::Vector3 rayPosition(PointOnBounds(direction));
	DirectX::SimpleMath::Ray ray(rayPosition, direction);
	
	for (auto& gameObject : Game::Instance()->gameObjects) {
		std::shared_ptr<GameObject> noCollisionGameObject = nullptr;
		auto it = std::find(noCollisionGameObjects.begin(), noCollisionGameObjects.end(), gameObject);

		if (it != noCollisionGameObjects.end())
			noCollisionGameObject = *it;

		if (gameObject != owner && gameObject != noCollisionGameObject) {
			std::optional<BoxColliderComponent> secondBox = gameObject->GetComponent<BoxColliderComponent>();

			if (secondBox.has_value()) {
				if (ray.Intersects(*secondBox->boundingBox, outDistance)) {
					return true;
				}
			}
		}
	}

	outDistance = -1.0f;
	return false;
}

DirectX::SimpleMath::Vector3 BoxColliderComponent::PointOnBounds(DirectX::SimpleMath::Vector3 direction) {
	direction.Normalize();
	float y = boundingBox->Extents.x * direction.y / direction.x;

	if (abs(y) < boundingBox->Extents.y)
		return DirectX::SimpleMath::Vector3(boundingBox->Extents.x, y, 0.0f);

	return DirectX::SimpleMath::Vector3(boundingBox->Extents.y * direction.x / direction.y, boundingBox->Extents.y, 0.0f);
}

DirectX::XMFLOAT3& BoxColliderComponent::GetCenter() {
	return boundingBox->Center;
}

DirectX::XMFLOAT3& BoxColliderComponent::GetExtents() {
	return boundingBox->Extents;
}
