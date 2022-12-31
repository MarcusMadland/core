

#include "crpch.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "math.hpp"
#include "defines.hpp"
#include "graphics/camera.hpp"

namespace Core::Math
{
	Transform DecomposeMatrix(const glm::mat4& matrix)
	{
		Transform result;
		
		glm::mat4 Local(matrix);

		// Normalize the matrix
		if (glm::epsilonEqual(Local[3][3], static_cast<float>(0),
			glm::epsilon<float>()))
		{
			return Transform();
		}
		
		result.position = glm::vec3(Local[3]);
		Local[3] = glm::vec4(0, 0, 0, Local[3].w);
		
		for (int i = 0; i < 3; i++)
			result.scale[i] = glm::length(glm::vec3(matrix[i]));

		const glm::mat3 rotMatrix(
			glm::vec3(matrix[0]) / result.scale[0],
			glm::vec3(matrix[1]) / result.scale[1],
			glm::vec3(matrix[2]) / result.scale[2]);
		result.rotation = glm::quat(rotMatrix);

		return result;
	}

	glm::mat4 ComposeMatrix(const Transform& transform)
	{
		// Compose translation matrix by translating from vec3
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), transform.position);

		// Compose rotation matrix by converting the euler vec3 to radians and then 
		// over to quaternion. From quat we can easily convert to a rotation matrix
		glm::mat4 rotation = glm::toMat4(transform.rotation);

		// Compose scale matrix by scaling from vec3
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.scale);

		// Multiply all transformation matrices and return result
		return translation * rotation * scale;
	}

	glm::quat FindLookAtRotation(const glm::vec3& start, const glm::vec3& target)
	{
		return RotationFromXVector(target - start);
	}

	glm::quat RotationFromXVector(const glm::vec3& direction)
	{
		glm::vec3 const NewX = glm::normalize(direction);

		// try to use up if possible
		glm::vec3 const UpVector = (glm::abs(NewX.y) < (1.f - CORE_SMALL_NUMBER)) ? glm::vec3(0, 1.0f, 0.f) : glm::vec3(1.f, 0, 0.f);

		const glm::vec3 NewY = glm::normalize(Exp(UpVector, NewX));
		const glm::vec3 NewZ = Exp(NewX, NewY);

		return glm::quat(glm::mat4(glm::mat3(NewX, NewY, NewZ)));
	}

	glm::vec3 WorldToScreenSpace(const glm::vec3& worldSpace, const Ref<Camera>& camera)
	{
		// @todo
		return glm::vec3();
	}

	glm::vec3 ScreenToWorldSpace(const glm::vec2& screenSpace, const Ref<Camera>& camera, const float& depth )
	{
		glm::vec4 viewport = { 0,0,camera->GetParams().width, camera->GetParams().height};
		glm::vec3 pos = glm::unProject({ screenSpace.x,screenSpace.y,1 }, camera->GetViewMatrix(), camera->GetProjectionMatrix(), viewport);
		pos = glm::normalize(pos - camera->GetParams().position) * depth + camera->GetParams().position;

		return pos;
	}

	glm::vec3 Exp(const glm::vec3& a, const glm::vec3& b)
	{
		const glm::vec3 result = glm::vec3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
		
		return result;
	}

	glm::quat ToQuat(const float& pitch, const float& yaw, const float& roll)
	{
		const glm::quat result = glm::quat(
			glm::radians(glm::vec3(pitch, yaw, roll)));
		return result;
	}

	glm::quat ToQuat(const glm::vec3& euler)
	{
		return ToQuat(euler.x, euler.y, euler.z);
	}
	
	bool InRange(const float& value, const float& min, const float& max)
	{
		return value > min && value < max;
	}

	float Interp(const float& current, const float& target,
		const float& deltaTime, const float& speed)
	{
		const float difference = target - current;
		const float move = deltaTime * speed;

		if (difference > deltaTime)
		{
			return current + move;
		}
		if (difference < -deltaTime)
		{
			return current - move;
		}

		return target;
	}
	glm::vec3 Interp(const glm::vec3& current, const glm::vec3& target,
		const float& deltaTime, const float& speed)
	{
		const glm::vec3 result = glm::vec3(
			Interp(current.x, target.x, deltaTime, speed), 
			Interp(current.y, target.y, deltaTime, speed),
			Interp(current.z, target.z, deltaTime, speed));
		return result;
	}
}