#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_TEXTURE_2D);
  GLuint Name; GLuint Names[3];
  glGenTextures(1, &Name);
  glGenTextures(3, Names);
  glBindTexture(GL_TEXTURE_2D, Name);
  glBindTexture(GL_TEXTURE_2D, Names[1]);
  camera->setAZ();
    
  // lights
  // textures  

  // objetos

  //4 objetos en pantalla divididos
	//objetos.push_back(new EjesRGB(200.0));
	//objetos.push_back(new Triangle(75));
	//objetos.push_back(new Pyramid(100.0, 250, 1, 1));
	//objetos.push_back(new ContCubo(100));
	//objetos.push_back(new TriangleRGB(50));
	//objetos.push_back(new TriangleRGB(100));


  //Diabolo
	diabolo = new Diabolo(25, 50, 90, 50, 50);
	objetos.push_back(diabolo);

  //Cubo con tapa
	objetos.push_back(new Cubo(50,50, 45, 1, 1, 100, 0));

  //Suelo
	objetos.push_back(new RectangleTex(500, 500, 10, 10, 0, 0));

	objetos.push_back(new Grass(50, 50, 90, 1, 1, 175, -200));
	objetos.push_back(new GlassPot(100, 100, 0, 1, 1, 150, -250));
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 
  
  for each (Entity* it in objetos)
  {
	  delete it;
  }
}
//-------------------------------------------------------------------------

void Scene::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  int size = objetos.size();
  for (int i = 0; i < size-2; i++)
  {
	  objetos[i]->render(camera->getViewMat());
  }


  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  for (int i = size - 2; i< size; i++)
  {
	  objetos[i]->render(camera->getViewMat());
  }
  glDepthMask(GL_TRUE);
  glDisable(GL_BLEND);
}
Diabolo* Scene::getDiabolo()
{
	return diabolo;
}
//-------------------------------------------------------------------------

