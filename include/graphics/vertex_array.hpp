#pragma once

#include <bgfx/bgfx.h>

#include "common.hpp"

namespace Core
{
	class VertexArray
	{
	public:
		VertexArray(bgfx::VertexBufferHandle vbh, bgfx::IndexBufferHandle ibh);
		~VertexArray();

		static Ref<VertexArray> Create(bgfx::VertexBufferHandle vbh, bgfx::IndexBufferHandle ibh);

	public: // @todo make private
		bgfx::VertexBufferHandle vbh;
		bgfx::IndexBufferHandle ibh;
	};
}