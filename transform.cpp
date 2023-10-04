#include "transform.h"

namespace jtg {

	inline float sqr(float f) {
		return f * f;
	}

	void Transform::recalc()
	{
		//right = glm::normalize(glm::cross(worldUp, forw));
		//up = glm::normalize(glm::cross(forw, right));

		mat = glm::mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);

		translate(pos);
		scaleBy(scale);
		rotate(rot);
		translate(-pivot);
	}

	void Transform::translate(glm::vec3 trans) {

		glm::mat4 transMat = glm::mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			trans.x, trans.y, trans.z, 1
		);

		mat *= transMat;
	}

	glm::quat Transform::eulerToQuat(glm::vec3 a) {

		a *= M_PI / 180.0f;

		float z = a.z / 2.0f;
		float y = a.y / 2.0f;
		float x = a.x / 2.0f;

		float cz = cos(z);
		float sz = sin(z);
		float cy = cos(y);
		float sy = sin(y);
		float cx = cos(x);
		float sx = sin(x);


		return glm::quat(
			cz * cy * cx + sz * sy * sx,
			sz * cy * cx - cz * sy * sx,
			cz * sy * cx + sz * cy * sx,
			cz * cy * sx - sz * sy * cx
		);
	}

	void Transform::rotate(glm::quat rot) {

		glm::mat4 rotationMatrix = glm::mat4(1.0f);

		const float w = rot.w;
		const float x = rot.x;
		const float y = rot.y;
		const float z = rot.z;

		rotationMatrix[0][0] = 1.0f - 2.0f * (y * y + z * z);
		rotationMatrix[0][1] = 2.0f * (x * y - z * w);
		rotationMatrix[0][2] = 2.0f * (x * z + y * w);

		rotationMatrix[1][0] = 2.0f * (x * y + z * w);
		rotationMatrix[1][1] = 1.0f - 2.0f * (x * x + z * z);
		rotationMatrix[1][2] = 2.0f * (y * z - x * w);

		rotationMatrix[2][0] = 2.0f * (x * z - y * w);
		rotationMatrix[2][1] = 2.0f * (y * z + x * w);
		rotationMatrix[2][2] = 1.0f - 2.0f * (x * x + y * y);

		mat *= rotationMatrix;
	}

	void Transform::scaleBy(glm::vec3 scale) {

		glm::mat4 scaleMat = glm::mat4(
			scale.x, 0, 0, 0,
			0, scale.y, 0, 0,
			0, 0, scale.z, 0,
			0, 0, 0,       1
		);

		mat *= scaleMat;
	}

}