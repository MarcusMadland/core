#include "crpch.hpp"

#include "renderer/buffers.hpp"
#include "defines.hpp"

namespace core
{
	VertexBuffer::VertexBuffer(const BufferLayout& layout, const void* data,
		const uint32_t& size)
	{
		bgfx::VertexLayout bgfxLayout;
		bgfxLayout.begin();
		for (auto& element : layout.getElements())
		{
			bgfxLayout.add(attribToBgfx(element.attrib), element.num,
				attribTypeToBgfx(element.attribType));
		}
		bgfxLayout.end();

		handle = bgfx::createVertexBuffer(bgfx::makeRef(data, size), bgfxLayout);
		ASSERT(bgfx::isValid(handle), "Created vertex buffer handle is invalid");
	}

	VertexBuffer::~VertexBuffer()
	{
		bgfx::destroy(handle);
	}

	ref<VertexBuffer> VertexBuffer::create(const BufferLayout& layout, const void* data,
		const uint32_t& size)
	{
		return makeRef<VertexBuffer>(layout, data, size);
	}

	bgfx::Attrib::Enum VertexBuffer::attribToBgfx(const Attrib& attrib)
	{
		switch (attrib)
		{
		case core::Attrib::Position:
			return bgfx::Attrib::Position;

		case core::Attrib::Normal:
			return bgfx::Attrib::Normal;
			
		case core::Attrib::Tangent:
			return bgfx::Attrib::Tangent;
			
		case core::Attrib::Bitangent:
			return bgfx::Attrib::Bitangent;
			
		case core::Attrib::Color0:
			return bgfx::Attrib::Color0;
			
		case core::Attrib::Color1:
			return bgfx::Attrib::Color1;
			
		case core::Attrib::Color2:
			return bgfx::Attrib::Color2;
			
		case core::Attrib::Color3:
			return bgfx::Attrib::Color3;
			
		case core::Attrib::Indices:
			return bgfx::Attrib::Indices;
			
		case core::Attrib::Weight:
			return bgfx::Attrib::Weight;
			
		case core::Attrib::TexCoord0:
			return bgfx::Attrib::TexCoord0;
			
		case core::Attrib::TexCoord1:
			return bgfx::Attrib::TexCoord1;
			
		case core::Attrib::TexCoord2:
			return bgfx::Attrib::TexCoord2;
			
		case core::Attrib::TexCoord3:
			return bgfx::Attrib::TexCoord3;
			
		case core::Attrib::TexCoord4:
			return bgfx::Attrib::TexCoord4;
			
		case core::Attrib::TexCoord5:
			return bgfx::Attrib::TexCoord5;
			
		case core::Attrib::TexCoord6:
			return bgfx::Attrib::TexCoord6;
			
		case core::Attrib::TexCoord7:
			return bgfx::Attrib::TexCoord7;
			
		default:
			return bgfx::Attrib::Position;
		}
	}

	bgfx::AttribType::Enum VertexBuffer::attribTypeToBgfx(const AttribType& attribType)
	{
		switch (attribType)
		{
		case core::AttribType::Uint8:
			return bgfx::AttribType::Uint8;

		case core::AttribType::Uint10:
			return bgfx::AttribType::Uint10;

		case core::AttribType::Int16:
			return bgfx::AttribType::Int16;

		case core::AttribType::Half:
			return bgfx::AttribType::Half;

		case core::AttribType::Float:
			return bgfx::AttribType::Float;

		default:
			return bgfx::AttribType::Float;
		}
	}

	IndexBuffer::IndexBuffer(const void* data, const uint32_t& size)
	{
		handle = bgfx::createIndexBuffer(bgfx::makeRef(data, size));
		ASSERT(bgfx::isValid(handle), "Created index buffer handle is invalid");
	}

	IndexBuffer::~IndexBuffer()
	{
		bgfx::destroy(handle);
	}

	ref<IndexBuffer> IndexBuffer::create(const void* data, const uint32_t& size)
	{
		return makeRef<IndexBuffer>(data, size);
	}

	VertexArray::VertexArray(const ref<VertexBuffer>& vertexBuffer,
		const ref<IndexBuffer>& indexBuffer)
		: vertexBuffer(vertexBuffer), indexBuffer(indexBuffer)
	{
		ASSERT(vertexBuffer, "VertexBuffer is invalid");
		ASSERT(indexBuffer, "IndexBuffer is invalid");
	}

	VertexArray::~VertexArray()
	{
	}

	ref<VertexArray> VertexArray::create(const ref<VertexBuffer>& vertexBuffer,
		const ref<IndexBuffer>& indexBuffer)
	{
		return makeRef<VertexArray>(vertexBuffer, indexBuffer);
	}
}