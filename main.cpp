#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtx/string_cast.hpp>

#include "camera.h"
#include "transform.h"
#include "shader.h"
#include "renderer.h"
#include "mesh.h"
#include "collider.h"

void onFramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

float t;
glm::vec2 winSize = glm::vec2(800, 800);

struct Actor {
	jtg::Renderer rend;
	jtg::Transform trans;
};

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); mac only

	GLFWwindow* mainWindow = glfwCreateWindow(winSize.x, winSize.y, "Learn openGL", NULL, NULL);
	if (mainWindow == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mainWindow);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, winSize.x, winSize.y);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(mainWindow, onFramebufferSize);

	// init game

	jtg::Camera cam;
	cam.recalc();
	cam.orient(glm::vec3(0, 0, 3), glm::vec3(0, 0, -1));

	Actor block;
	block.rend.setMesh(jtg::blockMesh(1, 1, 1));
	block.trans.pivot = glm::vec3(-.5, -.5, -.5);
	jtg::BoxCol blockCol;
	blockCol.size = glm::vec3(1, 1, 1);
	blockCol.trans = &block.trans;

	Actor marble;
	marble.rend.setMesh(jtg::polyhedronMesh(1));
	jtg::SphereCol marbleCol;
	marbleCol.trans = &marble.trans;

	// printf("mat: %s\n", glm::to_string(trans.mat));

	while (!glfwWindowShouldClose(mainWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);

		glfwPollEvents();

		// draw

		t += 0.01f;

		marble.trans.rot = jtg::Transform::eulerToQuat(glm::vec3(0, t * 50, 0));
		marble.trans.pos = glm::vec3(cos(t), sin(t), 0);
		marble.trans.recalc();
		marble.rend.renderAt(marble.trans.mat);

		block.trans.rot = jtg::Transform::eulerToQuat(glm::vec3(45, t * 50, 45));
		block.trans.pos = glm::vec3(sin(t), cos(t), -0.2);
		block.trans.recalc();
		block.rend.renderAt(block.trans.mat);

		// cam.track(.pos);
		cam.updateUbo();

		glm::vec3 col = jtg::SphereOnBox(marbleCol, blockCol);

		if (col != glm::vec3(0, 0, 0)) {
			std::cout << glm::to_string(col) << std::endl;
		}

		glfwSwapBuffers(mainWindow);
	}

	glfwTerminate();

	return 0;
}