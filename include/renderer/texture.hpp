

#pragma once

#include "common.hpp"

struct bgfx::TextureHandle;

namespace Core
{
	struct Texture2DParams
	{
		bool hasMips = false;
		bool nearest = false;

		uint16_t width = 0;
		uint16_t height = 0;
		uint16_t channels = 0;
	};

	class Texture2D
	{
		friend class Material;

	public:
		Texture2D(void* data, const Texture2DParams& params);
		~Texture2D();

		[[nodiscard]] const Texture2DParams& GetParams() const { return params; }

		static Ref<Texture2D> Create(void* data, const Texture2DParams& params);

	private: 
		Texture2DParams params;
		bgfx::TextureHandle handle;
		
	};
}