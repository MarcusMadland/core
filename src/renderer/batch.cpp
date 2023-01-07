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

#include "renderer/batch.hpp"
#include "debug/logger.hpp"

namespace core
{
	Batch::Batch(const BatchParams& params, const ref<Material>& material)
		: params(params), material(material)
	{
	}

	void Batch::add(const std::vector<MeshVertex>& vertices,
		const std::vector<uint16_t>& indices)
	{
		assert(vertices.size() > 0, "Vertices are empty");
		assert(indices.size() > 0, "Indices are empty");
		
		const size_t dataCount = (vertices.size() + indices.size()) +
			(currBatchedVertices.size() + currBatchedIndices.size());
		if (dataCount > params.maxDataCount)
		{
			flush();
			add(vertices, indices);
		}

		// Indices
		for (const uint16_t index : indices)
		{
			currBatchedIndices.push_back(
				static_cast<uint16_t>(currBatchedVertices.size()) + index);
		}

		// Vertices
		currBatchedVertices.insert(currBatchedVertices.end(),
			vertices.begin(), vertices.end());
	}

	void  Batch::add(const ref<Mesh>& mesh)
	{
		assert(mesh, "Mesh is invalid");
		
		if (mesh->getMaterial() != material)
		{
			Logger::logWarn("Overwriting mesh material to batch material");
		}

		add(mesh->getVertices(), mesh->getIndices());
	}

	void Batch::flush()
	{
		const ref<Mesh> batchedMesh = Mesh::create(currBatchedVertices,
			currBatchedIndices, material);
		assert(batchedMesh, "Mesh is invalid");
		batchedMeshes.push_back(batchedMesh);

		Logger::logInfo("Flushed batch, with %u batches, %u vertices and %u indices",
			batchedMeshes.size(), currBatchedVertices.size(),
			currBatchedIndices.size());

		currBatchedVertices.clear();
		currBatchedIndices.clear();
	}

	ref<Batch> Batch::create(const BatchParams& params,
		const ref<Material>& material)
	{
		return makeRef<Batch>(params, material);
	}
}