#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace jtg {


	class Shader {
	public:
		unsigned int id = 0;

		Shader(std::string vertexPath = "vert.vs", std::string fragmentPath = "frag.fs");

		void use() const;
		void transform(glm::mat4 mat) const;

	private:
		unsigned int compProgram(const char* vertSource, const char* fragSource, int* success, char* log);
		unsigned int compShader(const char* source, int type, int* success, char* log);
		std::string simpleRead(std::string path);


	};

};