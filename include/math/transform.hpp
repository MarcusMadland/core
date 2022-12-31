

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Core
{
	struct Transform
	{
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		
		explicit Transform(glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale = glm::vec3(1.0f));
		
		friend bool operator!= (const Transform& a, const Transform& b);
		friend bool operator== (const Transform& a, const Transform& b);
		friend Transform operator* (const Transform& a, const Transform& b);
		friend Transform operator+ (const Transform& a, const Transform& b);
	};
}