#include "collision.h"

#include <algorithm>

using namespace glm;

bool jtg::collision::SphereOnBox(const SphereCol& s, const BoxCol& b, vec3& point) {

	const vec3 sphereLocal = vec3((inverse(b.trans->mat) * s.trans->mat)[3]);
	const vec3 closest = ClampToBox(sphereLocal, b.size);

	const bool areTouching = distance(closest, sphereLocal) <= s.rad;

	if(areTouching)
	{
		point = vec3((b.trans->mat * vec4(closest, 0))[3]);
	}

	return areTouching;
}

float clamp(const float& f, const float& min, const float& max) {
	return std::max(min, std::min(f, max));
}

vec3 jtg::collision::ClampToBox(const vec3& pos, const vec3& size) {

	vec3 extents = size * 0.5f;

	vec3 p = pos;

	p.x = clamp(p.x, -extents.x, extents.x);
	p.y = clamp(p.y, -extents.y, extents.y);
	p.z = clamp(p.z, -extents.z, extents.z);

	return p;
}
