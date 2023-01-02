

#pragma once

#include <unordered_map>
#include <string>
#include <bgfx/bgfx.h>

#include "common.hpp"

namespace Core
{
	class Shader
	{
	public:
		Shader(const std::string& filenameVertex, const std::string& filenameFragment);
		~Shader();

		const std::string GetName() const { return name; }

		static Ref<Shader> Create(const std::string& filenameVertex, const std::string& filenameFragment);

	private:
		bgfx::ShaderHandle LoadShader(const std::string& filename);

	private: 
		friend class Renderer;

		bgfx::ProgramHandle handle;
		std::string name;
	};

	class ShaderManager
	{
	public:
		void LoadAndAdd(const std::string& vertexShaderPath,
			const std::string& fragmentShaderPath);
		void Add(const Ref<Shader>& shader);
		static Ref<Shader> Load(const std::string& vertexShaderPath,
			const std::string& fragmentShaderPath);
		Ref<Shader> Get(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Shader>> shaders;
	};
}