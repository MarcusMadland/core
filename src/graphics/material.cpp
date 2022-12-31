

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
		u_BaseColorMap = bgfx::createUniform("u_BaseColorMap", bgfx::UniformType::Sampler, 2);
		u_BaseColorFactor = bgfx::createUniform("u_BaseColorFactor", bgfx::UniformType::Vec4);

		baseColorMap.resize(2);
	}

	Material::~Material()
	{
	}

	void Material::AddTexture(Ref<Texture2D> texture, const std::string& name)
	{
		textures[name] = texture;
	}

	void Material::SetBasecolor(const std::string& textureName, const uint32_t& index)
	{
		baseColorMap[index] = textures[textureName];
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
		// Base Color	
		for (uint32_t i = 0; i < 2; i++)
		{
			if (baseColorMap[i])
			{
				bgfx::setTexture(i, u_BaseColorMap, baseColorMap[i]->handle, i);
			}
		}
		if (baseColorMap.empty())
		{
			bgfx::setUniform(u_BaseColorFactor, &baseColorFactor);
		}

		// States
		uint64_t twoSidedStates = (params.twoSided == true) ? 
			( BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A 
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_DEPTH_TEST_LESS
			| BGFX_STATE_MSAA) : BGFX_STATE_DEFAULT;

		uint64_t translucentStates = (params.blendType == Translucent) ?
			BGFX_STATE_BLEND_ALPHA : 0;
									
		bgfx::setState(twoSidedStates | translucentStates);
	}
}