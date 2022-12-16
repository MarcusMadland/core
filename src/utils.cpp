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

#include "utils.hpp"
#include "debug/logger.hpp"

namespace Core
{
	namespace Utils
	{
		bgfx::ShaderHandle LoadShader(const std::string& filename)
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
	}
}