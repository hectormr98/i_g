//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
  Entity() : modelMat(1.0) { };
  virtual ~Entity() { delete mesh; };

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
	Pyramid(GLdouble r, GLdouble h);
	~Pyramid() {};
	virtual void draw();
};

#endif //_H_Entities_H_