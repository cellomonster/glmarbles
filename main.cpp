#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtx/string_cast.hpp>

#include "camera.h"
#include "transform.h"
#include "shader.h"
#include "renderer.h"

void onFramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


float t;


int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); mac only

	GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "Learn openGL", NULL, NULL);
	if (mainWindow == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mainWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 800);


	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(mainWindow, onFramebufferSize);

	// init game

	jtg::Camera cam;
	cam.recalculateMatrix();
	cam.orient(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1));


	jtg::Mesh cube;

	cube.verts = {
	    //pos  , color  , uv
		0, 0, 0, 1, 1, 1, 0, 0,
		1, 0, 0, 1, 1, 1, 1, 0,
		1, 1, 0, 1, 1, 1, 1, 1,
		0, 1, 0, 1, 1, 1, 0, 1,

		0, 0, 1, 1, 1, 1, 0, 0,
		1, 0, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 0, 1,
	};

	cube.tris = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
	};

	jtg::Transform trans;
	trans.pos = glm::vec3(0, 0, -5);
	trans.recalculateMatrix();

	jtg::Renderer test;
	test.setMesh(cube);

	// printf("mat: %s\n", glm::to_string(trans.mat));

	while (!glfwWindowShouldClose(mainWindow))
	{
		glClearColor(0.5f, 0.5f, 1, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw
		cam.track(trans.pos);
		cam.updateUbo();

		t += 0.001;

		trans.rot = jtg::Transform::eulerToQuat(glm::vec3(0, sin(t) * 45, cos(t) * 45));
		trans.recalculateMatrix();

		test.renderAt(trans.mat);

		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}