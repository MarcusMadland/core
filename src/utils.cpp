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
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "utils.hpp"
#include "debug/logger.hpp"

namespace core::utils
{
	uint8_t* loadTexture2D(const std::string& filename,
		Texture2DParams& outParams, const bool& yFlip)
	{
		// Flip texture
		stbi_set_flip_vertically_on_load(yFlip);

		// Load texture data using stb image
		int width = 0, height = 0, channels = 0;
		uint8_t* bytes = stbi_load(filename.c_str(), &width, &height,
			&channels, 4);
		
		// If we fail to load the texture, we load a debug "no texture" texture
		if (!bytes)
		{
			core::Logger::logError("Failed to create texture, invalid data");

			bytes = stbi_load("../core/assets/textures/no_texture.png",
				&width, &height, &channels, 4);
		}

		// Output texture parameters we need to for the rendering of the texture
		outParams.width = static_cast<uint16_t>(width);
		outParams.height = static_cast<uint16_t>(height);
		outParams.channels = 4;

		return bytes;
	}

	ref<Mesh> processMesh(const aiScene* scene, aiMesh* mesh)
	{
		std::vector<MeshVertex> vertices;
		std::vector<uint16_t> indices;
		// Load verticies
		for (uint32_t i = 0; i < mesh->mNumVertices; i++)
		{
			MeshVertex vertex;
			vertex.position.x = mesh->mVertices[i].x;
			vertex.position.y = mesh->mVertices[i].y;
			vertex.position.z = mesh->mVertices[i].z;
			vertex.normal.x = mesh->mNormals[i].x;
			vertex.normal.y = mesh->mNormals[i].y;
			vertex.normal.z = mesh->mNormals[i].z;
			vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
			vertices.push_back(vertex);
		}
		// Load indices
		for (uint32_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		return Mesh::create(vertices, indices, nullptr);
	}

	void processNode(const aiScene* scene, aiNode* node,
		std::vector<ref<Mesh>>& outMeshes)
	{
		// Process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			outMeshes.push_back(processMesh(scene, mesh));
		}

		// Do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(scene, node->mChildren[i], outMeshes);
		}
	}

	std::vector<ref<Mesh>> loadMesh(const std::string& filename, const MeshLoadSettings& loadSettings)
	{
		std::vector<ref<Mesh>> meshes;

		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			Logger::logCritical(import.GetErrorString());
			return meshes;
		}

		processNode(scene, scene->mRootNode, meshes);

		Logger::logInfo("Loaded %u meshes", meshes.size());
		return meshes;
	}
}