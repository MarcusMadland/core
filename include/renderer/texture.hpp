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

#include "common.hpp"

// Forward Declarations
struct bgfx::TextureHandle;

namespace core
{
	struct Texture2DParams
	{
		bool hasMips = false;
		bool nearest = false;

		uint16_t width = 0;
		uint16_t height = 0;
		uint16_t channels = 0;
	};

	class Texture2D
	{
		friend class Material;

	public:
		Texture2D(const uint8_t* data, const Texture2DParams& params);
		~Texture2D();

		Texture2D(const Texture2D&) = default;
		Texture2D(Texture2D&&) = default;

		Texture2D& operator=(const Texture2D&) = default;
		Texture2D& operator=(Texture2D&&) = default;

		[[nodiscard]] const Texture2DParams& getParams() const { return params; }

		static ref<Texture2D> create(const void* data,
			const Texture2DParams& params);

	private: 
		Texture2DParams params;
		bgfx::TextureHandle handle;
	};
}