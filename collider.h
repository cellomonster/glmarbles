#pragma once

#include "transform.h"

namespace jtg {

	class Body {

	public:
		Transform *trans;
		glm::vec3 vel;
		glm::vec3 angVel;
	};

	struct BoxCol {
		Transform *trans;
		glm::vec3 size;
	};

	struct SphereCol {
		Transform* trans;
		float rad;
	};

	static glm::vec3 SphereOnBox(SphereCol sphere, BoxCol box);
	static glm::vec3 ClampToBox(glm::vec3 pos, glm::vec3 size);
	static float clamp(float f, float min, float max);
}