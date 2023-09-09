#include "shader.h"

namespace jtg {

	Shader::Shader(std::string vertPath, std::string fragPath) {

		int success;
		char log[512];

		std::string vertSource = simpleRead(vertPath);

		std::string fragSource = simpleRead(fragPath);

		id = compProgram(vertSource.c_str(), fragSource.c_str(), &success, log);
	}

	void Shader::use() const
	{
		glUseProgram(id);
	}

	void Shader::transform(glm::mat4 mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(id, "trans"), 1, GL_FALSE, &mat[0][0]);
	}

	unsigned int Shader::compProgram(const char* vertSource, const char* fragSource, int* success, char* log) {

		unsigned int id, vertId, fragId;

		vertId = compShader(vertSource, GL_VERTEX_SHADER, success, log);
		fragId = compShader(fragSource, GL_FRAGMENT_SHADER, success, log);

		id = glCreateProgram();
		glAttachShader(id, vertId);
		glAttachShader(id, fragId);
		glLinkProgram(id);

		glDeleteShader(vertId);
		glDeleteShader(fragId);

		glGetProgramiv(id, GL_LINK_STATUS, success);

		if (!*success) {
			glGetProgramInfoLog(id, 512, NULL, log);
			std::cout << "program link fail\n" << log << std::endl;
		}

		// bind uniform block Cam to shader for space transforms
		unsigned int projIndex = glGetUniformBlockIndex(id, "Cam");
		glUniformBlockBinding(id, projIndex, 0);

		return id;
	}

	unsigned int Shader::compShader(const char* source, int type, int* success, char* log) {

		unsigned int id = glCreateShader(type);
		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);
		glGetShaderiv(id, GL_COMPILE_STATUS, success);

		if (!*success) {
			glGetShaderInfoLog(id, 512, NULL, log);
			std::cout << "shaderc comp fail\n" << log << std::endl;
		}

		return id;
	}


	std::string Shader::simpleRead(std::string path) {

		std::string str;

		try {

			std::ifstream file;

			file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			file.open(path);
			std::stringstream strStream;
			strStream << file.rdbuf();
			file.close();

			str = strStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "shader file read error" << std::endl;
		}

		return str;
	}

}