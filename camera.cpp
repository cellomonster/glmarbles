#include "camera.h"

namespace jtg {

	Camera::Camera() {

		proj = glm::perspective(90.0, 1.0, 0.01, 100.0);

		glGenBuffers(1, &ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBufferData(GL_UNIFORM_BUFFER, 128, NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(glm::mat4));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void Camera::orient(glm::vec3 pos, glm::vec3 forw)
	{
		this->pos = pos;
		this->forw = forw;

		mat = glm::lookAt(pos, forw, worldUp);
	}

	void Camera::track(glm::vec3 target)
	{
		orient(pos, glm::normalize(target - pos));
	}

	void Camera::updateUbo() {
		int size = sizeof(glm::mat4);

		glBindBuffer(GL_UNIFORM_BUFFER, ubo);

		glBufferData(GL_UNIFORM_BUFFER, 2 * size, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, size, glm::value_ptr(proj));
		glBufferSubData(GL_UNIFORM_BUFFER, size, size, glm::value_ptr(mat));

		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

}