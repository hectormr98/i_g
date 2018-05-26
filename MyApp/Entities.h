//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include <vector>
#include "SpotLight.h"
#include "Camera.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
	Entity() : modelMat(1.0) {  };
  virtual ~Entity() { delete mesh; };
  Texture texture;
  virtual void render(glm::dmat4 const& modelViewMat);
  enum Textura { Tierra, Marte, Uranus, Moon, Sun, Venus };
  std::vector<std::string> texturaEnum = { "earth24", "mars", "BarrenReds", "moon", "sun" , "venus"};
  
protected:
  Material* material;
  Mesh* mesh = nullptr;
  //Mesh* mesh2 = nullptr;
  glm::dmat4 modelMat;
  virtual void draw();
  virtual void setMvM(glm::dmat4 const& modelViewMat);
  void setModelMat(glm::dmat4 const& mMat) { modelMat = mMat; };
  void setMaterial(Material const& mt) { if(material == nullptr) material = new Material(); *material = mt; };
  void setTexture(Texture const& tex) { texture = tex; };
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
  EjesRGB(GLdouble l);
  ~EjesRGB() { };
  virtual void draw();
};
//-------------------------------------------------------------------------
class Triangle : public Entity 
{
public:
	Triangle(GLdouble l);
	~Triangle() {};
	virtual void draw();
};
//-------------------------------------------------------------------------
class TriangleRGB : public Entity {
public:
	TriangleRGB(GLdouble l);
	~TriangleRGB() {};
	virtual void draw();
};
//-------------------------------------------------------------------------
class Pyramid :public Entity {
public:
	Pyramid(GLdouble r, GLdouble h, int repeW, int repeH);
	~Pyramid() {};
	virtual void draw();
};
class ContCubo :public Entity {
public:
	ContCubo(GLdouble h);
	~ContCubo() {};
	virtual void draw();
};
class Diabolo :public Entity {
public:
	float angulo = 90;
	float r, h;
	void rotate(float ang, float sepX, float sepY);
	Diabolo(GLdouble r, GLdouble h, float angul, float sepX, float sepY);
	~Diabolo() {};
	virtual void draw();
};

class RectangleTex :public Entity
{
public:
	RectangleTex(GLdouble r, GLdouble h, int repeticionesW, int repeticionesH, GLdouble altura, GLdouble angulo);
	~RectangleTex() {};
	virtual void draw();
};

class Cubo :public Entity {
public:
	Mesh* caja = nullptr;
	Cubo(GLdouble r, GLdouble h, GLdouble angl, float repeticionesW, float repeticionesH, float sepX, float sepY);
	~Cubo() {};
	virtual void draw();
};
class GlassPot :public Entity
{
public:
	Mesh* mesh = nullptr;
	GlassPot(GLdouble r, GLdouble h, GLdouble angl, float repeticionesW, float repeticionesH, float sepX, float sepY);
	~GlassPot() {};
	virtual void draw();
};

class Grass : public Entity
{
public:
	Mesh* mesh = nullptr;
	Grass(GLdouble r, GLdouble h, GLdouble angl, float repeticionesW, float repeticionesH, float sepX, float sepY);
	~Grass() {};
	virtual void draw(int pos);
	virtual void render(glm::dmat4 const &matrix);
};

class Sphere : public Entity
{
public:
	GLUquadricObj* qObj;
	Sphere(GLdouble ratio, GLint meridians, GLint parallels, GLint posX, GLint posY, GLint posZ, Material m, Textura tex);
	~Sphere() {};
	virtual void draw();
	virtual void render(glm::dmat4 const& matrix);
	int posX, posY, posZ;
protected:
	int ratio, meridians, parallels;
};
class EsferaLuz : public Sphere
{
public:
	Sphere* sphere1;
	Sphere* sphere2;
	SpotLight* light;
	Camera * cam;
	EsferaLuz(Camera* camera, GLdouble ratio, GLint meridians, GLint parallels, GLint posX, GLint posY, GLint posZ, Material m, Textura tex);
	~EsferaLuz() {};
	//virtual void draw() { Sphere::draw(); };
	virtual void render(glm::dmat4 const& matrix);
	void switchLight ();
	void rotate(float ang);
	void renderIzq(glm::dmat4 const& matrix);
	void renderDer(glm::dmat4 const& matrix);
private:
	bool switchLuz = true;
	glm::fvec3 tray = {0, 0, 0};
	glm::dvec3 posRel1;
	glm::dvec3 posRel2;
	glm::dvec3 aux;
	double ang = 0;
	//int ratio, meridians, parallels, posX, posY, posZ;
};
class Terreno : public Entity
{
public:
	Terreno(Material m);
	~Terreno() {};
	//virtual void draw() { Sphere::draw(); };
	virtual void render(glm::dmat4 const& matrix);
	virtual void draw();
};

#endif //_H_Entities_H_