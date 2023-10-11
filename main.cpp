#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtx/string_cast.hpp>

#include "camera.h"
#include "dynamics.h"
#include "transform.h"
#include "shader.h"
#include "renderer.h"
#include "mesh.h"

jtg::dynamics::World world;
std::vector<jtg::dynamics::Contact> contacts;

struct Block {
	jtg::Transform trans;
	jtg::Renderer rend;
	jtg::dynamics::BoxCollider col;

	Block() {

		rend.trans = &trans;
		col.trans = &trans;

		world.boxes.push_back(&col);
	}

	void setSize(vec3 size) {
		rend.setMesh(jtg::blockMesh(size));
		col.size = size;
	}
};

struct Marble {
	jtg::Transform trans;
	jtg::Renderer rend;
	jtg::dynamics::SphereCollider col;
	jtg::dynamics::Body body;

	Marble() {

		rend.trans = &trans;
		col.trans = &trans;

		body = jtg::dynamics::Body();
		body.mass = 1;

		col.body = &body;
		col.body->trans = &trans;

		float rad = .5f;

		rend.setMesh(jtg::polyhedronMesh(.5f));
		col.radius = rad;

		world.spheres.push_back(&col);
		world.bodies.push_back(&body);
	}
};


void OnFramebufferSize(GLFWwindow* window, int width, int height)
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

	glfwSetFramebufferSizeCallback(mainWindow, OnFramebufferSize);

	// init game

	jtg::Camera cam;
	cam.recalc();
	cam.orient(glm::vec3(0, 1, 5), glm::vec3(0, 0, -1));

	Block block;
	block.setSize(glm::vec3(3, 1, 3));
	block.trans.pos = glm::vec3(0, 0, 0);
	block.trans.rot = jtg::Transform::eulerToQuat(vec3(-30, 0, 0));
	block.trans.recalc();

	Block b2;
	b2.setSize(glm::vec3(3, 1, 3));
	b2.trans.pos = glm::vec3(-3, -3, 0);
	b2.trans.rot = jtg::Transform::eulerToQuat(vec3(30, 0, 0));
	b2.trans.recalc();

	/*Block b3;
	b3.setSize(glm::vec3(3, 1, 3));
	b3.trans.pos = glm::vec3(3, -3, 0);
	b3.trans.rot = jtg::Transform::eulerToQuat(vec3(0, 0, 30));
	b3.trans.recalc();*/

	Marble marble;
	marble.trans.pos = glm::vec3(0, 3.0f, 0);
	marble.trans.recalc();

	while (!glfwWindowShouldClose(mainWindow))
	{
		t += 0.05f;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 1);

		glfwPollEvents();

		// draw

		cam.updateUbo();

		Collide(contacts, world);
		Simulate(contacts, world, 0.01f);
		contacts.clear();

		block.rend.render();
		b2.rend.render();
		//b3.rend.render()
		marble.rend.render();

		glfwSwapBuffers(mainWindow);
	}

	glfwTerminate();

	return 0;
}