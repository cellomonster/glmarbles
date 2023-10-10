#pragma once
#include <vector>

#include "transform.h"

using namespace glm;

namespace jtg
{
	namespace dynamics
	{
		// referencing:
		// https://rasmusbarr.github.io/blog/dod-physics.html

		struct Body
		{
			Transform* trans;

			float mass;
			float moment;

			vec3 vel;
			vec3 angVel;
		};

		struct Boxes
		{
			std::vector<vec3> sizes;
			std::vector<Body> bodies;
		};

		struct Spheres
		{
			std::vector<float> radii;
			std::vector<Body> bodies;
		};

		struct Colliders
		{
			Boxes boxes;
			Spheres spheres;
		};

		struct Contact
		{
			Body bodyA, bodyB;
			vec3 point, norm;
		};

		void Collide(std::vector<Contact> contacts, std::vector<Body> bodies, Colliders colliders);
		void Simulate(std::vector<Contact> contacts, float deltaTime);

	}
}
