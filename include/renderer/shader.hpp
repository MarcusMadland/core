

#pragma once

#include <unordered_map>
#include <string>
#include <bgfx/bgfx.h>

#include "common.hpp"

namespace core
{
	class Shader
	{
	public:
		Shader(const std::string& filenameVertex, const std::string& filenameFragment);
		~Shader();

		const std::string getName() const { return name; }

		static ref<Shader> create(const std::string& filenameVertex, const std::string& filenameFragment);

	private:
		bgfx::ShaderHandle loadShader(const std::string& filename);

	private: 
		friend class Renderer;

		bgfx::ProgramHandle handle;
		std::string name;
	};

	class ShaderManager
	{
	public:
		void loadAndAdd(const std::string& vertexShaderPath,
			const std::string& fragmentShaderPath);
		void add(const ref<Shader>& shader);
		static ref<Shader> load(const std::string& vertexShaderPath,
			const std::string& fragmentShaderPath);
		ref<Shader> get(const std::string& name);

	private:
		std::unordered_map<std::string, ref<Shader>> shaders;
	};
}