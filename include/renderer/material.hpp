

#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <bgfx/bgfx.h>

#include "common.hpp"
#include "defines.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace core
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

		void addTexture(ref<Texture2D> texture, const std::string& name);

		void setBasecolor(const std::string& textureName, const uint32_t& index = 0);
		void setBasecolor(glm::vec4 color);

		[[nodiscard]] ref<Shader> getShader() { return shader; }

		static ref<Material> create(MaterialParams params);

	private:
		void updateUniforms();

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