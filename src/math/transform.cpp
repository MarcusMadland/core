

#include "crpch.hpp"

#include "math/transform.hpp"

namespace core
{
	Transform::Transform(const glm::vec3 position, const glm::quat rotation ,
		const glm::vec3 scale )
		: position(position)
		, rotation(rotation)
		, scale(scale)
	{
	}

	bool operator!=(const Transform& a, const Transform& b)
	{
		const bool pos = a.position != b.position;
		const bool ori = a.rotation != b.rotation;
		const bool scale = a.scale != b.scale;

		return (pos || ori || scale);
	}

	bool operator==(const Transform& a, const Transform& b)
	{
		const bool pos = a.position == b.position;
		const bool ori = a.rotation == b.rotation;
		const bool scale = a.scale == b.scale;

		return (pos && ori && scale);
	}

	Transform operator*(const Transform& a, const Transform& b)
	{
		return Transform(a.position * b.position, a.rotation * b.rotation, a.scale * b.scale);
	}

	Transform operator+(const Transform& a, const Transform& b)
	{
		return Transform(a.position + b.position, a.rotation + b.rotation, a.scale + b.scale);
	}
}