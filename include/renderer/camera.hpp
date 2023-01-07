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

#include <glm/glm.hpp>

#include "common.hpp"
#include "app/app.hpp"

namespace core
{
	struct CameraParams
	{
		float fov = 45.0f;
		float width = static_cast<float>(App::getInstance().getWindow().getWidth());
		float height = static_cast<float>(App::getInstance().getWindow().getHeight());
		float clipNear = 0.001f;
		float clipFar = 100.0f;
		glm::vec3 lookAt = glm::vec3(0.0f);
		glm::vec3 position = glm::vec3(0.0f, 0.0f, -5.0f);
	};

	class Camera final
	{
	public:
		Camera(const CameraParams& params, const uint32_t& viewID);
		~Camera() = default;

		Camera(const Camera&) = default;
		Camera(Camera&&) = default;

		Camera& operator=(const Camera&) = default;
		Camera& operator=(Camera&&) = default;

		void recalculate();

		[[nodiscard]] const CameraParams& getParams() const { return params; }
		[[nodiscard]] CameraParams& getParams() { return params; }

		[[nodiscard]] const uint32_t& getViewID() const { return viewID; }
		[[nodiscard]] const glm::mat4& getViewMatrix() const { return view; }
		[[nodiscard]] const glm::mat4& getProjectionMatrix() const { return proj; }
		[[nodiscard]] const glm::mat4& getViewProjectionMatrix() const { return view * proj; }

		static ref<Camera> create(const CameraParams& params, const uint32_t& viewID = 0);

	private:
		CameraParams params;

		glm::mat4 view;
		glm::mat4 proj;

		uint32_t viewID;
	};
}