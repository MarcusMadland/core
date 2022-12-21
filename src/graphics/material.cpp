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

#include "graphics/material.hpp"
#include "graphics/renderer.hpp"

namespace Core
{
	Material::Material(MaterialParams params)
		: params(params)
	{
		shader = Renderer::GetShaderManager()->Get("uber");

		// Uniforms
		u_BaseColorMap = bgfx::createUniform("u_BaseColorMap", bgfx::UniformType::Sampler);
		u_BaseColorFactor = bgfx::createUniform("u_BaseColorFactor", bgfx::UniformType::Vec4);
	}

	Material::~Material()
	{
	}

	void Material::SetBasecolor(Ref<Texture2D> texture)
	{
		baseColorMap = texture;
	}

	void Material::SetBasecolor(glm::vec4 color)
	{
		baseColorFactor = color;
	}

	Ref<Material> Material::Create(MaterialParams params)
	{
		return MakeRef<Material>(params);
	}

	void Material::UpdateUniforms()
	{
		if (baseColorMap)
		{
			bgfx::setTexture(0, u_BaseColorMap, baseColorMap->handle);
		}
		else
		{
			bgfx::setUniform(u_BaseColorFactor, &baseColorFactor);
		}
	}
}