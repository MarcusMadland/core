

#include "crpch.hpp"

#include "renderer/vertex.hpp"

namespace Core
{
	PrimitiveVertex::PrimitiveVertex()
		: position(glm::vec3(0.0f))
	    , color(0x0f)
		, normal(glm::vec3(0.0f))
	{}

	MeshVertex::MeshVertex()
		: position(glm::vec3(0.0f))
		, normal(glm::vec3(0.0f))
		, tangent(glm::vec3(0.0f))
		, biNormal(glm::vec3(0.0f))
		, texCoord(glm::vec2(0.0f))
		, data(glm::vec4(0.0f))
	{}
}
