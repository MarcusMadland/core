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
 * @todo Make this class
 */

#pragma once

#include "common.hpp"

#include "math/transform.hpp"
#include "primitive/vertex.hpp"
#include "graphics/vertex_array.hpp"

namespace Core
{
	class Mesh
	{
	public:
		Mesh(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices);
		
		static Ref<Mesh> Create(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices);
		
		[[nodiscard]] const Transform& GetTransform() const { return transform; }
		[[nodiscard]] const Ref<VertexArray> GetVertexArray() const { return vao; }

	private:
		Transform transform;

		std::vector<MeshVertex> vertices;
		std::vector<uint16_t> indices;
		
		Ref<VertexArray> vao;
	};

	
}