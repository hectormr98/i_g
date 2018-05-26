#include "Scene.h"
typedef Entity::Textura Textura;
//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1, 1, 1, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glEnable(GL_CULL_FACE);
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
	//diabolo = new Diabolo(25, 50, 90, 50, 50);
	//objetos.push_back(diabolo);

  //Cubo con tapa
	//objetos.push_back(new Cubo(50,50, 45, 1, 1, 100, 0));

  //Suelo
	//objetos.push_back(new RectangleTex(500, 500, 10, 10, 0, 0));

	//objetos.push_back(new Grass(50, 50, 90, 1, 1, 175, -200));
	//objetos.push_back(new GlassPot(100, 100, 0, 1, 1, 150, -250));
  light = new Light();
  light->enable();
  light->setDir(dvec3(0, 1, 0));
  light->setDiffuseIntensity(0.5);
  cameraLight = new SpotLight(20);
  cameraLight->enable();
  cameraLight->setDir(dvec3(0, 1, 0));
  cameraLight->setDiffuseIntensity(1);
  

  Material a({ 0, 0, 1, 1 }, { 1, 1, 1, 1 }, { 255, 255, 255, 255 });
  objetos.push_back(new Sphere(100, 50, 50, -200, 300, -100, a, Textura::Uranus));
  Material b({ 0, 1, 1, 1 }, { 1, 1, 1, 1 }, { 255, 255, 255, 255 });
  objetos.push_back(new Sphere(50, 50, 50, 100, 200, 0, b, Textura::Moon));
  Material c({ 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 255, 255, 255, 255 });
  objetos.push_back(new Sphere(100, 50, 50, -100, 100, 0, c, Textura::Marte));
  Material d({ 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 255, 255, 255, 255 });
  esferaLuz = (new EsferaLuz(camera, 50, 50, 50, 0, 500, 0, d, Textura::Sun));
  objetos.push_back(esferaLuz);
  Material e({ 1, 1, 1, 1 }, { 1, 1, 1, 1 }, {255, 255, 255, 255});
  terr = new Terreno(e);
  objetos.push_back(terr);
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
  //for (int i = 0; i < 1; i++)
  //{
	 // objetos[i]->render(camera->getViewMat());
  //}
  glEnable(GL_BLEND);
  light->load(camera->getViewMat());

  cameraLight->setDirFoco(camera->getDir());
  cameraLight->setPos(camera->getEye());
  cameraLight->load(camera->getViewMat());

  for (int i = 0; i< size; i++)
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

