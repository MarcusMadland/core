

#include "crpch.hpp"

#include "graphics/shader.hpp"
#include "debug/logger.hpp"

namespace Core
{
	Shader::Shader(const std::string& filenameVertex, const std::string& filenameFragment)
		: handle(BGFX_INVALID_HANDLE)
	{
		// Create handles for vertex and fragment shader
		bgfx::ShaderHandle vsh = LoadShader(filenameVertex);
		bgfx::ShaderHandle fsh = LoadShader(filenameFragment);

		// Create handle for shader program with the vertex and fragment shader
		handle = bgfx::createProgram(vsh, fsh, true);

		// Create shader name from filename
		auto first = filenameVertex.find_last_of('/') + 1;
		auto last = filenameVertex.find_last_of('-');
		name = filenameVertex.substr(first, last - first);

		Logger::LogInfo("Loaded shader: %s", name.c_str());
	}

	Shader::~Shader()
	{
		bgfx::destroy(handle);
	}

	Ref<Shader> Shader::Create(const std::string& filenameVertex, const std::string& filenameFragment)
	{
		return MakeRef<Shader>(filenameVertex, filenameFragment);
	}

	bgfx::ShaderHandle Shader::LoadShader(const std::string& filename)
	{
		FILE* file = fopen(filename.c_str(), "rb");
		if (!file)
		{
			Logger::LogCritical("Failed to load shader");
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

	void ShaderManager::LoadAndAdd(const std::string& vertexShaderPath,
		const std::string& fragmentShaderPath)
	{
		if (const Ref<Shader> shader = Load(vertexShaderPath, fragmentShaderPath))
		{
			Add(shader);
		}	
	}

	void ShaderManager::Add(const Ref<Shader>& shader)
	{
		shaders[shader->GetName()] = shader;
	}

	Ref<Shader> ShaderManager::Load(const std::string& vertexShaderPath,
		const std::string& fragmentShaderPath)
	{
		Ref<Shader> shader = Shader::Create(vertexShaderPath, fragmentShaderPath);

		return shader;
	}

	Ref<Shader> ShaderManager::Get(const std::string& name)
	{
		return shaders[name];
	}
}