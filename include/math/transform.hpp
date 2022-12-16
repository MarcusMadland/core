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

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Core
{
	/*
	 * Transform holds a readable version of the transformation matrix
	 *
	 * position The position in world space
	 * orientation Euler rotation in degrees, x = yaw, y = pitch, z = roll
	 * scale Scale / Size in all three axis
	 */
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 orientation; 
		glm::vec3 scale;

		explicit Transform(glm::vec3 position = glm::vec3(0.0f), glm::vec3 orientation = glm::vec3(0.0f),
			glm::vec3 scale = glm::vec3(1.0f));
		
		friend bool operator!= (const Transform& a, const Transform& b);
		friend bool operator== (const Transform& a, const Transform& b);
		friend Transform operator* (const Transform& a, const Transform& b);
		friend Transform operator+ (const Transform& a, const Transform& b);
	};
}