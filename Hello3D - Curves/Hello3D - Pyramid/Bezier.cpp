#include "Bezier.h"

void Bezier::initialize(vector<glm::vec3> controlPoints)
{
	this->controlPoints = controlPoints;
	H = { -1,  3, -3, 1,
		   3, -6,  3, 0,
		  -3,  3,  0, 0,
		   1,  0,  0, 0 };

	GLuint VBO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);

	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, controlPoints.size() * 3 * sizeof(GLfloat), controlPoints.data(), GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAOCPoints);

	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAOCPoints);

	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo posição (x, y, z)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Bezier::generate(int nPerSegment)
{
	float tSlice = 1.0 / (float)nPerSegment;

	for (int i = 0; i < nPerSegment; i += 4)
	{
		glm::vec3 newPoint;
		float t = tSlice * i;
		glm::vec4 T = glm::vec4(t * t * t, t * t, t, 1);
		glm::mat3x4 G = { controlPoints[i].x,     controlPoints[i].y,     controlPoints[i].z,
						  controlPoints[i + 1].x, controlPoints[i + 1].y, controlPoints[i + 1].z,
						  controlPoints[i + 2].x, controlPoints[i + 2].y, controlPoints[i + 2].z,
			              controlPoints[i + 3].x, controlPoints[i + 3].y, controlPoints[i + 3].z };
		newPoint = T * H * G;
		curvePoints.push_back(newPoint);





	}

	


}
