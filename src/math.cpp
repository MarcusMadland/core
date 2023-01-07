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

#include "crpch.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "math.hpp"
#include "defines.hpp"
#include "renderer/camera.hpp"

namespace core::math
{
	Transform decomposeMatrix(const glm::mat4& matrix)
	{
		Transform result;
		glm::mat4 local(matrix);

		// Normalize the matrix
		if (glm::epsilonEqual(local[3][3], static_cast<float>(0),
			glm::epsilon<float>()))
		{
			return Transform();
		}

		// Extract position and remove translation from local matrix
		result.position = glm::vec3(local[3]);
		local[3] = glm::vec4(0, 0, 0, local[3].w);

		// Extract scale
		for (int i = 0; i < 3; i++)
			result.scale[i] = glm::length(glm::vec3(matrix[i]));

		// Extract rotation
		const glm::mat3 rotMatrix(
			glm::vec3(matrix[0]) / result.scale[0],
			glm::vec3(matrix[1]) / result.scale[1],
			glm::vec3(matrix[2]) / result.scale[2]);
		result.rotation = glm::quat(rotMatrix);

		return result;
	}

	glm::mat4 composeMatrix(const Transform& transform)
	{
		// Compose translation matrix by translating from position
		const glm::mat4 translation = glm::translate(glm::mat4(1.0f),
			transform.position);

		// Compose rotation matrix by converting the quaternion to a 4x4 matrix
		const glm::mat4 rotation = glm::toMat4(transform.rotation);

		// Compose scale matrix by scaling from scale
		const glm::mat4 scale = glm::scale(glm::mat4(1.0f),
			transform.scale);

		// Multiply all transformation matrices and return result
		return translation * rotation * scale;
	}

	glm::vec3 worldToScreenSpace(const glm::vec3& worldSpace, const ref<Camera>& camera)
	{
		constexpr glm::vec3 result =  glm::vec3();
		return result;
	}

	glm::vec3 screenToWorldSpace(const glm::vec2& screenSpace,
		const ref<Camera>& camera, const float& depth )
	{
		// Create a viewport from camera width and height
		const glm::vec4 viewport = { 0,0,camera->getParams().width,
			camera->getParams().height};

		// Un-project screenspace to world space with current viewport
		glm::vec3 result = glm::unProject({ screenSpace.x, screenSpace.y,
			1 }, camera->getViewMatrix(),
			camera->getProjectionMatrix(), viewport);

		// Normalize the new direction with a multiplied depth value
		result = glm::normalize(result - camera->getParams().position) * depth
			+ camera->getParams().position;

		return result;
	}

	glm::vec3 exp(const glm::vec3& a, const glm::vec3& b)
	{
		const glm::vec3 result = glm::vec3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
	
		return result;
	}

	glm::quat findLookAtRotation(const glm::vec3& start, const glm::vec3& target)
	{
		return rotationFromXVector(target - start);
	}

	glm::quat rotationFromXVector(const glm::vec3& direction)
	{
		glm::vec3 const newX = glm::normalize(direction);

		// try to use up if possible
		glm::vec3 const upVector = (glm::abs(newX.y) < (1.f - CORE_SMALL_NUMBER)) ? glm::vec3(0, 1.0f, 0.f) : glm::vec3(1.f, 0, 0.f);

		const glm::vec3 newY = glm::normalize(exp(upVector, newX));
		const glm::vec3 newZ = exp(newX, newY);

		const glm::quat result =
			glm::quat(glm::mat4(glm::mat3(newX, newY, newZ)));
		
		return result;
	}

	glm::quat toQuat(const float& pitch, const float& yaw, const float& roll)
	{
		const glm::quat result = glm::quat(
			glm::radians(glm::vec3(pitch, yaw, roll)));
		return result;
	}

	glm::quat toQuat(const glm::vec3& euler)
	{
		return toQuat(euler.x, euler.y, euler.z);
	}

	bool inRange(const float& value, const float& min, const float& max)
	{
		return value > min && value < max;
	}

	float interp(const float& current, const float& target,
		const float& deltaTime, const float& speed)
	{
		const float difference = target - current;
		const float move = deltaTime * speed;

		if (difference > deltaTime)
		{
			return current + move;
		}
		if (difference < -deltaTime)
		{
			return current - move;
		}

		return target;
	}
	glm::vec3 interp(const glm::vec3& current, const glm::vec3& target,
		const float& deltaTime, const float& speed)
	{
		const glm::vec3 result = glm::vec3(
			interp(current.x, target.x, deltaTime, speed),
			interp(current.y, target.y, deltaTime, speed),
			interp(current.z, target.z, deltaTime, speed));
		return result;
	}
}