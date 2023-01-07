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

#include "common.hpp"
#include "mesh.hpp"

namespace core
{
	struct BatchParams
	{
		size_t maxDataCount = 1000;
	};

	class Batch
	{
		friend class Renderer;

	public:
		Batch(const BatchParams& params, const ref<Material>& material);
		~Batch() = default;

		Batch(const Batch&) = default;
		Batch(Batch&&) = default;

		Batch& operator=(const Batch&) = default;
		Batch& operator=(Batch&&) = default;

		void add(const std::vector<MeshVertex>& vertices,
			const std::vector<uint16_t>& indices);
		void add(const ref<Mesh>& mesh);
		void flush();

		std::vector<ref<Mesh>> getBatchedMeshes() { return batchedMeshes; }

		static ref<Batch> create(const BatchParams& params,
			const ref<Material>& material);

	private:
		BatchParams params;
		ref<Material> material; 
		std::vector<MeshVertex> currBatchedVertices;
		std::vector<uint16_t> currBatchedIndices;
		std::vector<ref<Mesh>> batchedMeshes;
	};
}