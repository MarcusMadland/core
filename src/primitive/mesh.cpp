

#include "crpch.hpp"

#include <bgfx/bgfx.h>

#include "primitive/mesh.hpp"
#include "graphics/vertex_array.hpp"
#include "primitive/vertex.hpp"

namespace Core
{
	Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices, Ref<Material> material)
		: vertices(vertices), indices(indices), material(material)
	{
		// Vertex Layout following MeshVertex struct
		bgfx::VertexLayout layout;
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Tangent, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord7, 4, bgfx::AttribType::Float)
			.end();

		// Shape 
		bgfx::VertexBufferHandle cubeVbh = bgfx::createVertexBuffer(bgfx::makeRef(Mesh::vertices.data(), Mesh::vertices.size() * sizeof(MeshVertex)), layout);
		bgfx::IndexBufferHandle cubeIbh = bgfx::createIndexBuffer(bgfx::makeRef(Mesh::indices.data(), Mesh::indices.size() * sizeof(uint16_t)));
		vao = VertexArray::Create(cubeVbh, cubeIbh);
	}

	Ref<Mesh> Mesh::Create(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices, Ref<Material> material)
	{
		return MakeRef<Mesh>(vertices, indices, material);
	}
}