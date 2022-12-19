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

#include <stb_image.h>

#include "utils.hpp"
#include "debug/logger.hpp"

namespace Core
{
	namespace Utils
	{
		uint8_t* LoadTexture2D(const std::string& filename, Texture2DParams& outParams)
		{
			// Load texture data using stb image
			int width = 0, height = 0, channels = 0;
			uint8_t* bytes = stbi_load(filename.c_str(), &width, &height, &channels, 4);
			
			// If we fail to load the texture, we load a debug "no texture" texture
			if (!bytes)
			{
				Core::Logger::LogError("Failed to create texture, invalid data");

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