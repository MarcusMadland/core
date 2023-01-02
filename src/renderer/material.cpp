

#include "crpch.hpp"

#include "renderer/material.hpp"
#include "renderer/renderer.hpp"

namespace core
{
	Material::Material(MaterialParams params)
		: params(params)
	{
		shader = Renderer::getShaderManager()->get("uber");

		// Uniforms
		u_BaseColorMap = bgfx::createUniform("u_BaseColorMap", bgfx::UniformType::Sampler, 2);
		u_BaseColorFactor = bgfx::createUniform("u_BaseColorFactor", bgfx::UniformType::Vec4);
	}

	Material::~Material()
	{
	}

	void Material::addTexture(ref<Texture2D> texture, const std::string& name)
	{
		textures[name] = texture;
	}

	void Material::setBasecolor(const std::string& textureName, const uint32_t& index)
	{
		baseColorMap = textures[textureName];
	}

	void Material::setBasecolor(glm::vec4 color)
	{
		baseColorFactor = color;
	}

	void Material::updateUniforms()
	{
		// Base Color	
		if (baseColorMap)
		{
			bgfx::setTexture(0, u_BaseColorMap, baseColorMap->handle);
		}
		else
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

	ref<Material> Material::create(MaterialParams params)
	{
		return makeRef<Material>(params);
	}
}