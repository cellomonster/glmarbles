#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "constants.h"
#include "transform.h"
#include "shader.h"

namespace jtg {

	class Camera: public Transform
	{
	public:
		Camera();
		
		glm::vec3 forw = glm::vec3(0, 0, -1);
		glm::mat4 proj = glm::mat4(1.0);

		void orient(glm::vec3 pos, glm::vec3 forw);
		void track(glm::vec3 target);

		void updateUbo();

	private:
		unsigned int ubo;

	};

}