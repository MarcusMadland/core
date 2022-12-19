#pragma once

#include "shader.hpp"

namespace Core
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static Ref<ShaderLibrary> GetShaderLibrary();

	private:

	};
}