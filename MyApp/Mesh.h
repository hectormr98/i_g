//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh 
{
public:
  static Mesh* generateTriangle(GLdouble l);
  static Mesh* generateTriangleRGB(GLdouble l);
  static Mesh* generateAxesRGB(GLdouble l);
  static Mesh* generatePyramid(GLdouble r, GLdouble l);
  static Mesh* generateContCubo(GLdouble l);
  static Mesh* generateDiabolo(GLdouble r,GLdouble l, float angul);
  static Mesh* generateRectangle(GLdouble w, GLdouble h, float angle);
  static Mesh* generateRectangleTex(GLdouble w, GLdouble h, float angle, float repeticiones);
  static Mesh* generateCubeTex(GLdouble w, float repeticiones);

 
  Mesh(void) { };
  ~Mesh(void);
  virtual void draw();
  glm::dvec3* getVertices() { return vertices; };
  glm::dvec4* getColours() { return colors; };
   
protected:
   GLuint numVertices = 0;
   GLuint type = GL_POINTS;
   glm::dvec3* vertices = nullptr;
   glm::dvec4* colors = nullptr;
   glm::dvec2* texCoords = nullptr;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_