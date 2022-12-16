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

#include "math.hpp"
#include "debug/logger.hpp"

namespace Core::Math
{
	Transform DecomposeMatrix(const glm::mat4& transform)
	{
		glm::vec3 rotation, scale;
		glm::mat4 localMatrix(transform);

		// Normalize the matrix
		if (glm::epsilonEqual(localMatrix[3][3], static_cast<float>(0),
			glm::epsilon<float>()))
			return Transform();

		// First, isolate perspective.  This is the messiest
		if (
			glm::epsilonNotEqual(localMatrix[0][3], static_cast<float>(0), glm::epsilon<float>()) ||
			glm::epsilonNotEqual(localMatrix[1][3], static_cast<float>(0), glm::epsilon<float>()) ||
			glm::epsilonNotEqual(localMatrix[2][3], static_cast<float>(0), glm::epsilon<float>()))
		{
			// Clear the perspective partition
			localMatrix[0][3] = localMatrix[1][3] = localMatrix[2][3] = static_cast<float>(0);
			localMatrix[3][3] = static_cast<float>(1);
		}

		// Next take care of translation (easy)
		const auto translation = glm::vec3(localMatrix[3]);
		localMatrix[3] = glm::vec4(0, 0, 0, localMatrix[3].w);

		glm::vec3 row[3];

		// Now get scale and shear
		for (uint8_t i = 0; i < 3; ++i)
			for (uint8_t j = 0; j < 3; ++j)
				row[i][j] = localMatrix[i][j];
		
		// Compute X scale factor and normalize first row
		scale.x = length(row[0]);
		row[0] = glm::detail::scale(row[0], static_cast<float>(1));
		scale.y = length(row[1]);
		row[1] = glm::detail::scale(row[1], static_cast<float>(1));
		scale.z = length(row[2]);
		row[2] = glm::detail::scale(row[2], static_cast<float>(1));

		// Extract euler rotation and convert to degrees
		rotation.x = glm::degrees(atan2f(row[1][2], row[2][2]));
		rotation.y = glm::degrees(atan2f(-row[0][2], sqrtf(row[1][2] * row[1][2] + row[2][2] * row[2][2])));
		rotation.z = glm::degrees(atan2f(row[0][1], row[0][0]));
	

		return Transform(translation, rotation, scale);
	}
	glm::mat4 ComposeMatrix(const Transform& transform)
	{
		// Compose translation matrix by translating from vec3
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), transform.position);

		// Compose rotation matrix by converting the euler vec3 to radians and then 
		// over to quaternion. From quat we can easily convert to a rotation matrix
		glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(transform.orientation)));
	
		// Compose scale matrix by scaling from vec3
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.scale);

		// Multiply all transformation matrices and return result
		return translation * rotation * scale;
	}
	glm::vec3 OrientationFromVectorXZ(glm::vec3 direction)
	{
		glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

		// Final rotation matrix we convert to euler on return
		glm::mat4 rotation= glm::mat4(1.0f);

		// As long as the direction and vector we rotate against is not the same
		// either negative or positive we calculate the perpendicular
		if (upVector != glm::abs(direction))
		{
			glm::vec3 perp = glm::cross(upVector, direction);
			float angle = glm::angle(direction, upVector);
			rotation = glm::rotate(angle, perp);
		}

		// Since rotation is rotated from up vector the rotation will stay positive 
		// even tho it's negative. We solve this by rotating it 180 degrees around 
		// either x or z (in this case x) 
		else if(direction.y < 0.0f)
		{	
			rotation = glm::rotate(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		}

		// Decompose the matrix so we get a transform struct. Then get the euler orientation
		// and return it
		return DecomposeMatrix(rotation).orientation;
	}
	float Interp(float current, float target, float interpSpeed, float deltaTime)
	{
		const float dist = target - current;

		if (glm::sqrt(dist) < 1.e-8f)
		{
			return target;
		}

		const float step = interpSpeed * deltaTime;
		return current + glm::clamp(dist, -step, step);
	}
	bool InRange(float value, float min, float max)
	{
		return value > min && value < max;
	}

}