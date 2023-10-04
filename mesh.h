#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace jtg {

	struct Mesh {
		std::vector<float> verts;
		std::vector<unsigned int> tris;
	};

	Mesh blockMesh(const glm::vec3& size);
	Mesh polyhedronMesh(const float& r);
}