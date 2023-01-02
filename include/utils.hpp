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

/*
 * Collection of commonly used utility functions
 */
#pragma once

#include <bgfx/bgfx.h>
#include "renderer/texture.hpp"

namespace core
{
	namespace utils
	{
		/*
		 * Loads a texture's data
		 *
		 * @remark The out params can be further modified before creation of
		 * texture
		 *
		 * @param[in] filename The directory and filename of the texture
		 * @param[out] outParams The texture parameters out put used to create
		 * a texture
		 *
		 * @return Texture data in bytes
		 */
		uint8_t* loadTexture2D(const std::string& filename, Texture2DParams& outParams);
	}
}