#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "transform.h"
#include "shader.h"

namespace jtg {

	struct Mesh {
		std::vector<float> verts;
		std::vector<unsigned int> tris;
	};

	class Renderer
	{
	public:
		Renderer();

		void setMesh(const Mesh& mesh) const;
		void renderAt(const glm::mat4& pos) const;

	private:

		Shader shader;

		unsigned int vbo = 0;
		unsigned int vao = 0;
		unsigned int ebo = 0;
		unsigned int tex = 0;

		
	};
};

