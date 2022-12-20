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

#include "crpch.hpp"

#include <bgfx/bgfx.h>

#include "graphics/texture.hpp"
#include "debug/logger.hpp"

namespace Core
{
	Texture2D::Texture2D(void* data, const Texture2DParams& params)
		: handle(BGFX_INVALID_HANDLE), params(params)
	{
		if (!data)
		{
			Logger::LogError("Failed to create texture, invalid data");
		}

		if (params.width <= 0 || params.height <= 0)
		{
			Logger::LogError("Failed to create texture, invalid texture width or/and height");
		}

		if (!bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::RGBA8, BGFX_SAMPLER_U_BORDER | BGFX_SAMPLER_V_BORDER))
		{
			Logger::LogError("Failed to create texture, invalid texture");
		}

		// Create bgfx texture handle
		handle = bgfx::createTexture2D(
			params.width
			, params.height
			, params.hasMips
			, 1
			, bgfx::TextureFormat::RGBA8
			, (params.nearest ? (BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT) : (BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC)) | BGFX_SAMPLER_U_BORDER | BGFX_SAMPLER_V_BORDER
			, bgfx::copy(data, params.width * params.height * params.channels)
		);

		// Delete input data since we copy the data to bgfx
		delete data;
	}

	Texture2D::~Texture2D()
	{
		// Destroy our texture handle
		bgfx::destroy(handle);
	}

	Ref<Texture2D> Texture2D::Create(void* data, const Texture2DParams& params)
	{
		return MakeRef<Texture2D>(data, params);
	}
}