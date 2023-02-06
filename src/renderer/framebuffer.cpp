#include "crpch.hpp"

#include <bx/bx.h>

#include "renderer/framebuffer.hpp"
#include "defines.hpp"
#include "debug.hpp"

namespace core
{
	Framebuffer::Framebuffer(const std::vector<ref<Texture2D>>& textures)
		: textures(textures), handle(BGFX_INVALID_HANDLE)
	{
		// Make vector of texture just contain the bgfx handles
		std::vector<bgfx::TextureHandle> texturesHandles;
		for (auto& texture : textures)
		{
			texturesHandles.push_back(texture->handle);
		}
		const bgfx::TextureHandle* textureData = texturesHandles.data();
		
		// Create framebuffer handle with texture handles
		if (textureData)
		{
			handle = bgfx::createFrameBuffer(texturesHandles.size(), textureData, true);
		}

		if (bgfx::isValid(handle))
		{
			Logger::logInfo("Successfully created framebuffer with %u rendertargets", texturesHandles.size());
		}
	}

	Framebuffer::~Framebuffer()
	{
		bgfx::destroy(handle); 
	}

	ref<Framebuffer> Framebuffer::create(const std::vector<ref<Texture2D>>& textures)
	{
		return makeRef<Framebuffer>(textures);
	}
}