

#pragma once

#include "math/transform.hpp"
#include "common.hpp"

class Camera;

namespace Core::Math
{
	// Advanced Math
	Transform DecomposeMatrix(const glm::mat4& matrix);
	glm::mat4 ComposeMatrix(const Transform& transform);

	glm::vec3 WorldToScreenSpace(const glm::vec3& worldSpace, const Ref<Camera>& camera);
	glm::vec3 ScreenToWorldSpace(const glm::vec2& screenSpace, const Ref<Camera>& camera, const float& depth = 2.0f); // from bottom left corner

	glm::quat FindLookAtRotation(const glm::vec3& start, const glm::vec3& target);
	glm::quat RotationFromXVector(const glm::vec3& direction);

	// Simple Math
	glm::vec3 Caret(const glm::vec3& a, const glm::vec3& b);// glm does not support this with floats so we need a custom function for this
	float Square(const float& a);

	// Conversions
	glm::quat ToQuat(const float& pitch, const float& yaw, const float& roll);
	glm::quat ToQuat(const glm::vec3& euler);

	// Utils
	bool InRange(float value, float min, float max);
	float Interp(float current, float target, float deltaTime, float speed);
	glm::vec3 Interp(glm::vec3 current, glm::vec3 target, float deltaTime, float speed);
}