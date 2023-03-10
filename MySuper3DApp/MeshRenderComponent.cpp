#include "pch.h"
#include "MeshRenderComponent.h"

MeshRenderComponent::MeshRenderComponent(std::string modelFileName, LPCWSTR textureFileName)
	: RenderComponent(textureFileName, D3D11_FILL_SOLID) {
	this->modelFileName = modelFileName;
}

MeshRenderComponent::MeshRenderComponent(std::string modelFileName, LPCWSTR textureFileName, float importScale)
	: RenderComponent(textureFileName, D3D11_FILL_SOLID) {
	this->modelFileName = modelFileName;
	this->importScale = importScale;
}

void MeshRenderComponent::Initialize() {
	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(modelFileName, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	if (!pScene)
		return;

	ProcessNode(pScene->mRootNode, pScene);

	RenderComponent::Initialize();
}

void MeshRenderComponent::ProcessNode(aiNode* node, const aiScene* scene) {
	for (UINT i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	for (UINT i = 0; i < node->mNumChildren; i++) 
		ProcessNode(node->mChildren[i], scene);
}

void MeshRenderComponent::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
	for (UINT i = 0; i < mesh->mNumVertices; i++) {
		XMFLOAT4 textureCoordinate = {};

		if (mesh->mTextureCoords[0]) {
			textureCoordinate.x = (float)mesh->mTextureCoords[0][i].x;
			textureCoordinate.y = (float)mesh->mTextureCoords[0][i].y;
		}
		
		points.push_back(
			{ 
				mesh->mVertices[i].x * importScale,
				mesh->mVertices[i].y * importScale,
				mesh->mVertices[i].z * importScale,
				1.0f 
			}
		);
		points.push_back(textureCoordinate);
	}

	//Get indices
	for (UINT i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indexes.push_back(face.mIndices[j]);
	}
}
