#include "crpch.hpp"

#include "renderer/buffers.hpp"

namespace core
{
	VertexArray::VertexArray(const bgfx::VertexBufferHandle& vbh,
		const bgfx::IndexBufferHandle& ibh)
		: vbh(vbh), ibh(ibh)
	{
	}

	VertexArray::~VertexArray()
	{
		bgfx::destroy(ibh);
		bgfx::destroy(vbh);
	}

	ref<VertexArray> VertexArray::create(const bgfx::VertexBufferHandle& vbh,
		const bgfx::IndexBufferHandle& ibh)
	{
		return makeRef<VertexArray>(vbh, ibh);
	}
}