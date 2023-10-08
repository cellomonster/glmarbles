#include "collider.h"

#include <algorithm>

bool jtg::SphereOnBox(SphereCol sphere, BoxCol box) {

	glm::vec3 sphereLocal = glm::vec3((glm::inverse(box.trans->mat) * sphere.trans->mat)[3]);

	glm::vec3 closest = ClampToBox(sphereLocal, box.size);

	return glm::distance(closest, sphereLocal) <= sphere.rad;
}

float jtg::clamp(float f, float min, float max) {
	return std::max(min, std::min(f, max));
}

glm::vec3 jtg::ClampToBox(glm::vec3 pos, glm::vec3 size) {

	glm::vec3 extents = size * 0.5f;

	glm::vec3 p = pos;

	p.x = clamp(p.x, -extents.x, extents.x);
	p.y = clamp(p.y, -extents.y, extents.y);
	p.z = clamp(p.z, -extents.z, extents.z);

	return p;
}
