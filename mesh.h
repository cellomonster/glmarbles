#pragma once

#include <vector>

namespace jtg {

	struct Mesh {
		std::vector<float> verts;
		std::vector<unsigned int> tris;
	};

	Mesh blockMesh(const float& x, const float& y, const float& z);
	Mesh polyhedronMesh(const float& r);
}