

#pragma once

#include <bgfx/bgfx.h>

#include "graphics/texture.hpp"

namespace Core
{
	namespace Utils
	{
		uint8_t* LoadTexture2D(const std::string& filename, Texture2DParams& outParams);
	}
}