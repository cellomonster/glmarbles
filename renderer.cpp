#include "renderer.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

namespace jtg {

	void Renderer::setMesh(const Mesh& newMesh)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 
			sizeof(float) * newMesh.verts.size(), 
			&newMesh.verts.front(),
			GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
			sizeof(int) * newMesh.tris.size(), 
			&newMesh.tris.front(),
			GL_STATIC_DRAW);

		mesh = newMesh;
	}

	Renderer::Renderer()
	{
		shader = Shader("texture.vs", "texture.fs");

		int width, height, nrChannels;
		unsigned char* texData = stbi_load("test.png", &width, &height, &nrChannels, 0);

		glGenVertexArrays(1, &vao);

		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		glGenTextures(1, &tex);


		glBindVertexArray(vao);

		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		unsigned long stride = 8 * sizeof(float);

		// position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);

		// normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// uvs
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		stbi_image_free(texData);
	}

	void Renderer::renderAt(const glm::mat4& mat) const {

		shader.use();
		shader.transform(mat);

		glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, mesh.tris.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Renderer::render() const {
		renderAt(trans->mat);
	}
} 