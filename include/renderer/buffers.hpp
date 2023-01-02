#pragma once

#include <bgfx/bgfx.h>

#include "common.hpp"

namespace core
{
	class VertexArray
	{
	public:
		VertexArray(bgfx::VertexBufferHandle vbh, bgfx::IndexBufferHandle ibh);
		~VertexArray();

		static ref<VertexArray> create(bgfx::VertexBufferHandle vbh, bgfx::IndexBufferHandle ibh);

	public: // @todo make private
		bgfx::VertexBufferHandle vbh;
		bgfx::IndexBufferHandle ibh;
	};
}