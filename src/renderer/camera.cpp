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

#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer/camera.hpp"

namespace core
{
	Camera::Camera(const CameraParams& params, const uint32_t& viewID)
		: params(params), view(glm::mat4(1.0f)), proj(glm::mat4(1.0f))
		, viewID(viewID)
	{
		recalculate();
	}

	void Camera::recalculate()
	{
		bx::mtxLookAt(&view[0][0],
			{ params.position.x, params.position.y, params.position.z },
			{ params.lookAt.x, params.lookAt.y, params.lookAt.z });

		bx::mtxProj(&proj[0][0], params.fov, params.width / params.height,
			params.clipNear, params.clipFar, bgfx::getCaps()->homogeneousDepth);

		bgfx::setViewTransform(static_cast<uint16_t>(viewID), &view[0][0],
			&proj[0][0]);
	}

	ref<Camera> Camera::create(const CameraParams& params, const uint32_t& viewID )
	{
		return makeRef<Camera>(params, viewID);
	}
}