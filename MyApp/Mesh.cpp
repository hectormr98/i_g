#include "Mesh.h"
#define pi 3.14159265

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;
  delete[] colors;
}
//-------------------------------------------------------------------------

void Mesh::draw() 
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate 
    }
	
    glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count

	  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::generateAxesRGB(GLdouble l)
{
  Mesh* m = new Mesh();
  m->type = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}

Mesh * Mesh::generateTriangleRGB(GLdouble l)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];

	double x, y, ang;
	const float aux = 120;
	for (size_t i = 0; i < 3; i++)
	{
		ang = radians(float(90 +aux *i));
		x = l*cos(ang);
		y = l*sin(ang);
		m->vertices[i] = dvec3(x, y, 0);
	}

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

Mesh * Mesh::generateTriangle(GLdouble l)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m->vertices = new dvec3[m->numVertices];

	double x, y, ang;
	const float aux = 120;
	for (size_t i = 0; i < 3; i++)
	{

		ang = radians(float(90 + aux *i));
		x = l*cos(ang);
		y = l*sin(ang);
		m->vertices[i] = dvec3(x, y, 0);

	}

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

Mesh* Mesh::generatePyramid(GLdouble r, GLdouble h) {
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_FAN;
	m->numVertices = 5;
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0, 0, h);
	double x, y, ang;
	const double aux = 120;
	for (int i = 1; i < m->numVertices; i++){
		ang = radians(float(90 + aux*i));
		x = r*cos(ang);
		y = r*sin(ang);
		m->vertices[i] = dvec3(x, y, 0);
	}
	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[3] = dvec4(1, 1, 1, 1);
	m->colors[4] = dvec4(0, 1, 0, 1);

	return m;
}
//-------------------------------------------------------------------------