#pragma once

#include "transform.h"

using namespace glm;

namespace jtg {
	namespace col {

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

		bool SphereOnBox(SphereCol sphere, BoxCol box);
		vec3 ClampToBox(vec3 pos, vec3 size);

	}
}