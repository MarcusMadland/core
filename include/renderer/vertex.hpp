

#pragma once

#include <glm/glm.hpp>

namespace core
{
	struct PrimitiveVertex
	{
		glm::vec3 position;
		uint32_t color;
		glm::vec3 normal;

		PrimitiveVertex();
	};

	struct MeshVertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 biNormal;
		glm::vec2 texCoord;
		glm::vec4 data; // x = texID

		MeshVertex();
	};
}