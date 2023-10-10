#include "dynamics.h"

using namespace jtg;
using namespace jtg::dynamics;


vec3 ClampToBox(const vec3& pos, const vec3& size) {

	vec3 extents = size * 0.5f;

	vec3 p = pos;

	p.x = clamp(p.x, -extents.x, extents.x);
	p.y = clamp(p.y, -extents.y, extents.y);
	p.z = clamp(p.z, -extents.z, extents.z);

	return p;
}


bool SphereOnBox(const Transform& sphereTransform, const float& radius,
	const Transform& boxTransform, const vec3& size, Contact& contact) {

	const vec3 sphereLocal = vec3((inverse(boxTransform.mat) * sphereTransform.mat)[3]);
	const vec3 closest = ClampToBox(sphereLocal, size);

	const bool areTouching = distance(closest, sphereLocal) <= radius;

	if (areTouching)
	{
		contact.point = closest;
		contact.norm = normalize(sphereTransform.pos - closest);
	}

	return areTouching;
}

float clamp(const float& f, const float& min, const float& max) {
	return std::max(min, std::min(f, max));
}


void dynamics::Collide(std::vector<Contact> contacts, std::vector<Body> bodies, Colliders colliders)
{
	// sphere on box only for now
	for(int s = 0; s < colliders.spheres.radii.size(); s++)
	{
		Body sphereBody = colliders.spheres.bodies[s];
		float radius = colliders.spheres.radii[s];

		for(int b = 0; b < colliders.boxes.sizes.size(); b++)
		{
			Body boxBody = colliders.boxes.bodies[b];
			vec3 size = colliders.boxes.sizes[b];

			Contact contact;
			contact.bodyA = sphereBody;
			contact.bodyB = boxBody;

			if (SphereOnBox(*sphereBody.trans, radius, *boxBody.trans, size, contact)) {
				contacts.push_back(contact);
			}
		}
	}
}

void dynamics::Simulate(std::vector<Contact> contacts, float deltaTime)
{
	for(int i = 0; i < contacts.size(); i++)
	{
		Contact contact = contacts[i];

		float momentumA = 

		contact.bodyA.trans->pos += 
	}
}