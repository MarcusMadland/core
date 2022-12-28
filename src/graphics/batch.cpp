#include "crpch.hpp"

#include "graphics/batch.hpp"
#include "debug/logger.hpp"

namespace Core
{
	Batch::Batch(const BatchParams& params, Ref<Material> material)
		: material(material)
	{
		// @todo for dynamic
		//currBatchedVertices.reserve(8);
		//currBatchedIndices.reserve(12);
	}

	Batch::~Batch()
	{
	}

	void Batch::Add(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices)
	{
		// Indices
		for (uint32_t i = 0; i < indices.size(); i++)
		{
			currBatchedIndices.push_back(currBatchedVertices.size() + indices[i]);
		}

		// Vertices
		currBatchedVertices.insert(currBatchedVertices.end(), vertices.begin(), vertices.end());
	}

	void  Batch::Add(Ref<Mesh> mesh)
	{
		if (mesh->GetMaterial() != material)
		{
			Logger::LogWarn("Overwriting mesh material to batch material");
		}

		Add(mesh->GetVertices(), mesh->GetIndices());
	}

	void Batch::Flush()
	{
		Ref<Mesh> batchedMesh = Mesh::Create(currBatchedVertices, currBatchedIndices, material);
		batchedMeshes.push_back(batchedMesh);

		Logger::LogInfo("Flushed batch, with %u batches, %u vertices and %u indices", 
			batchedMeshes.size(), currBatchedVertices.size(), currBatchedIndices.size());
	}

	Ref<Batch> Batch::Create(const BatchParams& params, Ref<Material> material)
	{
		return MakeRef<Batch>(params, material);
	}
}