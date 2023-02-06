#pragma once

#include <bgfx/bgfx.h>

#include "common.hpp"
#include "texture.hpp"

namespace core
{
	class Framebuffer
	{
		friend class Renderer;

	public:
		Framebuffer(const std::vector<ref<Texture2D>>& textures);
		~Framebuffer();

		Framebuffer(const Framebuffer&) = default;
		Framebuffer(Framebuffer&&) = default;

		Framebuffer& operator=(const Framebuffer&) = default;
		Framebuffer& operator=(Framebuffer&&) = default;

		[[nodiscard]] const std::vector<ref<Texture2D>>& getParams() const { return textures; }

		static ref<Framebuffer> create(const std::vector<ref<Texture2D>>& textures);

	public: // @todo Make private
		const std::vector<ref<Texture2D>> textures;
		
		bgfx::FrameBufferHandle handle;
	};
}