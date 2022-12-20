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