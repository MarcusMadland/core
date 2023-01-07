/*
 * Copyright 2022 Marcus Madland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <bgfx/bgfx.h>

#include "common.hpp"

namespace core
{
	// @todo Create buffer wrappers for vbo and ibo as well? Is it really needed?
	class VertexArray
	{
	friend class Renderer;
		
	public:
		VertexArray(const bgfx::VertexBufferHandle& vbh,
			const bgfx::IndexBufferHandle& ibh);
		~VertexArray();

		VertexArray(const VertexArray&) = default;
		VertexArray(VertexArray&&) = default;

		VertexArray& operator=(const VertexArray&) = default;
		VertexArray& operator=(VertexArray&&) = default;

		static ref<VertexArray> create(const bgfx::VertexBufferHandle& vbh,
			const bgfx::IndexBufferHandle& ibh);

	private:
		bgfx::VertexBufferHandle vbh;
		bgfx::IndexBufferHandle ibh;
	};
}