#include "dynamics.h"
#include <glm/gtx/projection.hpp>

using namespace jtg;
using namespace jtg::dynamics;

Body staticBody;


vec3 ClampToBox(const vec3& pos, const vec3& size) {
	const vec3 extents = size * 0.5f;

	vec3 p = pos;

	p.x = clamp(p.x, -extents.x, extents.x);
	p.y = clamp(p.y, -extents.y, extents.y);
	p.z = clamp(p.z, -extents.z, extents.z);

	return p;
}


bool SphereOnBox(const SphereCollider& sphere, const BoxCollider& box, Contact& contact) {

	const vec3 sphereLocal = vec3((inverse(box.trans->mat) * sphere.trans->mat)[3]);
	const vec3 closest = ClampToBox(sphereLocal, box.size);

	const bool areTouching = distance(closest, sphereLocal) <= sphere.radius;

	if (areTouching)
	{
		contact.point = closest;
		contact.norm = normalize(sphere.trans->pos - closest);
	}

	return areTouching;
}

float clamp(const float& f, const float& min, const float& max) {
	return std::max(min, std::min(f, max));
}


void dynamics::Collide(std::vector<Contact> contacts, const World& world)
{
	// sphere on box only for now
	for(int s = 0; s < world.spheres.size(); s++)
	{
		const SphereCollider* sphere = &world.spheres[s];

		for(int b = 0; b < world.boxes.size(); b++)
		{
			const BoxCollider* box = &world.boxes[b];

			Contact contact;
			contact.bodyA = sphere->body;

			if (SphereOnBox(*sphere, *box, contact)) {
				contacts.push_back(contact);
			}
		}
	}
}

void dynamics::Simulate(const std::vector<Contact>& contacts, World& world, float deltaTime)
{
	for(int i = 0; i < contacts.size(); i++)
	{
		Contact contact = contacts[i];

		// no support for other body yet
		// one sphere in static world

		vec3 momentumA = contact.bodyA->vel * contact.bodyA->mass;

		vec3 impulse = proj(-momentumA, contact.norm);

		contact.bodyA->vel += impulse / contact.bodyA->mass;
	}

	vec3 grav = vec3(0, -9.81f * deltaTime, 0);

	for (int i = 0; i < world.bodies.size(); i++)
	{
		Body* body = &world.bodies[i];

		body->trans->pos += body->vel * deltaTime;
		body->trans->recalc();

		body->vel += grav;
	}
}