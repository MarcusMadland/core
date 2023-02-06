#pragma once

#include <bgfx/bgfx.h>

#include "common.hpp"
#include "texture.hpp"

namespace core
{
	struct FramebufferParams
	{
		
	};

	class Framebuffer
	{
		friend class Renderer;

	public:
		Framebuffer(const FramebufferParams& params);
		~Framebuffer();

		Framebuffer(const Framebuffer&) = default;
		Framebuffer(Framebuffer&&) = default;

		Framebuffer& operator=(const Framebuffer&) = default;
		Framebuffer& operator=(Framebuffer&&) = default;

		[[nodiscard]] const FramebufferParams& getParams() const { return params; }

		static ref<Framebuffer> create(const FramebufferParams& params);

	private:
		FramebufferParams params;
		std::vector<ref<Texture2D>> textures;
		bgfx::FrameBufferHandle handle;
	};
}