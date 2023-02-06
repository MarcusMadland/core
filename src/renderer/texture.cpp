

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
		if (params.width <= 0 || params.height <= 0)
		{
			Logger::logError("Failed to create texture, invalid texture width or/and height");
		}

		// Flags
		uint64_t flags = 0
			| (params.nearest ? (BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_MIP_POINT) : (BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC))
			| (params.isRenderTarget ? BGFX_TEXTURE_RT : 0)
			| (params.stretch ? BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP : 0);
		
		// Check if texture can be made
		if (!bgfx::isTextureValid(0, false, 1, toBGFX(params.format), BGFX_TEXTURE_RT))
		{
			Logger::logError("Texture with these parameters can't be created");
		}

		// Create texture with data
		if (data)
		{
			handle = bgfx::createTexture2D(
				params.width
				, params.height
				, params.hasMips
				, 1
				, toBGFX(params.format)
				, flags
				, bgfx::copy(data, params.width * params.height *
					params.channels));

			delete data;
		}
		// Create texture without data
		else
		{
			handle = bgfx::createTexture2D(
				params.width
				, params.height
				, params.hasMips
				, 1
				, toBGFX(params.format)
				, flags);
		}
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

	bgfx::TextureFormat::Enum Texture2D::toBGFX(Texture2DFormat format)
	{
		switch (format)
		{
		case core::Texture2DFormat::R1:
			return bgfx::TextureFormat::R1;
		case core::Texture2DFormat::A8:
			return bgfx::TextureFormat::A8;
		case core::Texture2DFormat::R8:
			return bgfx::TextureFormat::R8;
		case core::Texture2DFormat::R8I:
			return bgfx::TextureFormat::R8I;
		case core::Texture2DFormat::R8U:
			return bgfx::TextureFormat::R8U;
		case core::Texture2DFormat::R8S:
			return bgfx::TextureFormat::R8S;
		case core::Texture2DFormat::R16:
			return bgfx::TextureFormat::R16;
		case core::Texture2DFormat::R16I:
			return bgfx::TextureFormat::R16I;
		case core::Texture2DFormat::R16U:
			return bgfx::TextureFormat::R16U;
		case core::Texture2DFormat::R16F:
			return bgfx::TextureFormat::R16F;
		case core::Texture2DFormat::R16S:
			return bgfx::TextureFormat::R16S;
		case core::Texture2DFormat::R32I:
			return bgfx::TextureFormat::R32I;
		case core::Texture2DFormat::R32U:
			return bgfx::TextureFormat::R32U;
		case core::Texture2DFormat::R32F:
			return bgfx::TextureFormat::R32F;
		case core::Texture2DFormat::RG8:
			return bgfx::TextureFormat::RG8;
		case core::Texture2DFormat::RG8I:
			return bgfx::TextureFormat::RG8I;
		case core::Texture2DFormat::RG8U:
			return bgfx::TextureFormat::RG8U;
		case core::Texture2DFormat::RG8S:
			return bgfx::TextureFormat::RG8S;
		case core::Texture2DFormat::RG16:
			return bgfx::TextureFormat::RG16;
		case core::Texture2DFormat::RG16I:
			return bgfx::TextureFormat::RG16I;
		case core::Texture2DFormat::RG16U:
			return bgfx::TextureFormat::RG16U;
		case core::Texture2DFormat::RG16F:
			return bgfx::TextureFormat::RG16F;
		case core::Texture2DFormat::RG16S:
			return bgfx::TextureFormat::RG16S;
		case core::Texture2DFormat::RG32I:
			return bgfx::TextureFormat::RG32I;
		case core::Texture2DFormat::RG32U:
			return bgfx::TextureFormat::RG32U;
		case core::Texture2DFormat::RG32F:
			return bgfx::TextureFormat::RG32F;
		case core::Texture2DFormat::RGB8:
			return bgfx::TextureFormat::RGB8;
		case core::Texture2DFormat::RGB8I:
			return bgfx::TextureFormat::RGB8I;
		case core::Texture2DFormat::RGB8U:
			return bgfx::TextureFormat::RGB8U;
		case core::Texture2DFormat::RGB8S:
			return bgfx::TextureFormat::RGB8S;
		case core::Texture2DFormat::RGB9E5F:
			return bgfx::TextureFormat::RGB9E5F;
		case core::Texture2DFormat::BGRA8:
			return bgfx::TextureFormat::BGRA8;
		case core::Texture2DFormat::RGBA8:
			return bgfx::TextureFormat::RGBA8;
		case core::Texture2DFormat::RGBA8I:
			return bgfx::TextureFormat::RGBA8I;
		case core::Texture2DFormat::RGBA8U:
			return bgfx::TextureFormat::RGBA8U;
		case core::Texture2DFormat::RGBA8S:
			return bgfx::TextureFormat::RGBA8S;
		case core::Texture2DFormat::RGBA16:
			return bgfx::TextureFormat::RGBA16;
		case core::Texture2DFormat::RGBA16I:
			return bgfx::TextureFormat::RGBA16I;
		case core::Texture2DFormat::RGBA16U:
			return bgfx::TextureFormat::RGBA16U;
		case core::Texture2DFormat::RGBA16F:
			return bgfx::TextureFormat::RGBA16F;
		case core::Texture2DFormat::RGBA16S:
			return bgfx::TextureFormat::RGBA16S;
		case core::Texture2DFormat::RGBA32I:
			return bgfx::TextureFormat::RGBA32I;
		case core::Texture2DFormat::RGBA32U:
			return bgfx::TextureFormat::RGBA32U;
		case core::Texture2DFormat::RGBA32F:
			return bgfx::TextureFormat::RGBA32F;
		case core::Texture2DFormat::R5G6B5:
			return bgfx::TextureFormat::R5G6B5;
		case core::Texture2DFormat::RGBA4:
			return bgfx::TextureFormat::RGBA4;
		case core::Texture2DFormat::RGB5A1:
			return bgfx::TextureFormat::RGB5A1;
		case core::Texture2DFormat::RGB10A2:
			return bgfx::TextureFormat::RGB10A2;
		case core::Texture2DFormat::RG11B10F:
			return bgfx::TextureFormat::RG11B10F;
		case core::Texture2DFormat::D16:
			return bgfx::TextureFormat::D16;
		case core::Texture2DFormat::D24:
			return bgfx::TextureFormat::D24;
		case core::Texture2DFormat::D24S8:
			return bgfx::TextureFormat::D24S8;
		case core::Texture2DFormat::D32:
			return bgfx::TextureFormat::D32;
		case core::Texture2DFormat::D16F:
			return bgfx::TextureFormat::D16F;
		case core::Texture2DFormat::D24F:
			return bgfx::TextureFormat::D24F;
		case core::Texture2DFormat::D32F:
			return bgfx::TextureFormat::D32F;
		case core::Texture2DFormat::D0S8:
			return bgfx::TextureFormat::D0S8;
		default:
			return bgfx::TextureFormat::RGBA8;
		}
	}
}