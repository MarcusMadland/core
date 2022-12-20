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

#include "common.hpp"
#include "shader.hpp"

class Texture;

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
	public:
		Material(MaterialParams params);
		~Material();

		Ref<Shader> GetShader() { return shader; }

		static Ref<Material> Create(MaterialParams params);

	private:
		MaterialParams params;

		Ref<Shader> shader;
		std::vector<Ref<Texture>> textures;
	};
}