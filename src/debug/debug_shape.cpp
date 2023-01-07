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

#include "debug/debug_shape.hpp"

namespace core
{
	Primitive::Primitive(const std::vector<PrimitiveVertex>& primitiveVertices,
			const std::vector<uint16_t>& primitiveIndices)
	{
		vertices = primitiveVertices;
		indices = primitiveIndices;
	}

	void Primitive::make(const std::vector<PrimitiveVertex>& primitiveVertices,
			const std::vector<uint16_t>& primitiveIndices)
	{
		vertices = primitiveVertices;
		indices = primitiveIndices;
	}

	
	// Hard coded Cube that will be used mostly for debug drawing
	Cube::Cube()
	{
		constexpr glm::vec3 scale = glm::vec3(1.0f);
		
		std::vector<PrimitiveVertex> vertices;
		vertices.resize(36);
		vertices[0].position = { -scale.x ,  scale.y ,  scale.z };
		vertices[1].position = {  scale.x ,  scale.y ,  scale.z };
		vertices[2].position = { -scale.x , -scale.y ,  scale.z };
		vertices[3].position = {  scale.x , -scale.y ,  scale.z };
		vertices[4].position = { -scale.x ,  scale.y , -scale.z };
		vertices[5].position = {  scale.x ,  scale.y , -scale.z };
		vertices[6].position = { -scale.x , -scale.y , -scale.z };
		vertices[7].position = {  scale.x , -scale.y , -scale.z };

		const uint16_t indicesArr[] =
		{
			0, 2, 3, 1, 5, 7, 6, 4,
			0, 2, 6, 4, 5, 7, 3, 1,
			0,
		};
		std::vector<uint16_t> indices = std::vector<uint16_t>(std::begin(indicesArr), std::end(indicesArr));

		make(vertices, indices);
	}

	// Hard coded Pyramid that will be used mostly for debug drawing
	Pyramid::Pyramid()
	{
		constexpr glm::vec3 scale = glm::vec3(1.0f);
		
		std::vector<PrimitiveVertex> vertices;
		vertices.resize(5);

		vertices[0].position = { -scale.x , 0.0f ,  scale.z };
		vertices[1].position = { -scale.x , 0.0f , -scale.z };
		vertices[2].position = { scale.x,  0.0f ,  -scale.z };
		vertices[3].position = { scale.x , 0.0f ,  scale.z };
		vertices[4].position = { 0.0f, scale.y ,  0.0f };

		std::vector<uint16_t> indices;
		indices.resize(18);
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 3;
		indices[4] = 2;
		indices[5] = 3;
		indices[6] = 0;
		indices[7] = 1;
		indices[8] = 4;
		indices[9] = 1;
		indices[10] = 2;
		indices[11] = 4;
		indices[12] = 2;
		indices[13] = 3;
		indices[14] = 4;
		indices[15] = 3;
		indices[16] = 0;
		indices[17] = 4;
		
		make(vertices, indices);
	}

	// Hard coded Sphere that will be used mostly for debug drawing
	Sphere::Sphere()
	{
		std::vector<PrimitiveVertex> vertices;
		std::vector<uint16_t> indices;

		constexpr float latitudeBands = 12;
		constexpr float longitudeBands = 12;

		for (float latitude = 0.0f; latitude <= latitudeBands; latitude++)
		{
			const float theta = latitude * static_cast<float>(3.141592 / latitudeBands);
			const float sinTheta = glm::sin(theta);
			const float cosTheta = glm::cos(theta);

			for (float longitude = 0.0f; longitude <= longitudeBands; longitude++)
			{
				constexpr float radius = 0.5f;
				const float phi = longitude * 2.f * static_cast<float>(3.141592 / longitudeBands);
				const float sinPhi = glm::sin(phi);
				const float cosPhi = glm::cos(phi);

				PrimitiveVertex vertex;
				vertex.normal = { cosPhi * sinTheta, cosTheta, sinPhi * sinTheta };
				vertex.position = { radius * vertex.normal.x, radius * vertex.normal.y, radius * vertex.normal.z };
				vertices.push_back(vertex);
			}
		}

		for (uint32_t latitude = 0; latitude < static_cast<uint32_t>(latitudeBands); latitude++)
		{
			for (uint32_t longitude = 0; longitude <  static_cast<uint32_t>(longitudeBands); longitude++)
			{
				const uint32_t first = (latitude *  (static_cast<uint32_t>(longitudeBands + 1)) + longitude);
				const uint32_t second = first +  static_cast<uint32_t>(longitudeBands + 1);

				indices.push_back(first);
				indices.push_back(second);
				indices.push_back(first + 1);
				indices.push_back(second);
				indices.push_back(second + 1);
				indices.push_back(first + 1);
			}
		}

		make(vertices, indices);
	}

	// Hard coded Quad that will be used mostly for debug drawing and billboards
	Quad::Quad()
	{
		constexpr float scale = 1.0f;
		
		std::vector<PrimitiveVertex> vertices;
		vertices.resize(4);
		vertices[0].position = { -scale, -scale, 0.0f};
		vertices[1].position = { scale, -scale, 0.0f};
		vertices[2].position = { scale, scale, 0.0f};
		vertices[3].position = { -scale, scale, 0.0f};
	
		std::vector<uint16_t> indices;
		indices.resize(6);
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 2;
		indices[4] = 3;
		indices[5] = 0;

		make(vertices, indices);
	}

	// Hard coded Line that will be used mostly for debug drawing
	Line::Line()
	{
		std::vector<PrimitiveVertex> vertices;
		vertices.resize(2);
		vertices[0].position = glm::vec3(0.0f, 0.0f, 0.0f);
		vertices[1].position = glm::vec3(1.0f, 0.0f, 0.0f);

		std::vector<uint16_t> indices;
		indices.resize(2);
		indices[0] = 0;
		indices[1] = 1;

		make(vertices, indices);
	}

	// Hard coded 2x2 Grid that will be used mostly for debug drawing
	Grid::Grid()
	{
		std::vector<PrimitiveVertex> vertices;
		vertices.resize(9);
		vertices[0].position = glm::vec3(0.0f, 0.0f, 0.0f);
		vertices[1].position = glm::vec3(1.0f, 0.0f, 0.0f);
		vertices[2].position = glm::vec3(1.0f, 1.0f, 0.0f);
		vertices[3].position = glm::vec3(0.0f, 1.0f, 0.0f);
		vertices[4].position = glm::vec3(-1.0f, 1.0f, 0.0f);
		vertices[5].position = glm::vec3(-1.0f, 0.0f, 0.0f);
		vertices[6].position = glm::vec3(-1.0f, -1.0f, 0.0f);
		vertices[7].position = glm::vec3(0.0f, -1.0f, 0.0f);
		vertices[8].position = glm::vec3(1.0f, -1.0f, 0.0f);

		std::vector<uint16_t> indices;
		indices.resize(16);
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 3;
		indices[4] = 0;
		indices[5] = 3;
		indices[6] = 4;
		indices[7] = 5;
		indices[8] = 0;
		indices[9] = 5;
		indices[10] = 6;
		indices[11] = 7;
		indices[12] = 0;
		indices[13] = 7;
		indices[14] = 8;
		indices[15] = 1;

		make(vertices, indices);
	}

	// Hard coded Circle that will be used mostly for debug drawing
	Circle::Circle()
	{
		constexpr float radius = 0.5f;
		
		std::vector<PrimitiveVertex> vertices;
		std::vector<uint16_t> indices;

		int vertexCount = 20;

		// Size our vector so it can hold all the requested vertices plus our center one
		vertices.resize(static_cast<size_t>(vertexCount + 1));

		// Calculate the angle we'll need to rotate by for each iteration (* (PI / 180) to convert it into radians)
		double segRotationAngle = (360.0 / vertexCount) * (3.14159265 / 180);

		// We need an initial vertex in the center as a point for all of the triangles we'll generate
		vertices[0].position = glm::vec3(0.0f);

		// Set the starting point for the initial generated vertex. We'll be rotating this point around the origin in the loop
		double startX = 0.0 - radius;
		double startY = 0.0;

		for (int i = 1; i < vertexCount + 1; i++)
		{
			// Calculate the angle to rotate the starting point around the origin
			double finalSegRotationAngle = (i * segRotationAngle);

			// Rotate the start point around the origin (0, 0) by the finalSegRotationAngle (see https://en.wikipedia.org/wiki/Rotation_(mathematics) section on two dimensional rotation)
			vertices[i].position.x = static_cast<float>(cos(finalSegRotationAngle) * startX - sin(finalSegRotationAngle) * startY);
			vertices[i].position.y = static_cast<float>(cos(finalSegRotationAngle) * startY + sin(finalSegRotationAngle) * startX);

			// Add generated point index
			indices.push_back(i);

			// Add next point index (with logic to wrap around when we reach the start)
			int index = (i + 1) % vertexCount;
			if (index == 0)
			{
				index = vertexCount;
			}
		}

		indices.push_back(1);

		make(vertices, indices);
	}
}