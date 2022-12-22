#include "crpch.hpp"

#include "graphics/vertex_array.hpp"

namespace Core
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

	Ref<VertexArray> VertexArray::Create(bgfx::VertexBufferHandle vbh, bgfx::IndexBufferHandle ibh)
	{
		return MakeRef<VertexArray>(vbh, ibh);
	}
}