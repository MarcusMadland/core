#include "crpch.hpp"

#include "renderer/buffers.hpp"

namespace core
{
	VertexArray::VertexArray(bgfx::VertexBufferHandle vbh, bgfx::IndexBufferHandle ibh)
		: vbh(vbh), ibh(ibh)
	{
	}

	VertexArray::~VertexArray()
	{
		bgfx::destroy(ibh);
		bgfx::destroy(vbh);
	}

	ref<VertexArray> VertexArray::create(bgfx::VertexBufferHandle vbh, bgfx::IndexBufferHandle ibh)
	{
		return makeRef<VertexArray>(vbh, ibh);
	}
}