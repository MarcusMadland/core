

#include "crpch.hpp"

#include "renderer/shader.hpp"
#include "debug/logger.hpp"

namespace core
{
	Shader::Shader(const std::string& filenameVertex, const std::string& filenameFragment)
		: handle(BGFX_INVALID_HANDLE)
	{
		// Create handles for vertex and fragment shader
		bgfx::ShaderHandle vsh = loadShader(filenameVertex);
		bgfx::ShaderHandle fsh = loadShader(filenameFragment);

		// Create handle for shader program with the vertex and fragment shader
		handle = bgfx::createProgram(vsh, fsh, true);

		// Create shader name from filename
		auto first = filenameVertex.find_last_of('/') + 1;
		auto last = filenameVertex.find_last_of('-');
		name = filenameVertex.substr(first, last - first);

		Logger::logInfo("Loaded shader: %s", name.c_str());
	}

	Shader::~Shader()
	{
		bgfx::destroy(handle);
	}

	ref<Shader> Shader::create(const std::string& filenameVertex, const std::string& filenameFragment)
	{
		return makeRef<Shader>(filenameVertex, filenameFragment);
	}

	bgfx::ShaderHandle Shader::loadShader(const std::string& filename)
	{
		FILE* file = fopen(filename.c_str(), "rb");
		if (!file)
		{
			Logger::logCritical("Failed to load shader");
			return bgfx::ShaderHandle();
		}

		fseek(file, 0, SEEK_END);
		long fileSize = ftell(file);
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
		if (const ref<Shader> shader = load(vertexShaderPath, fragmentShaderPath))
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
		ref<Shader> shader = Shader::create(vertexShaderPath, fragmentShaderPath);

		return shader;
	}

	ref<Shader> ShaderManager::get(const std::string& name)
	{
		return shaders[name];
	}
}