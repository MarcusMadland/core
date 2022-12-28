#pragma once

#include "common.hpp"

#include "primitive/mesh.hpp"

namespace Core
{
	struct BatchParams
	{
		const size_t maxTriangleCount = 1000;
		const size_t maxVertexCount = maxTriangleCount * 4;
		const size_t maxIndexCount = maxTriangleCount * 6;
		const size_t maxTextures = 8;
	};

	class Batch
	{
	public:
		Batch(const BatchParams& params);
		~Batch();

		std::vector<Ref<Mesh>> GetBatchedMeshes() { return batchedMeshes; }

		static Ref<Batch> Create(const BatchParams& params);

	private:
		std::vector<Ref<Mesh>> batchedMeshes;
	};
}