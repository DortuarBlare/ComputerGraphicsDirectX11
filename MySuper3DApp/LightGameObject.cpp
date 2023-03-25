#include "pch.h"
#include "LightGameObject.h"
#include "TransformComponent.h"

LightGameObject::LightGameObject() {
    /*mesh = std::make_shared<MeshRenderComponent>(
        "Models/Arrow.fbx",
        L"Textures/Arrow.png"
    );*/
}

void LightGameObject::Initialize() {
    //AddComponent(mesh);

    GameObject::Initialize();
}

Matrix LightGameObject::GetViewMatrix() {
    return transform->GetView();
}

Matrix LightGameObject::GetProjectionMatrix() {
    return
        Matrix::CreateOrthographic(
            static_cast<float>(Game::Instance()->renderSystem->display->GetClientWidth()),
            static_cast<float>(Game::Instance()->renderSystem->display->GetClientHeight()),
            0.1f,
            1000.0f
        );
}
