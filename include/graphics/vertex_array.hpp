#pragma once

#include <bgfx/bgfx.h>

#include "common/types.hpp"

namespace Core
{
	class VertexArray
	{
	public:
		VertexArray(bgfx::VertexBufferHandle vbh, bgfx::IndexBufferHandle ibh);
		~VertexArray();

		static Ref<VertexArray> Create(bgfx::VertexBufferHandle vbh, bgfx::IndexBufferHandle ibh);

	public:
		bgfx::VertexBufferHandle vbh;
		bgfx::IndexBufferHandle ibh;
	};
}