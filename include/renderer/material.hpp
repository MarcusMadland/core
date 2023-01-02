

#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <bgfx/bgfx.h>

#include "common.hpp"
#include "defines.hpp"
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

		void AddTexture(Ref<Texture2D> texture, const std::string& name);

		void SetBasecolor(const std::string& textureName, const uint32_t& index = 0);
		void SetBasecolor(glm::vec4 color);

		[[nodiscard]] Ref<Shader> GetShader() { return shader; }

		static Ref<Material> Create(MaterialParams params);

	private:
		void UpdateUniforms();

	private:
		MaterialParams params;

		Ref<Shader> shader;

		std::unordered_map<std::string, Ref<Texture2D>> textures;

		Ref<Texture2D> baseColorMap;
		bgfx::UniformHandle u_BaseColorMap;

		glm::vec4 baseColorFactor;
		bgfx::UniformHandle u_BaseColorFactor;
	};
}