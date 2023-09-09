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

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(mainWindow, onFramebufferSize);

	// init game

	jtg::Camera cam;
	cam.recalculateMatrix();
	cam.orient(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1));

	jtg::Transform trans;
	jtg::Renderer test;

	// printf("mat: %s\n", glm::to_string(trans.mat));

	while (!glfwWindowShouldClose(mainWindow))
	{
		glClearColor(0.5f, 0.5f, 1, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		t += .01;

		trans.rot = jtg::Transform::eulerToQuat(glm::vec3(t, 0, 0));
		trans.recalculateMatrix();

		// draw
		cam.track(trans.pos);
		cam.updateUbo();
		test.renderAt(trans.mat);

		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}