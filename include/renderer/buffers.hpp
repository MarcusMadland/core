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
	class VertexLayout
	{

	};

	class VertexBuffer
	{
	public:
		VertexBuffer(const VertexLayout& layout);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = default;
		VertexBuffer(VertexBuffer&&) = default;

		VertexBuffer& operator=(const VertexBuffer&) = default;
		VertexBuffer& operator=(VertexBuffer&&) = default;

	private:
		bgfx::VertexBufferHandle handle;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		IndexBuffer(const IndexBuffer&) = default;
		IndexBuffer(IndexBuffer&&) = default;

		IndexBuffer& operator=(const IndexBuffer&) = default;
		IndexBuffer& operator=(IndexBuffer&&) = default;

	private:
		bgfx::IndexBufferHandle handle;
	};

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