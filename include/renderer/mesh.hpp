



#pragma once

#include "common.hpp"

#include "math/transform.hpp"
#include "vertex.hpp"
#include "buffers.hpp"
#include "material.hpp"

namespace core
{
	class Mesh
	{
	public:
		Mesh(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices, ref<Material> material);
		
		static ref<Mesh> create(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices, ref<Material> material);
		
		[[nodiscard]] const Transform& getTransform() const { return transform; }
		[[nodiscard]] const ref<Material> getMaterial() const { return material; }
		[[nodiscard]] const ref<VertexArray> getVertexArray() const { return vao; }

		const std::vector<MeshVertex> getVertices() const { return vertices; }
		const std::vector<uint16_t> getIndices() const { return indices; }

	private:
		ref<Material> material;
		Transform transform;

		std::vector<MeshVertex> vertices;
		std::vector<uint16_t> indices;
		
		ref<VertexArray> vao;
	};

	
}