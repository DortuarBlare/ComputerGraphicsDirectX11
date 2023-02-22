#include "SquareRenderComponent.h"

SquareRenderComponent::SquareRenderComponent() : RenderComponent() {
	indeces.insert(indeces.end(), { 0, 1, 2, 1, 0, 3 });
}

SquareRenderComponent::SquareRenderComponent(D3D11_FILL_MODE fillMode, std::shared_ptr<DirectX::SimpleMath::Vector4> renderOffset) :
	RenderComponent(fillMode, renderOffset) {
	indeces.insert(indeces.end(), { 0, 1, 2, 1, 0, 3 });
}
