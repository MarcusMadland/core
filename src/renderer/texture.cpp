

#include "crpch.hpp"

#include <bgfx/bgfx.h>

#include "defines.hpp"
#include "renderer/texture.hpp"
#include "debug/logger.hpp"

namespace core
{
	Texture2D::Texture2D(const uint8_t* data, const Texture2DParams& params)
		: params(params), handle(BGFX_INVALID_HANDLE)
	{
		ASSERT(data, "Texture data is invalid");

		if (params.width <= 0 || params.height <= 0)
		{
			Logger::logError("Failed to create texture, invalid texture width or/and height");
		}

		if (!bgfx::isTextureValid(0, false, 1,
			bgfx::TextureFormat::RGBA8, BGFX_SAMPLER_U_BORDER |
			BGFX_SAMPLER_V_BORDER))
		{
			Logger::logError("Texture with these input can't be created");
		}

		// Create texture handle
		handle = bgfx::createTexture2D(
			params.width
			, params.height
			, params.hasMips
			, 1
			, bgfx::TextureFormat::RGBA8
			, (params.nearest ? (BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT) : (BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC)) | BGFX_SAMPLER_U_BORDER | BGFX_SAMPLER_V_BORDER
			, bgfx::copy(data, params.width * params.height *
				params.channels)
		);

		// Delete input data since we copy the data to the handle
		delete data;
	}

	Texture2D::~Texture2D()
	{
		// Destroy our texture handle
		bgfx::destroy(handle);
	}

	ref<Texture2D> Texture2D::create(const uint8_t* data,
		const Texture2DParams& params)
	{
		return makeRef<Texture2D>(data, params);
	}
}