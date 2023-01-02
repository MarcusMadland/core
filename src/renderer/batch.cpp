#include "crpch.hpp"

#include "renderer/batch.hpp"
#include "debug/logger.hpp"

namespace core
{
	Batch::Batch(const BatchParams& params, ref<Material> material)
		: params(params), material(material)
	{
		// @todo for dynamic
		//currBatchedVertices.reserve(8);
		//currBatchedIndices.reserve(12);
	}

	Batch::~Batch()
	{
	}

	void Batch::add(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices)
	{
		const size_t dataCount = (vertices.size() + indices.size()) + (currBatchedVertices.size() + currBatchedIndices.size());
		if (dataCount > params.maxDataCount)
		{
			flush();
			add(vertices, indices);
		}

		// Indices
		for (uint32_t i = 0; i < indices.size(); i++)
		{
			currBatchedIndices.push_back(currBatchedVertices.size() + indices[i]);
		}

		// Vertices
		currBatchedVertices.insert(currBatchedVertices.end(), vertices.begin(), vertices.end());
	}

	void  Batch::add(ref<Mesh> mesh)
	{
		if (mesh->getMaterial() != material)
		{
			Logger::logWarn("Overwriting mesh material to batch material");
		}

		add(mesh->getVertices(), mesh->getIndices());
	}

	void Batch::flush()
	{
		ref<Mesh> batchedMesh = Mesh::create(currBatchedVertices, currBatchedIndices, material);
		batchedMeshes.push_back(batchedMesh);

		Logger::logInfo("Flushed batch, with %u batches, %u vertices and %u indices",
			batchedMeshes.size(), currBatchedVertices.size(), currBatchedIndices.size());

		currBatchedVertices.clear();
		currBatchedIndices.clear();
	}

	ref<Batch> Batch::create(const BatchParams& params, ref<Material> material)
	{
		return makeRef<Batch>(params, material);
	}
}