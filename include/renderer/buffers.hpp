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
	enum class AttribType
	{
		Uint8,  
		Uint10, 
		Int16,  
		Half,   
		Float,  
	};

	enum class Attrib
	{
		Position, 
		Normal,   
		Tangent,   
		Bitangent, 
		Color0,    
		Color1,    
		Color2,    
		Color3,    
		Indices,   
		Weight,    
		TexCoord0, 
		TexCoord1,
		TexCoord2, 
		TexCoord3, 
		TexCoord4, 
		TexCoord5, 
		TexCoord6, 
		TexCoord7, 
	};

	struct BufferElement
	{
		AttribType attribType;
		uint8_t num;
		Attrib attrib;

		BufferElement(const AttribType& attribType, const uint8_t& num, const Attrib& attrib)
			: attribType(attribType), num(num), attrib(attrib)
		{}
	};

	class BufferLayout
	{
	public:
		BufferLayout(const std::vector<BufferElement>& elements)
			: elements(elements)
		{}

		[[nodiscard]] const std::vector<BufferElement> getElements() const { return elements; }

	private:
		std::vector<BufferElement> elements;
	};

	class VertexBuffer
	{
		friend class Renderer;

	public:
		VertexBuffer(const BufferLayout& layout, const void* data, 
			const uint32_t& size);
		~VertexBuffer();

		VertexBuffer(const VertexBuffer&) = default;
		VertexBuffer(VertexBuffer&&) = default;

		VertexBuffer& operator=(const VertexBuffer&) = default;
		VertexBuffer& operator=(VertexBuffer&&) = default;

		static ref<VertexBuffer> create(const BufferLayout& layout, const void* data, 
			const uint32_t& size);

	private:
		bgfx::Attrib::Enum attribToBgfx(const Attrib& attrib);
		bgfx::AttribType::Enum attribTypeToBgfx(const AttribType& attribType);

	private:
		bgfx::VertexBufferHandle handle;
	};

	class IndexBuffer
	{
		friend class Renderer;

	public:
		IndexBuffer(const void* data, const uint32_t& size);
		~IndexBuffer();

		IndexBuffer(const IndexBuffer&) = default;
		IndexBuffer(IndexBuffer&&) = default;

		IndexBuffer& operator=(const IndexBuffer&) = default;
		IndexBuffer& operator=(IndexBuffer&&) = default;

		static ref<IndexBuffer> create(const void* data, const uint32_t& size);

	private:
		bgfx::IndexBufferHandle handle;
	};

	class VertexArray
	{
	friend class Renderer;
		
	public:
		VertexArray(const ref<VertexBuffer>& vertexBuffer,
			const ref<IndexBuffer>& indexBuffer);
		~VertexArray();

		VertexArray(const VertexArray&) = default;
		VertexArray(VertexArray&&) = default;

		VertexArray& operator=(const VertexArray&) = default;
		VertexArray& operator=(VertexArray&&) = default;

		static ref<VertexArray> create(const ref<VertexBuffer>& vertexBuffer,
			const ref<IndexBuffer>& indexBuffer);

	private:
		ref<VertexBuffer> vertexBuffer;
		ref<IndexBuffer> indexBuffer;
	};
}