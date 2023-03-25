#pragma once
#include "GameObject.h"
//#include "MeshRenderComponent.h"

using namespace DirectX::SimpleMath;

class LightGameObject : public GameObject {
private:
	//std::shared_ptr<MeshRenderComponent> mesh;

public:
	LightGameObject();

	void Initialize() override;

	Matrix GetViewMatrix();
	Matrix GetProjectionMatrix();
};
