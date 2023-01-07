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
		Shader(const std::string& filenameVertex,
			const std::string& filenameFragment);
		~Shader();

		Shader(const Shader&) = default;
		Shader(Shader&&) = default;

		Shader& operator=(const Shader&) = default;
		Shader& operator=(Shader&&) = default;

		[[nodiscard]] std::string getName() const { return name; }

		static ref<Shader> create(const std::string& filenameVertex,
			const std::string& filenameFragment);

	private:
		static bgfx::ShaderHandle loadShader(const std::string& filename);

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