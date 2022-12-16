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

#include "math/transform.hpp"

namespace Core
{
	Transform::Transform(const glm::vec3 position, const glm::vec3 orientation /* = glm::vec3(0.0f) */, 
		const glm::vec3 scale /* = glm::vec3(1.0f) */)
		: position(position)
		, orientation(orientation)
		, scale(scale)
	{
	}

	bool operator!=(const Transform& a, const Transform& b)
	{
		const bool pos = a.position != b.position;
		const bool ori = a.orientation != b.orientation;
		const bool scale = a.scale != b.scale;

		return (pos || ori || scale);
	}

	bool operator==(const Transform& a, const Transform& b)
	{
		const bool pos = a.position == b.position;
		const bool ori = a.orientation == b.orientation;
		const bool scale = a.scale == b.scale;

		return (pos && ori && scale);
	}

	Transform operator*(const Transform& a, const Transform& b)
	{
		return Transform(a.position * b.position, a.orientation * b.orientation, a.scale * b.scale);
	}

	Transform operator+(const Transform& a, const Transform& b)
	{
		return Transform(a.position + b.position, a.orientation + b.orientation, a.scale + b.scale);
	}
}