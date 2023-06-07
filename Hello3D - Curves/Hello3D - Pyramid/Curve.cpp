#include "Curve.h"

void Curve::draw()
{	//Chamada de desenho dos controlPoints
	glBindVertexArray(VAOCPoints);
	glDrawArrays(GL_POINTS, 0, controlPoints.size());

	//Chamada de desenho da Curva gerada
	glBindVertexArray(VAOCurve);
	glDrawArrays(GL_LINE_STRIP, 0, curvePoints.size());
}
