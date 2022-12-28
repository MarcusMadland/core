#pragma once

#include "common.hpp"

#include "primitive/mesh.hpp"

namespace Core
{
	struct BatchParams
	{
		
	};

	class Batch
	{
	public:
		Batch(const BatchParams& params, Ref<Material> material);
		~Batch();

		void Add(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices);
		void Add(Ref<Mesh> mesh);
		void Flush();

		std::vector<Ref<Mesh>> GetBatchedMeshes() { return batchedMeshes; }

		static Ref<Batch> Create(const BatchParams& params, Ref<Material> material);

	private:
		Ref<Material> material; //temp
		std::vector<MeshVertex> currBatchedVertices;
		std::vector<uint16_t> currBatchedIndices;

		std::vector<Ref<Mesh>> batchedMeshes;
	};
}