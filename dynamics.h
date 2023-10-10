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
			mat3 moment;

			glm::vec3 vel;
			vec3 angVel;
		};

		struct BoxCollider
		{
			Transform* trans;
			vec3 size;

			Body* body;
		};

		struct SphereCollider
		{
			Transform* trans;
			float radius;

			Body* body;
		};

		struct World
		{
			std::vector<BoxCollider> boxes;
			std::vector<SphereCollider> spheres;
			std::vector<Body> bodies;
		};

		struct Contact
		{
			Body* bodyA, bodyB;
			vec3 point;
			vec3 norm;
		};

		void Collide(std::vector<Contact> contacts, const World& world);
		void Simulate(const std::vector<Contact>& contacts, World& world, float deltaTime);

	}
}
