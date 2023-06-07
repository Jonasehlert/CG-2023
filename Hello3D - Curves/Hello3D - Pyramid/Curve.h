#pragma once
#include "Shader.h"

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

using namespace std;

class Curve
{
public:
	Curve() {}
	void initialize(vector <glm::vec3> controlPoints);
	void generate(int nPerSegment);
	void draw();

protected:
	GLuint VAOCurve, VAOCPoints;
	Shader* shader;
	vector <glm::vec3> controlPoints, curvePoints;
	glm::mat4 H;
};

