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

#include "common.hpp"

/*
 * Forward Declarations
 */
struct bgfx::TextureHandle;

namespace core
{
	enum class Texture2DFormat
	{
		// Colors
		R1,
		A8,
		R8,
		R8I,
		R8U,
		R8S,
		R16,
		R16I,
		R16U,
		R16F,
		R16S,
		R32I,
		R32U,
		R32F,
		RG8,
		RG8I,
		RG8U,
		RG8S,
		RG16,
		RG16I,
		RG16U,
		RG16F,
		RG16S,
		RG32I,
		RG32U,
		RG32F,
		RGB8,
		RGB8I,
		RGB8U,
		RGB8S,
		RGB9E5F,
		BGRA8,
		RGBA8,
		RGBA8I,
		RGBA8U,
		RGBA8S,
		RGBA16,
		RGBA16I,
		RGBA16U,
		RGBA16F,
		RGBA16S,
		RGBA32I,
		RGBA32U,
		RGBA32F,
		R5G6B5,
		RGBA4,
		RGB5A1,
		RGB10A2,
		RG11B10F,

		// Depths
		D16,
		D24,
		D24S8,
		D32,
		D16F,
		D24F,
		D32F,
		D0S8,
	};

	struct Texture2DParams
	{
		Texture2DFormat format = Texture2DFormat::RGBA8;

		bool hasMips = false;
		bool nearest = false;
		bool stretch = true;
		bool isRenderTarget = false;

		uint16_t width = 0;
		uint16_t height = 0;
		uint16_t channels = 0;
	};

	class Texture2D
	{
		friend class Material;
		friend class Framebuffer;

	public:
		Texture2D(const uint8_t* data, const Texture2DParams& params);
		~Texture2D();

		Texture2D(const Texture2D&) = default;
		Texture2D(Texture2D&&) = default;

		Texture2D& operator=(const Texture2D&) = default;
		Texture2D& operator=(Texture2D&&) = default;

		[[nodiscard]] const Texture2DParams& getParams() const { return params; }

		static ref<Texture2D> create(const uint8_t* data,
			const Texture2DParams& params);

	private:
		bgfx::TextureFormat::Enum Texture2D::toBGFX(Texture2DFormat format);

	public: // @todo make private 
		Texture2DParams params;
		bgfx::TextureHandle handle;
	};
}