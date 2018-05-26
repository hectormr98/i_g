#include "Entities.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <vector>
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
	mesh = Mesh::generateRectangleTex(width, height, angl, repeticionesW, repeticionesH, -sepX, 0, 0, 0);
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
RectangleTex::RectangleTex(GLdouble r, GLdouble h, int repeticionesW, int repeticionesH, GLdouble altura, GLdouble angulo)
{
     mesh = Mesh::generateNormalRectangleTex(r, h,repeticionesW, repeticionesH);
}


GlassPot::GlassPot(GLdouble r, GLdouble h, GLdouble angl, float repeticionesW, float repeticionesH, float sepX, float sepY)
{
	mesh = Mesh::generateCubeTex(r, repeticionesW, repeticionesH, sepX, sepY);
}
void GlassPot::draw()
{
	texture.bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	texture.load("..\\Bmps\\window.bmp",150);
	mesh->draw();
	texture.unbind();
}

Grass::Grass(GLdouble r, GLdouble h, GLdouble angl, float repeticionesW, float repeticionesH, float sepX, float sepY)
{
	mesh = Mesh::generateRectangleTex(r, h, angl, repeticionesW, repeticionesH, sepX, sepY, -r, 0);
}
void Grass::draw(int pos)
{
	texture.bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(1);
	std::vector <dvec3> aux;
	for(int i = 0; i < mesh->getVertices()->length()+2; i++)
	{
		aux.push_back(mesh->getVertices()[i]);
		mesh->getVertices()[i].z += pos;
	}
	mesh->draw();
	for (int i = 0; i < mesh->getVertices()->length()+2; i++)
	{
		mesh->getVertices()[i] = aux[i];
	}
	texture.unbind();

	
}

void Grass::render(glm::dmat4 const &matrix)
{
	texture.loadTrans("..\\Bmps\\grass.bmp", dvec3(0, 0, 0));
	dmat4 aux = modelMat * matrix;
	draw(0);
	aux = glm::rotate(aux, radians(90.0), dvec3(0, 1, 0));
	glLoadMatrixd(value_ptr(aux));
	draw(400);
}

Sphere::Sphere(GLdouble ratio_, GLint meridians_, GLint parallels_, GLint posX_, GLint posY_, GLint posZ_, Material m, Textura tex)
{
	//gluSphere(qObj, ratio, meridians, parallels);
	std::string algo = texturaEnum [(int)tex];
	texture.load("..\\Bmps\\"+algo+".bmp");
	qObj = gluNewQuadric();
	ratio = ratio_;
	meridians = meridians_;
	parallels = parallels_;
	posX = posX_;
	posY = posY_;
	posZ = posZ_;
	setMaterial(m);
}

void Sphere::draw()
{
	texture.bind(GL_MODULATE);
	glLineWidth(1);

	glCullFace(GL_BACK);
	gluQuadricDrawStyle(qObj, GLU_FILL);
	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricOrientation(qObj, GLU_OUTSIDE);
	gluQuadricTexture(qObj, GL_TRUE);

	gluSphere(qObj, ratio, meridians, parallels);
	texture.unbind();
}
void Sphere::render(glm::dmat4 const& matrix)
{
	dmat4 aux = matrix*modelMat;
	aux = glm::translate(aux, dvec3(posX, posY, posZ));
	glLoadMatrixd(value_ptr(aux));
	draw();
}

EsferaLuz::EsferaLuz(Camera* camera, GLdouble ratio_, GLint meridians_, GLint parallels_, GLint posX_, GLint posY_, GLint posZ_, Material m, Textura tex) :Sphere(ratio_, meridians_, parallels_, posX_, posY_, posZ_, m, tex)
{
	sphere1 = new Sphere(ratio_ / 2, meridians_ /2, parallels_/2, posX_-ratio_, posY_, posZ_, m, Textura::Uranus);
	sphere2 = new Sphere(ratio_ / 2, meridians_ / 2, parallels_ / 2, posX_ + ratio_, posY_, posZ_, m, Textura::Uranus);
	posRel1 = {posX_-sphere1->posX, posY_-sphere1->posY, posZ_-sphere1->posZ};
	posRel2 = { posX_ - sphere2->posX, posY_ - sphere2->posY, posZ_ - sphere2->posZ };
	light = new SpotLight(05);
	light->enable();
	light->setDirFoco(dvec3(0, -1, 0));
	light->setPos(dvec3(posX_, posY_, posZ_));
	light->setDiffuseIntensity(1);
	cam = camera;
	aux = { posX, posY, posZ };

}

void EsferaLuz::render(glm::dmat4 const& matrix)
{
	//light->setPos(dvec3(posX, posY, posZ));
	dmat4 aux = matrix*modelMat;
	aux = glm::translate(aux, { tray.x, tray.y, tray.z });
	aux = glm::rotate(aux, radians(ang)*100, dvec3(0, 1, 0));
	light->load(aux);
	glLoadMatrixd(value_ptr(aux));
	Sphere::draw();
	renderIzq(aux);
	renderDer(aux);
	
}
void EsferaLuz::switchLight()
{
	switchLuz = !switchLuz;
	if(switchLuz)light->enable();
	else light->disable();
}

void EsferaLuz::renderIzq(glm::dmat4 const& matrix)
{
	dmat4 aux = matrix*modelMat;
	aux = glm::translate(aux, posRel1);
	glLoadMatrixd(value_ptr(aux));
	sphere1->draw();
}
void EsferaLuz::renderDer(glm::dmat4 const& matrix)
{
	dmat4 aux = matrix*modelMat;
	aux = glm::translate(aux, posRel2);
	glLoadMatrixd(value_ptr(aux));
	sphere2->draw();
}
void EsferaLuz::rotate(float an)
{
	if(ang<360)ang += an;
	else ang = 0;
	tray = { 512*cos(ang), ratio*2*sin(ang) *sin(ang)+300, -512*sin(ang) *cos(ang) };


}

Terreno::Terreno(Material m)
{
	mesh = IndexMesh::generateTerrain();
	texture.load("..\\Bmps\\BarrenReds.bmp");
	setMaterial(m);
}

void Terreno::render(glm::dmat4 const& matrix)
{
	dmat4 aux = matrix*modelMat;
	glLoadMatrixd(value_ptr(aux));
	draw();
}

void Terreno::draw()
{
	texture.bind(GL_MODULATE);
	glLineWidth(1);

	glCullFace(GL_BACK);
	mesh->draw();

	texture.unbind();
}
//--------------------------------------------------------------------------
//comentario