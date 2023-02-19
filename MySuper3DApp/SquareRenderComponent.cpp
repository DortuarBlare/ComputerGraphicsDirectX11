#include "SquareRenderComponent.h"

SquareRenderComponent::SquareRenderComponent() : TriangleRenderComponent() {
	indeces.insert(indeces.end(), { 1, 0, 3 });
}

SquareRenderComponent::SquareRenderComponent(std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset) :
	TriangleRenderComponent(renderOffset) {
	indeces.insert(indeces.end(), { 1, 0, 3 });
}
