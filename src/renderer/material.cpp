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

#include "defines.hpp"
#include "renderer/material.hpp"
#include "renderer/renderer.hpp"

namespace core
{
	Material::Material(const MaterialParams& params)
		: params(params)
		, baseColorMap(nullptr), u_BaseColorMap(BGFX_INVALID_HANDLE)
		, baseColorFactor(glm::vec4(CORE_BIG_NUMBER)), u_BaseColorFactor(BGFX_INVALID_HANDLE)
	{
		shader = Renderer::getShaderManager()->get("uber");
		ASSERT(shader, "Shader is null");
			
		// Uniforms
		u_BaseColorMap = bgfx::createUniform("u_BaseColorMap",
			bgfx::UniformType::Sampler, 2);
		u_BaseColorFactor = bgfx::createUniform("u_BaseColorFactor",
			bgfx::UniformType::Vec4);
	}

	void Material::addTexture(const ref<Texture2D>& texture,
		const std::string& name)
	{
		textures[name] = texture;
	}

	void Material::setBasecolor(const std::string& textureName)
	{
		ASSERT(!textureName.empty(), "Texture name is empty");
		baseColorMap = textures[textureName];
	}

	void Material::setBasecolor(const glm::vec4& color)
	{
		baseColorFactor = color;
	}

	void Material::updateUniforms() const
	{
		// Base Color	
		if ((baseColorFactor.w >= CORE_BIG_NUMBER) && baseColorMap)
		{
			bgfx::setTexture(0, u_BaseColorMap, baseColorMap->handle);
		}
		bgfx::setUniform(u_BaseColorFactor, &baseColorFactor); // Set it to default factor when texture is valid

		// States
		const uint64_t default = BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS;

		const uint64_t twoSided    = (params.twoSided) ?
			0 : BGFX_STATE_CULL_CCW;

		const uint64_t translucent = (params.blendType == BlendType::Translucent) ?
			BGFX_STATE_BLEND_ALPHA     : 0;
									
		bgfx::setState(default | twoSided | translucent);
	}

	ref<Material> Material::create(const MaterialParams& params)
	{
		return makeRef<Material>(params);
	}
}