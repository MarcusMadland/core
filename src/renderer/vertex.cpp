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

#include "renderer/vertex.hpp"

namespace core
{
	PrimitiveVertex::PrimitiveVertex()
		: position(glm::vec3(0.0f))
	    , color(0x0f)
		, normal(glm::vec3(0.0f))
	{}

	MeshVertex::MeshVertex()
		: position(glm::vec3(0.0f))
		, normal(glm::vec3(0.0f))
		, tangent(glm::vec3(0.0f))
		, biNormal(glm::vec3(0.0f))
		, texCoord(glm::vec2(0.0f))
	{}
}
