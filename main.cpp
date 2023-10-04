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


struct Block {
	jtg::Transform trans;
	jtg::Renderer rend;
	jtg::BoxCol col;

	Block() : trans(), rend(), col() {
		trans = jtg::Transform();

		rend.trans = trans;
		col.trans = trans;
	}

	inline void setSize(glm::vec3 size) {
		rend.setMesh(jtg::blockMesh(size));
		col.size = size;
	}
};

struct Marble {
	jtg::Transform trans;
	jtg::Renderer rend;
	jtg::SphereCol col;
	jtg::Body body;

	Marble() {
		rend.trans = trans;
		col.trans = trans;
		body.trans = trans;

		float rad = .5f;

		rend.setMesh(jtg::polyhedronMesh(.5f));
		col.rad = rad;
	}
};


void onFramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

float t;
glm::vec2 winSize = glm::vec2(800, 800);

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

	Block block;
	block.setSize(glm::vec3(5, 2, 5));
	block.trans.pos = glm::vec3(0, -1, 0);
	block.trans.recalc();

	Marble marble;
	marble.trans.pos = glm::vec3(0, .5f, 0);
	marble.trans.recalc();

	while (!glfwWindowShouldClose(mainWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);

		glfwPollEvents();

		// draw

		cam.updateUbo();

		t += 0.05f;

		block.trans.rot = jtg::Transform::eulerToQuat(glm::vec3(0, t, 0));
		block.trans.recalc();
		block.rend.render();

		//bool sphereColliding = jtg::SphereOnBox(marble.col, block.col);

		//if (sphereColliding) {
		//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//}
		//else {
		//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//}

		

		glfwSwapBuffers(mainWindow);
	}

	glfwTerminate();

	return 0;
}