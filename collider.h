#include "transform.h"

namespace jtg {

	class Collider {

	public:
		Transform trans;
	};

	class Rigidbody {

	public:
		Transform trans;
		glm::vec3 vel;
		glm::vec3 angVel;
	};

	class BoxCol : public Collider {

	public:
		glm::vec3 size;


	};

	class SphereCol : public Collider {
	public:
		float rad;
	};

	static glm::vec3 SphereOnBox(SphereCol sphere, BoxCol box);
}