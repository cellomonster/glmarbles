#include "collider.h"

static glm::vec3 jtg::SphereOnBox(SphereCol sphere, BoxCol box) {

	glm::vec3 contactNormal = glm::vec3(0, 0, 0);
	glm::vec3 spherePosLocalToBox = sphere.trans.pos *= glm::inverse(box.trans.mat);

	// wide X
	if(spherePosLocalToBox > )

	return glm::vec3(0, 0, 0);
}