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
Pyramid::Pyramid(GLdouble r, GLdouble h, int repeW, int repeH) {

	mesh = Mesh::generatePiramidTex(r, h, repeW, repeH);

}

void Pyramid::draw() {
	texture.bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	texture.load("..\\Bmps\\emopng.bmp");
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.unbind();
}

void ContCubo::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
ContCubo::ContCubo(GLdouble h) {

	mesh = Mesh::generateContCubo(h, 0, 0);

}
void Diabolo::draw() {
	texture.bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	texture.load("..\\Bmps\\Diabolo.bmp");
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	texture.unbind();
}
Diabolo::Diabolo(GLdouble radius, GLdouble height, float angul, float sepX, float sepY) {

	r = radius;
	h = height;
	angulo = angul;
	mesh = Mesh::generateDiaboloTex(r, h, angulo, sepX, sepY);

}
void Diabolo::rotate(float ang, float sepX, float sepY)
{
	angulo += ang;
	mesh = Mesh::generateDiaboloTex(r, h, angulo, sepX, sepY);
}

void Cubo::draw() {
	texture.bind();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	texture.load("..\\Bmps\\Caja.bmp");
	mesh->draw();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	texture.load("..\\Bmps\\CajaDentro.bmp");
	caja->draw();
	glCullFace(GL_FRONT);
	texture.load("..\\Bmps\\Caja.bmp");
	caja->draw();
	glDisable(GL_CULL_FACE);

	texture.unbind();
}
Cubo::Cubo(GLdouble width, GLdouble height, GLdouble angl,float repeticionesW, float repeticionesH, float sepX, float sepY) 
{
	mesh = Mesh::generateRectangleTex(width, height, angl, repeticionesW, repeticionesH, -sepX, 0);
	caja = Mesh::generateCubeTex(width, repeticionesW, repeticionesH, -sepX, 0);
}

void RectangleTex::draw()
{
	texture.bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	texture.load("..\\Bmps\\Suelo.bmp");
	mesh->draw();
	texture.unbind();
}
RectangleTex::RectangleTex(GLdouble r, GLdouble h, int repeticionesW, int repeticionesH)
{
     mesh = Mesh::generateNormalRectangleTex(r, h, repeticionesW, repeticionesH);
}
//--------------------------------------------------------------------------
//comentario