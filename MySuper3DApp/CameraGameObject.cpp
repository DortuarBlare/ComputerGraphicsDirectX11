#include "pch.h"
#include "CameraGameObject.h"
#include "TransformComponent.h"

void CameraGameObject::Initialize() {
    GameObject::Initialize();
    Game::instance->inputDevice->MouseMove.AddRaw(this, &CameraGameObject::MouseEventHandler);

    velocity = 5.0f;
    orbitOffset = *transform->localPosition;
}

void CameraGameObject::Update() {
    GameObject::Update();

    Matrix rotationMatrix = Matrix::CreateFromYawPitchRoll(yaw, pitch, 0);

    Vector3 forward = Vector3::Transform(Vector3::Forward, rotationMatrix);
    Vector3 right = Vector3::Transform(Vector3::Right, rotationMatrix);

    if (Game::instance->inputDevice->IsKeyDown(Keys::P))
        perspective = true;
    if (Game::instance->inputDevice->IsKeyDown(Keys::O))
        perspective = false;

    if (Game::instance->inputDevice->IsKeyDown(Keys::A)) {
        *transform->localPosition -= velocity * Game::instance->deltaTime * right;
        Detach();
    }
    if (Game::instance->inputDevice->IsKeyDown(Keys::D)) {
        *transform->localPosition += velocity * Game::instance->deltaTime * right;
        Detach();
    }
    if (Game::instance->inputDevice->IsKeyDown(Keys::W)) {
        *transform->localPosition += velocity * Game::instance->deltaTime * forward;
        Detach();
    }
    if (Game::instance->inputDevice->IsKeyDown(Keys::S)) {
        *transform->localPosition -= velocity * Game::instance->deltaTime * forward;
        Detach();
    }

    if (Game::instance->inputDevice->IsKeyDown(Keys::Space)) {
        *transform->localPosition += velocity * Game::instance->deltaTime * Vector3::Up;
        Detach();
    }
    if (Game::instance->inputDevice->IsKeyDown(Keys::LeftShift)) {
        *transform->localPosition -= velocity * Game::instance->deltaTime * Vector3::Up;
        Detach();
    }

    if (orbitMode && transform->parent) {
        *transform->localPosition = *transform->parent->localPosition + orbitOffset;
        target = *transform->parent->localPosition;
    }
    else {
        target = *transform->localPosition +
            Vector3::Transform(
                Vector3::Forward,
                Matrix::CreateFromYawPitchRoll(yaw, pitch, 0)
            );
        up = Vector3::Transform(
            Vector3::Up,
            Matrix::CreateFromYawPitchRoll(yaw, pitch, 0)
        );
    }

    viewMatrix = CreateViewMatrix();

    if (perspective)
        projectionMatrix = CreatePerspectiveMatrix();
    else
        projectionMatrix = CreateOrthographicMatrix();

    /*std::cout <<
        "Camera position: " <<
        transform->localPosition->x << ' ' <<
        transform->localPosition->y << ' ' <<
        transform->localPosition->z <<
        std::endl;*/
}

void CameraGameObject::FixedUpdate() {
    GameObject::FixedUpdate();
}


void CameraGameObject::AttachTo(std::shared_ptr<TransformComponent> transform) {
    orbitMode = true;
    this->transform->parent = transform;

    orbitOffset = 10.0f *
        Vector3::Transform(
            Vector3::Forward + Vector3::Up,
            Matrix::CreateFromYawPitchRoll(yaw, pitch, 0)
        );

    up = Vector3::Up;
}

void CameraGameObject::Detach() {
    if (transform->parent) {
        orbitMode = false;
        transform->parent = nullptr;
    }
}


Matrix CameraGameObject::GetCameraMatrix() {
    return viewMatrix * projectionMatrix;
}

Matrix CameraGameObject::CreateViewMatrix() {
    return Matrix::CreateLookAt(*transform->localPosition, target, up);
}

Matrix CameraGameObject::CreatePerspectiveMatrix() {
    return
        Matrix::CreatePerspectiveFieldOfView(
            fov,
            static_cast<float>(Game::instance->GetDisplay()->GetClientWidth()) / Game::instance->GetDisplay()->GetClientHeight(),
            nearPlane,
            farPlane
        );
}

Matrix CameraGameObject::CreateOrthographicMatrix() {
    return
        Matrix::CreateOrthographic(
            Game::instance->GetDisplay()->GetClientWidth() / 50,
            Game::instance->GetDisplay()->GetClientHeight() / 50,
            nearPlane,
            farPlane
        );
}


void CameraGameObject::MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData) {
    /**transform->localRotation *=
        Quaternion::CreateFromYawPitchRoll(
            -mouseData.Offset.x * cameraRotationSpeed,
            -mouseData.Offset.y * cameraRotationSpeed,
            0
        );*/

    /**transform->localRotation =
        Quaternion::CreateFromAxisAngle(Vector3::Up, -mouseData.Offset.x * cameraRotationSpeed) *
        Quaternion::CreateFromAxisAngle(Vector3::Transform(
            Vector3::Right, Matrix::CreateFromQuaternion(*transform->localRotation)),
            -mouseData.Offset.y * cameraRotationSpeed
        ) *
        *transform->localRotation;*/

    if (!orbitMode) {
        yaw += -mouseData.Offset.x * rotationSpeed;
        pitch += -mouseData.Offset.y * rotationSpeed;

        if (pitch > DirectX::XM_PIDIV2 - 0.01)
            pitch = DirectX::XM_PIDIV2 - 0.01;
        if (pitch < -DirectX::XM_PIDIV2 + 0.01)
            pitch = -DirectX::XM_PIDIV2 + 0.01;

        if (velocity + mouseData.WheelDelta / 10 > 0)
            velocity += mouseData.WheelDelta / 10;
    }
    else {
        Vector3 right = orbitOffset.Cross(up);
        Quaternion quaternionFromMouseInput =
            Quaternion::CreateFromAxisAngle(up, -0.005f * mouseData.Offset.x) *
            Quaternion::CreateFromAxisAngle(right, 0.005f * mouseData.Offset.y);
        orbitOffset = Vector3::Transform(orbitOffset, Matrix::CreateFromQuaternion(quaternionFromMouseInput));
        up = Vector3::Transform(up, Matrix::CreateFromQuaternion(quaternionFromMouseInput));

        // Changing the distance to the planet
        orbitOffset *= 1 - orbitApproximationSpeed * mouseData.WheelDelta;
    }
}
