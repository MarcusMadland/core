

#pragma once

#include <vector>

#include "vertex.hpp"
#include "math/transform.hpp"

namespace Core
{
	class Primitive
	{
	public:
		Primitive() = default;
		Primitive(const std::vector<PrimitiveVertex>& primitiveVertices,
			const std::vector<uint16_t>& primitiveIndices);
		virtual ~Primitive() = default;
		
		Primitive(const Primitive&) = default;
		Primitive(Primitive&&) = default;
		
		Primitive& operator=(const Primitive&) = default;
		Primitive& operator=(Primitive&&) = default;

		void Make(const std::vector<PrimitiveVertex>& primitiveVertices,
			const std::vector<uint16_t>& primitiveIndices);

		[[nodiscard]] const std::vector<PrimitiveVertex>& GetVertices() const { return vertices; }
		[[nodiscard]] const std::vector<uint16_t>& GetIndices() const { return indices; }

	public:
		std::vector<PrimitiveVertex> vertices;
		std::vector<uint16_t> indices;
	};

	class Cube final : public Primitive
	{
	public:
		explicit Cube(const glm::vec3& scale = glm::vec3(1.0f));
	};

	class Pyramid final : public Primitive
	{
	public:
		explicit Pyramid(const glm::vec3& scale = glm::vec3(1.0f));
	};

	class Sphere final : public Primitive
	{
	public:
		explicit Sphere(const float& radius = 1.0f);
	};

	class Quad final : public Primitive
	{
	public:
		explicit Quad(float scale = 1.0f);
	};

	class Line final : public Primitive
	{
	public:
		explicit Line();
	};

	class Grid final : public Primitive
	{
	public:
		explicit Grid();
	};

	class Circle final : public Primitive
	{
	public:
		explicit Circle(float radius = 1.0f);
	};
}