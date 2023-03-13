#pragma once
#include "RenderComponent.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

class MeshRenderComponent : public RenderComponent {
public:
	std::string modelFileName;
	float importScale = 1.0f;
	Vector3 importTranslation = Vector3::Zero;

	MeshRenderComponent() = delete;
	MeshRenderComponent(std::string modelFileName, LPCWSTR textureFileName);
	MeshRenderComponent(std::string modelFileName, LPCWSTR textureFileName, float importScale);
	MeshRenderComponent(std::string modelFileName, LPCWSTR textureFileName, float importScale, Vector3 importTranslation);

	void Initialize() override;
	void ProcessNode(aiNode* node, const aiScene* scene);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
};
