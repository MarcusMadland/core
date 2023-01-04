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

/*
 * Collection of commonly used maths not present in the GLM library
 */
#pragma once

#include "common.hpp"
#include "math/transform.hpp"

/*
 * Forward Declarations
 */
class Camera;

namespace core
{
	namespace math
	{
		/*
		 * Advanced Maths
		 */

		/*!
		 * Decomposes a 4x4 matrix into a Transform structure.
		 *
		 * @param[in] matrix A 4x4 matrix to decompose from
		 * 
		 * @return A three component transform for Position, Rotation and Scale
		 */
		Transform decomposeMatrix(const glm::mat4& matrix);

		/*!
		 * Composes a 4x4 matrix from a Transform structure.
		 *
		 * @param[in] transform A transform struct to construct from
		 * 
		 * @return A 4x4 transformation matrix 
		 */
		glm::mat4 composeMatrix(const Transform& transform);

		/*!
		 * @todo Yet to be implemented
		 */
		glm::vec3 worldToScreenSpace(const glm::vec3& worldSpace,
			const ref<Camera>& camera);

		/*!
		 * Tries to convert from screen space to world space.
		 * 
		 * @remark The returned value starts from the bottom left corner in
		 * pixels
		 *
		 * @param[in] screenSpace A two dimensional vector in screen space to
		 * convert from
		 * @param[in] camera The camera to read the returned screenspace from
		 * @param[in] depth The depth that should be used in the returned value
		 * since screen space is two dimensional
		 * 
		 * @return Three dimensional vector in world space
		 */
		glm::vec3 screenToWorldSpace(const glm::vec2& screenSpace,
			const ref<Camera>& camera, const float& depth = 2.0f); 

		/*!
		 * Tries to find the rotation between two points
		 *
		 * @param[in] start The start position in world space (eye)
		 * @param[in] target The end position in world space (lookAt)
		 * 
		 * @return The quaternion rotation between two points
		 */
		glm::quat findLookAtRotation(const glm::vec3& start,
			const glm::vec3& target);

		/*!
		 * Tries to find the rotation from a directional vector's X axis
		 *
		 * @param[in] direction The direction to convert from
		 * 
		 * @return The quaternion rotation from direction
		 */
		glm::quat rotationFromXVector(const glm::vec3& direction);

		/*
		 * Simple Maths
		 */

		/*!
		 * @todo Yet to be documented
		 */
		glm::vec3 exp(const glm::vec3& a, const glm::vec3& b);
		
		/*
		 * Conversions
		 */

		/*!
		 * Converts from euler rotation to a quaternion rotation
		 *
		 * @param[in] pitch Pitch rotation (x)
		 * @param[in] yaw Pitch rotation (y)
		 * @param[in] roll Pitch rotation (z)
		 *
		 * @return The quaternion rotation from euler
		 */
		glm::quat toQuat(const float& pitch, const float& yaw, const float& roll);

		/*!
		 * Converts from euler rotation to a quaternion rotation
		 *
		 * @remark Euler rotation should be in this order, Pitch, Yaw, Roll
		 *
		 * @param[in] euler Three dimensional vector in euler degrees.
		 *
		 * @return The quaternion rotation from euler
		 */
		glm::quat toQuat(const glm::vec3& euler);

		/*
		 * Utilities
		 */

		/*!
		 * Checks if input value is between min and max
		 *
		 * @param[in] value The value to check
		 * @param[in] min The minimum the value can be
		 * @param[in] max The maximum the value can be
		 *
		 * @return True if the value is higher than min and lower than max
		 */
		bool inRange(const float& value, const float& min, const float& max);

		/*!
		 * Linear Interpolates from current to target
		 *
		 * @param[in] current The current value to interpolate from. Should be
		 * the same value that is set upon return
		 * @param[in] target The desired value current should be
		 * @param[in] deltaTime The Delta Time of current frame
		 * @param[in] speed The speed of the interpolation. Higher = Faster
		 */
		float interp(const float& current, const float& target,
			const float& deltaTime, const float& speed);

		/*!
		 * Linear Interpolates from current to target
		 *
		 * @param[in] current The current value to interpolate from. Should be
		 * the same value that is set upon return
		 * @param[in] target The desired value current should be
		 * @param[in] deltaTime The Delta Time of current frame
		 * @param[in] speed The speed of the interpolation. Higher = Faster
		 */
		glm::vec3 interp(const glm::vec3& current, const glm::vec3& target,
			const float& deltaTime, const float& speed);
	}
}
