#pragma once
#include "Curve.h"
class Bezier :
	public Curve
{
	Bezier() {}
	void initialize(vector <glm::vec3> controlPoints);
	void generate(int nPerSegment);
};

