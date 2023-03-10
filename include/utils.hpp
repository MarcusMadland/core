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
#include "renderer/vertex.hpp"
#include "renderer/mesh.hpp"

namespace core::utils
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
	uint8_t* loadTexture2D(const std::string& filename,
		Texture2DParams& outParams, const bool& yFlip = false);

	struct MeshLoadSettings
	{
		bool isSkeletalMesh = false;
	};
	/*
	 * Loads a mesh's data
	 *
	 * @param[in] filename The directory and filename of the mesh
	 * @param[in] loadSettings Settings to use when loading mesh
	 * @param[out] outVertices List of the mesh vertex data
	 * @param[out] outIndices List of the mesh index data
	 *
	 * @return List of mesh pointers
	 */
	std::vector<ref<Mesh>> loadMesh(const std::string& filename, const MeshLoadSettings& loadSettings);
}