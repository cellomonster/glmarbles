#include "dynamics.h"

using namespace jtg::dynamics;
using namespace jtg::collision;

void jtg::dynamics::Step(World world)
{
	for (int b = 0; b < world.bodies.size(); b++)
	{
		Body body = world.bodies[b];

		// TODO: test between bodies

		for(int s = 0; s < world.statics.size(); s++)
		{
			Collider col = world.statics[s];

			genContact(world, a, b);
		}
	}
}

void genContact(World world, Body a, Body b)
{
	if(SphereOnBox())
}