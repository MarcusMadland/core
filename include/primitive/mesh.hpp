



#pragma once

#include "common.hpp"

#include "math/transform.hpp"
#include "primitive/vertex.hpp"
#include "graphics/vertex_array.hpp"
#include "graphics/material.hpp"

namespace Core
{
	class Mesh
	{
	public:
		Mesh(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices, Ref<Material> material);
		
		static Ref<Mesh> Create(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices, Ref<Material> material);
		
		[[nodiscard]] const Transform& GetTransform() const { return transform; }
		[[nodiscard]] const Ref<Material> GetMaterial() const { return material; }
		[[nodiscard]] const Ref<VertexArray> GetVertexArray() const { return vao; }

		const std::vector<MeshVertex> GetVertices() const { return vertices; }
		const std::vector<uint16_t> GetIndices() const { return indices; }

	private:
		Ref<Material> material;
		Transform transform;

		std::vector<MeshVertex> vertices;
		std::vector<uint16_t> indices;
		
		Ref<VertexArray> vao;
	};

	
}