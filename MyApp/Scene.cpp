#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  
  camera->setAZ();
    
  // lights
  // textures  

  // objetos

  //4 objetos en pantalla divididos
	//objetos.push_back(new EjesRGB(200.0));
	//objetos.push_back(new Triangle(75));
	objetos.push_back(new Pyramid(100.0, 250));
	objetos.push_back(new ContCubo(100));
	//objetos.push_back(new TriangleRGB(50));
	//objetos.push_back(new TriangleRGB(100));


  //Diabolo
	diabolo = new Diabolo(50, 100, 90);
	objetos.push_back(diabolo);

  //Cubo con tapa
	objetos.push_back(new Cubo(100, 100, 45));
  
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
  glMatrixMode(GL_MODELVIEW);
	for (int i = 0; i < objetos.size(); i++)// Entity* it in objetos)
	{
		camera->getVP()->setPos(camera->getVP()->getW()/2*(i%2)-camera->getVP()->getW()/4, camera->getVP()->getH()/2*(i/2)-camera->getVP()->getH()/4);
		objetos[i]->render(camera->getViewMat());
	}
}
Diabolo* Scene::getDiabolo()
{
	return diabolo;
}
//-------------------------------------------------------------------------

