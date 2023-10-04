#include "collider.h"

#include <algorithm>

static glm::vec3 jtg::SphereOnBox(SphereCol sphere, BoxCol box) {

	glm::vec3 contNorm = glm::vec3(0);

	glm::vec3 spherePosLocalToBox = sphere.trans->pos;
	spherePosLocalToBox *= glm::inverse(box.trans->mat);

	glm::vec3 closest = ClampToBox(spherePosLocalToBox, box.size);

	if (glm::distance(closest, spherePosLocalToBox) <= sphere.rad) {
		contNorm = glm::normalize(spherePosLocalToBox - closest);
		contNorm *= box.trans->mat;
	}

	return contNorm;
}

static float jtg::clamp(float f, float min, float max) {
	return std::max(min, std::min(f, max));
}

static glm::vec3 jtg::ClampToBox(glm::vec3 pos, glm::vec3 size) {

	glm::vec3 extents = size * 0.5f;

	glm::vec3 p = pos;

	p.x = clamp(pos.x, -extents.x, extents.x);
	p.y = clamp(pos.y, -extents.y, extents.y);
	p.z = clamp(pos.z, -extents.z, extents.z);

	return p;
}
