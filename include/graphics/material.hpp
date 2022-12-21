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

#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <bgfx/bgfx.h>

#include "common.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace Core
{
	enum MaterialType
	{
		Default,
	};

	enum BlendType
	{
		Opaque,
		Translucent,
	};

	enum ShadingType
	{
		Lit,
		Unlit,
	};

	struct MaterialParams
	{
		MaterialType materialType = MaterialType::Default;
		BlendType blendType = BlendType::Opaque;
		ShadingType shadingType = ShadingType::Lit;
		bool castShadow = true;
		bool twoSided = false;
	};

	class Material
	{
	friend class Renderer;

	public:
		Material(MaterialParams params);
		~Material();

		void SetBasecolor(Ref<Texture2D> texture);
		void SetBasecolor(glm::vec4 color);

		[[nodiscard]] Ref<Shader> GetShader() { return shader; }

		static Ref<Material> Create(MaterialParams params);

	private:
		void UpdateUniforms();

	private:
		MaterialParams params;

		Ref<Shader> shader;

		Ref<Texture2D> baseColorMap;
		bgfx::UniformHandle u_BaseColorMap;

		glm::vec4 baseColorFactor;
		bgfx::UniformHandle u_BaseColorFactor;
	};
}