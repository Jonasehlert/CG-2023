/******************************************************************************\
* Virtual Cow Parade -- Texture Generator                                      *
*                                                                              *
* Técnicas Avançadas de Computação Gráfica 2010-2
-----------*
*                                                                              *
* Este programa utiliza a libnoise (http://libnoise.sourceforge.net) para a    *
* geração de texturas procedurais                                              *
*                                                                              *
*                                                                              *
* Projeto iniciado por Rossana Queiroz  em 08/11/2010                          *
* Última atualização em 25/05/2023
*                                                                              *
\******************************************************************************/

#include <iostream>
#include <noise/noise.h>
#include "noiseutils.h"

#include <sstream>
#include <ctime>


using namespace noise;


utils::NoiseMap BuildAHeightMap(int w, int h, float* bounds) {
	//Classe para a criação de ruído de perlin (Perlin Noise)
	module::Perlin myModule;

	myModule.SetFrequency(2.0);
	myModule.SetOctaveCount(2);
	myModule.SetPersistence(0.5);


	//Utilizando a biblioteca auxiliar noiseutils, podemos instanciar um mapa de noise, que neste caso será utilizado para gerar um heightmap
	utils::NoiseMap heightMap;

	//
	utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(w, h);
	heightMapBuilder.SetBounds(bounds[0], bounds[1], bounds[2], bounds[3]);
	heightMapBuilder.Build();

	return heightMap;
}

utils::NoiseMap BuildASphericalHeightMap(int w, int h) {
	//Classe para a criação de ruído de perlin (Perlin Noise)
	module::Perlin myModule;

	//myModule.SetSeed(time(0));
	//myModule.SetLacunarity(4.5);


	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderSphere heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(w, h);
	heightMapBuilder.SetBounds(-90.0, 90.0, -180.0, 180.0);
	heightMapBuilder.Build();

	return heightMap;
}


void RenderHeightMap(utils::NoiseMap heightMap, std::string filename) {
	//Renderizando...
	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap(heightMap);
	renderer.SetDestImage(image);

	//Para definir faixas de cores para os BIOMAS... 
	renderer.ClearGradient();
	//renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
	//renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
	//renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
	//renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
	//renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
	//renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
	//renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
	//renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow

	//Criando aleatoriamente os biomas
	int n = rand() % 7 + 2; // sorteia de 2 a 8 biomas
	float slice = 2.0 / (float)n; //divide o espaço de -1 a 1 entre o nro de biomas sorteado

	for (int i = 0; i < n; i++)
	{
		int R = rand() % 256;
		int G = rand() % 256;
		int B = rand() % 256;
		renderer.AddGradientPoint(-1.0000 + i * slice, utils::Color(R, G, B, 255));
	}

	//renderer.EnableLight ();
	//renderer.SetLightContrast (3); // Triple the contrast
	//renderer.SetLightBrightness (2); // Double the brightness

	renderer.Render();

	//Escrevendo...
	utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename(filename.c_str());
	writer.WriteDestFile();
}

int main(int argc, char** argv)
{
	srand(time(0));

	utils::NoiseMap heightMap;
	float bounds[4] = { 2.0, 6.0, -3.0, 1.0 };

	//Modo padrão
	heightMap = BuildAHeightMap(512, 512, bounds);

	//Para criar o mapa com projeção esférica
	//heightMap = BuildASphericalHeightMap(1024, 512);


	RenderHeightMap(heightMap, "../example14.bmp");


	std::cout << "Success!\n";

	getchar();


	return 0;
}