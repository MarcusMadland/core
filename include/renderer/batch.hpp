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
		Batch(const BatchParams& params, ref<Material> material);
		~Batch();

		void add(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices);
		void add(ref<Mesh> mesh);
		void flush();

		std::vector<ref<Mesh>> getBatchedMeshes() { return batchedMeshes; }

		static ref<Batch> create(const BatchParams& params, ref<Material> material);

	private:
		BatchParams params;
		ref<Material> material; //temp
		std::vector<MeshVertex> currBatchedVertices;
		std::vector<uint16_t> currBatchedIndices;

		std::vector<ref<Mesh>> batchedMeshes;
	};
}