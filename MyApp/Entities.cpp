#include "Entities.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

void Entity::render(dmat4 const& modelViewMat) 
{ 
	setMvM(modelViewMat); 
	draw(); 
}

void Entity::draw() 
{ 
  if (mesh != nullptr) 
    mesh -> draw(); 
  /*if (mesh2 != nullptr)
  mesh2->draw();*/
}

void Entity::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
    mesh = Mesh::generateAxesRGB(l);
}

void EjesRGB::draw()
{
  glLineWidth(2);
  mesh->draw();
  glLineWidth(1);
}
//-------------------------------------------------------------------------

Triangle::Triangle(GLdouble l) :Entity() {
	mesh = Mesh::generateTriangle(l);
}

void Triangle::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
//-------------------------------------------------------------------------

TriangleRGB::TriangleRGB(GLdouble l) {
	mesh = Mesh::generateTriangleRGB(l);
}

void TriangleRGB::draw() {
	glLineWidth(1);
	mesh->draw();
}
//-------------------------------------------------------------------------
Pyramid::Pyramid(GLdouble r, GLdouble h) {

	mesh = Mesh::generatePyramid(r, h);

}

void Pyramid::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
//--------------------------------------------------------------------------
//comentario