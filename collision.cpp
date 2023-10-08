#include "collision.h"

#include <algorithm>

using namespace glm;

bool jtg::col::SphereOnBox(SphereCol sphere, BoxCol box) {

	vec3 sphereLocal = vec3((inverse(box.trans.mat) * sphere.trans.mat)[3]);

	vec3 closest = ClampToBox(sphereLocal, box.size);

	return distance(closest, sphereLocal) <= sphere.rad;
}

float clamp(float f, float min, float max) {
	return std::max(min, std::min(f, max));
}

vec3 jtg::col::ClampToBox(vec3 pos, vec3 size) {

	vec3 extents = size * 0.5f;

	vec3 p = pos;

	p.x = clamp(p.x, -extents.x, extents.x);
	p.y = clamp(p.y, -extents.y, extents.y);
	p.z = clamp(p.z, -extents.z, extents.z);

	return p;
}
