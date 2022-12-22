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

namespace Core::Math
{
	enum AxisType
	{
		X, Y, Z
	};

	// Advanced Math
	Transform DecomposeMatrix(const glm::mat4& matrix);
	glm::mat4 ComposeMatrix(const Transform& transform);

	glm::mat4 MatrixFromXVector(glm::vec3 direction);
	glm::vec3 RotationFromXVector(glm::vec3 direction);

	// Simple Math
	// glm does not support this with floats so we need a custom function for this
	glm::vec3 Caret(glm::vec3 a, glm::vec3 b);

	// Utils
	bool InRange(float value, float min, float max);
}