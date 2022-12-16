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

#include "transform.hpp"

namespace Core::Math
{
	/*
	 * Decomposes a 4x4 matrix to a transform
	 * 
	 * @param transform The matrix that should be decomposed
	 * @return The final constructed transform
	 */
	Transform DecomposeMatrix(const glm::mat4& transform);

	/*
	 * Composes a 4x4 matrix from a transform
	 *
	 * @param transform The transform that the matrix should be composed from
	 * @return The final constructed matrix
	 */
	glm::mat4 ComposeMatrix(const Transform& transform);

	/*
	 * Constructs a euler rotation from a normalized direction
	 *
	 * @param direction The direction the rotation should be constructed from,
	 * must be normalized
	 * @return Final euler vector made from the orientation of direction
	 */
	glm::vec3 OrientationFromVectorXZ(glm::vec3 direction);
	
	/*
	 * Checks if the value is greater than min and less than max
	 *
	 * @param value The value to check against
	 * @param min The lowest the value can be for the return to be true
	 * @param max The highest the value can be for the return to be true
	 * @return True if value is between min and max, False otherwise
	 */
	bool InRange(float value, float min, float max);
	
	// @todo Take a look at linear and non linear lerp and make new functions
	float Interp(float current, float target, float interpSpeed, float deltaTime);
}