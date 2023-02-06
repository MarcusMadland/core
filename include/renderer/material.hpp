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

#include <glm/glm.hpp>
#include <bgfx/bgfx.h>

#include "common.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace core
{
	enum class MaterialType
	{
		Default,
	};

	enum class BlendType
	{
		Opaque,
		Translucent,
	};

	enum class ShadingType
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
		explicit Material(const MaterialParams& params);
		~Material() = default;

		Material(const Material&) = default;
		Material(Material&&) = default;

		Material& operator=(const Material&) = default;
		Material& operator=(Material&&) = default;

		void addTexture(const ref<Texture2D>& texture, const std::string& name);

		void setBasecolor(const std::string& textureName);
		void setBasecolor(const glm::vec4& color);

		[[nodiscard]] ref<Shader> getShader() { return shader; }

		static ref<Material> create(const MaterialParams& params);

	private:
		void updateUniforms() const;

	private:
		MaterialParams params;

		ref<Shader> shader;

		std::unordered_map<std::string, ref<Texture2D>> textures;

		ref<Texture2D> baseColorMap;
		bgfx::UniformHandle u_BaseColorMap;

		glm::vec4 baseColorFactor;
		bgfx::UniformHandle u_BaseColorFactor;
	};
}