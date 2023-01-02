

#include "crpch.hpp"

#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer/camera.hpp"

namespace core
{
	Camera::Camera(const CameraParams& params, const uint32_t viewID)
		: params(params), view(glm::mat4(1.0f)), proj(glm::mat4(1.0f)), viewID(viewID)
	{
		bx::mtxLookAt(&view[0][0],
			{ params.position.x, params.position.y, params.position.z },
			{ params.lookAt.x, params.lookAt.y, params.lookAt.z });

		bx::mtxProj(&proj[0][0], params.fov, params.width / params.height,
			params.clipNear, params.clipFar, bgfx::getCaps()->homogeneousDepth);

		bgfx::setViewTransform(viewID, &view[0][0], &proj[0][0]);
	}

	void Camera::recalculate()
	{
		bx::mtxLookAt(&view[0][0],
			{ params.position.x, params.position.y, params.position.z },
			{ params.lookAt.x, params.lookAt.y, params.lookAt.z });

		bx::mtxProj(&proj[0][0], params.fov, params.width / params.height,
			params.clipNear, params.clipFar, bgfx::getCaps()->homogeneousDepth);

		bgfx::setViewTransform(viewID, &view[0][0], &proj[0][0]);
	}

	ref<Camera> Camera::create(const CameraParams& params, const uint32_t viewID )
	{
		return makeRef<Camera>(params, viewID);
	}
}