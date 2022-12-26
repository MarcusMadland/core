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

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>

#include "math.hpp"
#include "defines.hpp"
#include "system/camera.hpp"
#include "debug/logger.hpp"

namespace Core::Math
{
	Transform DecomposeMatrix(const glm::mat4& matrix)
	{
		glm::vec3 translation, scale, rotation;

		// Lets start with translation: it is equal to the elements of the last column, we get these and then 0 out that column
		glm::mat4 Local(matrix);

		// Normalize the matrix
		if (glm::epsilonEqual(Local[3][3], (float)(0), glm::epsilon<float>()))
			return Transform();

		translation = glm::vec3(Local[3]);
		Local[3] = glm::vec4(0, 0, 0, Local[3].w);

		// Now onto rotation: Calculate the polar decomposition of Local to obtain rotation R and stretch S matrices:
		// Local = RS

		for (int i = 0; i < 3; i++)
			scale[i] = glm::length(glm::vec3(matrix[i]));

		const glm::mat3 rotMatrix(glm::vec3(matrix[0]) / scale[0], glm::vec3(matrix[1]) / scale[1], glm::vec3(matrix[2]) / scale[2]);
		rotation = RotationFromQuat(glm::quat(rotMatrix));

		return Transform(translation, rotation, scale);
	}

	glm::mat4 ComposeMatrix(const Transform& transform)
	{
		// Compose translation matrix by translating from vec3
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), transform.position);

		// Compose rotation matrix by converting the euler vec3 to radians and then 
		// over to quaternion. From quat we can easily convert to a rotation matrix
		glm::mat4 rotation = glm::toMat4(QuatFromRotation(transform.rotation));

		// Compose scale matrix by scaling from vec3
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.scale);

		// Multiply all transformation matrices and return result
		return translation * rotation * scale;
	}

	glm::vec3 FindLookAtRotation(const glm::vec3& start, const glm::vec3& target)
	{
		return RotationFromXVector(target - start);
	}

	glm::vec3 RotationFromXVector(const glm::vec3& direction)
	{
		return RotationFromQuat(MatrixFromXVector(direction));
	}

	glm::mat4 MatrixFromXVector(const glm::vec3& direction)
	{
		// Work on this, now think about 3d coords (y up, not z)

		glm::vec3 const NewX = glm::normalize(direction);

		// try to use up if possible
		glm::vec3 const UpVector = (glm::abs(NewX.y) < (1.f - CORE_SMALL_NUMBER)) ? glm::vec3(0, 1.0f, 0.f) : glm::vec3(0, 0, 1.f);

		const glm::vec3 NewY = glm::normalize(Caret(UpVector, NewX));
		const glm::vec3 NewZ = Caret(NewX, NewY);

		return glm::mat4(glm::mat3(NewX, NewY, NewZ));
	}

	glm::vec3 RotationFromQuat(const glm::quat& quat)
	{
		const double SingularityTest = quat.z * quat.x - quat.w * quat.y;
		const double YawY = 2.0 * (quat.w * quat.z + quat.x * quat.y);
		const double YawX = (1.0 - 2.0 * (Square(quat.y) + Square(quat.z)));

		const double SINGULARITY_THRESHOLD = 0.4999995;
		const double RAD_TO_DEG = (180.0 / CORE_PI);
		double Pitch, Yaw, Roll;

		if (SingularityTest < -SINGULARITY_THRESHOLD)
		{
			Pitch = -90.0;
			Yaw = (atan2(YawY, YawX) * RAD_TO_DEG);
			Roll = NormalizeAxis(-Yaw - (2.0 * atan2(quat.x, quat.w) * RAD_TO_DEG));
		}
		else if (SingularityTest > SINGULARITY_THRESHOLD)
		{
			Pitch = 90.0;
			Yaw = (atan2(YawY, YawX) * RAD_TO_DEG);
			Roll = NormalizeAxis(Yaw - (2.0 * atan2(quat.x, quat.w) * RAD_TO_DEG));
		}
		else
		{
			Pitch = (asin(2.0 * SingularityTest) * RAD_TO_DEG); // Note: not FastAsin like float implementation
			Yaw = (atan2(YawY, YawX) * RAD_TO_DEG);
			Roll = (atan2(-2.0 * (quat.w * quat.x + quat.y * quat.z), (1.0 - 2.0 * (Square(quat.x) + Square(quat.y)))) * RAD_TO_DEG);
		}

		glm::vec3 RotatorFromQuat = glm::vec3(Pitch, Yaw, Roll);

		return RotatorFromQuat;
	}

	glm::quat QuatFromRotation(const glm::vec3& rotation)
	{
		const double DEG_TO_RAD = CORE_PI / (180.0);
		const double RADS_DIVIDED_BY_2 = DEG_TO_RAD / 2.0;
		double SP, SY, SR;
		double CP, CY, CR;

		const double PitchNoWinding = glm::mod(rotation.x, 360.0f); // fmod?
		const double YawNoWinding = glm::mod(rotation.y, 360.0f); // fmod?
		const double RollNoWinding = glm::mod(rotation.z, 360.0f);// fmod?

		SinCos(&SP, &CP, PitchNoWinding * RADS_DIVIDED_BY_2);
		SinCos(&SY, &CY, YawNoWinding * RADS_DIVIDED_BY_2);
		SinCos(&SR, &CR, RollNoWinding * RADS_DIVIDED_BY_2);

		glm::quat RotationQuat;
		RotationQuat.w = CR * CP * CY + SR * SP * SY;
		RotationQuat.x = CR * SP * SY - SR * CP * CY;
		RotationQuat.y = -CR * SP * CY - SR * CP * SY;
		RotationQuat.z = CR * CP * SY - SR * SP * CY;

		return RotationQuat;
	}

	glm::vec3 WorldToScreenSpace(const glm::vec3& worldSpace, const Ref<Camera>& camera)
	{
		// @todo
		return glm::vec3();
	}

	glm::vec3 ScreenToWorldSpace(const glm::vec2& screenSpace, const Ref<Camera>& camera, const float& depth /* = 10.0f */)
	{
		glm::vec4 viewport = { 0,0,camera->GetParams().width, camera->GetParams().height};
		glm::vec3 pos = glm::unProject({ screenSpace.x,screenSpace.y,1 }, camera->GetViewMatrix(), camera->GetProjectionMatrix(), viewport);
		pos = glm::normalize(pos - camera->GetParams().position) * depth + camera->GetParams().position;

		return pos;
	}





	glm::vec3 Caret(const glm::vec3& a, const glm::vec3& b)
	{
		return glm::vec3
			(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
			);
	}

	float Square(const float& a)
	{
		return a * a;
	}

	void SinCos(double* ScalarSin, double* ScalarCos, double Value)
	{
		// No approximations for doubles
		*ScalarSin = sin(Value);
		*ScalarCos = cos(Value);
	}

	double NormalizeAxis(double angle)
	{
		// returns Angle in the range [0,360)
		angle = ClampAxis(angle);

		if (angle > (double)180.0)
		{
			// shift to (-180,180]
			angle -= (double)360.0;
		}

		return angle;
	}

	double ClampAxis(double angle)
	{
		// returns Angle in the range (-360,360)
		angle = glm::mod((float)angle, 360.0f); // fmod?
	
		if (angle < (double)0.0)
		{
			// shift to [0,360) range
			angle += (double)360.0;
		}

		return angle;
	}

	bool InRange(float value, float min, float max)
	{
		return value > min && value < max;
	}

	float Interp(float current, float target, float deltaTime, float speed)
	{
		// @todo
		return 0.0f;
	}
}