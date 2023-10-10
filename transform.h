#pragma once


#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace jtg {

	class Transform {

	public:
		static glm::quat eulerToQuat(glm::vec3 euler);

		glm::vec3 pivot = glm::vec3(0.0);
		glm::vec3 pos = glm::vec3(0.0);
		glm::quat rot = glm::quat(1.0, 0.0, 0.0, 0.0);
		glm::vec3 scale = glm::vec3(1.0);

		void recalc();

		glm::mat4 mat = glm::mat4(1.0);

	private:
		void translate(glm::vec3 trans);
		void rotate(glm::quat rot);
		void scaleBy(glm::vec3 scale);
	};
};