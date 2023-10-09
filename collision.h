#pragma once

#include "transform.h"

using namespace glm;

namespace jtg {
	namespace collision {

		struct Collider
		{
			Transform* trans;
		};

		struct BoxCol : Collider {
			vec3 size;
		};

		struct SphereCol : Collider {
			float rad;
		};

		bool SphereOnBox(const SphereCol& s, const BoxCol& b, vec3& point);
		vec3 ClampToBox(const vec3& pos, const vec3& size);

	}
}