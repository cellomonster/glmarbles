#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "transform.h"
#include "shader.h"

namespace jtg {
	class Renderer
	{
	public:
		Renderer();

		void renderAt(glm::mat4 pos) const;

	private:

		Shader shader;

		unsigned int vbo = 0;
		unsigned int vao = 0;
		unsigned int ebo = 0;
		unsigned int tex = 0;

		
	};
};

