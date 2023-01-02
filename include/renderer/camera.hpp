

#pragma once

#include <glm/glm.hpp>

#include "common.hpp"

namespace core
{
	struct CameraParams
	{
		float fov = 45.0f;
		float width = 1280.0f;
		float height = 720.0f;
		float clipNear = 0.001f;
		float clipFar = 100.0f;
		glm::vec3 lookAt = glm::vec3(0.0f);
		glm::vec3 position = glm::vec3(0.0f, 0.0f, -5.0f);
	};

	class Camera final
	{
	public:
		Camera(const CameraParams& params, const uint32_t viewID);
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

		static ref<Camera> create(const CameraParams& params, const uint32_t viewID = 0);

	private:
		CameraParams params;

		glm::mat4 view;
		glm::mat4 proj;

		uint32_t viewID;
	};
}