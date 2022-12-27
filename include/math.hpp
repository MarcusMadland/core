/*
 * Copyright 2022 Marcus Madland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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