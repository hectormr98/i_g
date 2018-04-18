//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
  Entity() : modelMat(1.0) { };
  virtual ~Entity() { delete mesh; };
  Texture texture;
  virtual void render(glm::dmat4 const& modelViewMat);
  
protected:
  Mesh* mesh = nullptr;
  //Mesh* mesh2 = nullptr;
  glm::dmat4 modelMat;
  virtual void draw();
  virtual void setMvM(glm::dmat4 const& modelViewMat);
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

#endif //_H_Entities_H_