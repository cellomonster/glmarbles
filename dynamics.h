#pragma once
#include <vector>

#include "collision.h"

using namespace glm;

namespace jtg
{
	namespace dynamics
	{
		struct Body {
			Transform* trans;
			vec3 vel;
			vec3 angVel;

			col::Collider col;
		};

		struct Contact
		{
			Body bodyA, bodyB;
			vec3 pointA, pointB;
			vec3 normalA, normalB;
		};


		struct World
		{
			std::vector<col::Collider> statics;
			std::vector<Body> bodies;
			
		};

		void Step(World world);

	}
}
