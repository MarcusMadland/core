#pragma once

#include <bgfx/bgfx.h>

namespace Core
{
	namespace Utils
	{
		bgfx::ShaderHandle LoadShader(const std::string& filename);
	}
}