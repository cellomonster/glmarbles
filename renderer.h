#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "transform.h"
#include "shader.h"
#include "mesh.h"

namespace jtg {

	class Renderer
	{
	public:
		Renderer();

		Transform *trans;
		Shader shader;

		void setMesh(const Mesh& mesh);
		void render() const;
		void renderAt(const glm::mat4& pos) const;

	private:

		Mesh mesh;

		unsigned int vbo = 0;
		unsigned int vao = 0;
		unsigned int ebo = 0;
		unsigned int tex = 0;
	};
};


