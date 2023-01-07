/*
 * Copyright 2022 Marcus Madland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "crpch.hpp"

#include "defines.hpp"
#include "renderer/shader.hpp"
#include "debug/logger.hpp"

namespace core
{
	Shader::Shader(const std::string& filenameVertex,
		const std::string& filenameFragment)
		: handle(BGFX_INVALID_HANDLE)
	{
		// Create handles for vertex and fragment shader
		const bgfx::ShaderHandle vsh = loadShader(filenameVertex);
		const bgfx::ShaderHandle fsh = loadShader(filenameFragment);

		// Create handle for shader program with the vertex and fragment shader
		handle = bgfx::createProgram(vsh, fsh, true);

		// Create shader name from filename
		const size_t first = filenameVertex.find_last_of('/') + 1;
		const size_t last = filenameVertex.find_last_of('-');
		name = filenameVertex.substr(first, last - first);

		Logger::logInfo("Loaded shader: %s", name.c_str());
	}

	Shader::~Shader()
	{
		bgfx::destroy(handle);
	}

	ref<Shader> Shader::create(const std::string& filenameVertex,
		const std::string& filenameFragment)
	{
		return makeRef<Shader>(filenameVertex, filenameFragment);
	}

	bgfx::ShaderHandle Shader::loadShader(const std::string& filename)
	{
		FILE* file;
		fopen_s(&file, filename.c_str(), "rb");
		
		ASSERT(file, "Failed to load shader (usually invalid path)");

		fseek(file, 0, SEEK_END);
		const long fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		const bgfx::Memory* mem = bgfx::alloc(fileSize + 1);
		fread(mem->data, 1, fileSize, file);
		mem->data[mem->size - 1] = '\0';
		fclose(file);

		return bgfx::createShader(mem);
	}

	void ShaderManager::loadAndAdd(const std::string& vertexShaderPath,
		const std::string& fragmentShaderPath)
	{
		if (const ref<Shader> shader = load(vertexShaderPath,
			fragmentShaderPath))
		{
			add(shader);
		}	
	}

	void ShaderManager::add(const ref<Shader>& shader)
	{
		shaders[shader->getName()] = shader;
	}

	ref<Shader> ShaderManager::load(const std::string& vertexShaderPath,
		const std::string& fragmentShaderPath)
	{
		ref<Shader> shader = Shader::create(vertexShaderPath,
			fragmentShaderPath);

		return shader;
	}

	ref<Shader> ShaderManager::get(const std::string& name)
	{
		return shaders[name];
	}
}