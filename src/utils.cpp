

#include "crpch.hpp"

#include <stb_image.h>

#include "utils.hpp"
#include "debug/logger.hpp"

namespace core
{
	namespace utils
	{
		uint8_t* loadTexture2D(const std::string& filename, Texture2DParams& outParams)
		{
			// Flip texture
			stbi_set_flip_vertically_on_load(true);

			// Load texture data using stb image
			int width = 0, height = 0, channels = 0;
			uint8_t* bytes = stbi_load(filename.c_str(), &width, &height, &channels, 4);
			
			// If we fail to load the texture, we load a debug "no texture" texture
			if (!bytes)
			{
				core::Logger::logError("Failed to create texture, invalid data");

				bytes = stbi_load("../core/assets/textures/no_texture.png", &width, &height, &channels, 4);
			}

			// Output texture parameters we need to for the rendering of the texture
			outParams.width = width;
			outParams.height = height;
			outParams.channels = 4;

			return bytes;
		}
	}
}