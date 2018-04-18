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
	if (texCoords != nullptr)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
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
	m->colors[3] = dvec4(1, 1, 0, 1);
	m->colors[4] = dvec4(0, 1, 0, 1);

	return m;
}

Mesh* Mesh::generatePiramidTex(GLdouble w, GLdouble h, float repeticionesW, float repeticionesH)
{
	//Texturas
	Mesh* m = generatePyramid(w, h);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0.5f, repeticionesH);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(repeticionesW, 0);
	m->texCoords[3] = dvec2(0, 0);
	m->texCoords[4] = dvec2(repeticionesW, 0);



	return m;
}
Mesh * Mesh::generateContCubo(GLdouble l, float separacionX, float separacionY)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 10;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m->vertices = new dvec3[m->numVertices];


	m->vertices[0] = dvec3(separacionX ,l ,separacionY);
	m->vertices[1] = dvec3(separacionX, 0, separacionY);
	m->vertices[2] = dvec3(l + separacionX, l, separacionY);
	m->vertices[3] = dvec3(l + separacionX, 0, separacionY);
	m->vertices[4] = dvec3(l + separacionX, l, l+ separacionY);
	m->vertices[5] = dvec3(l + separacionX, 0, l+ separacionY);
	m->vertices[6] = dvec3(separacionX, l, l+ separacionY);
	m->vertices[7] = dvec3(separacionX, 0, l+ separacionY);
	m->vertices[8] = dvec3(separacionX, l, separacionY);
	m->vertices[9] = dvec3(separacionX, 0, separacionY);



	m->colors = new dvec4[m->numVertices];
	return m;
}
Mesh * Mesh::generateDiabolo(GLdouble r,GLdouble l, float angulo, float sepX, float sepY)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_FAN;
	m->numVertices = 20;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0, 0, 0);
	double x, y, ang;
	const double aux = 120;
	for (int i = 1; i < 5; i++) {
		ang = radians(float(angulo + aux*i));
		x = r*cos(ang);
		y = r*sin(ang);
		m->vertices[i] = dvec3(x, -l, y);
	}
	m->vertices[5] = dvec3(0, 0, 0);
	for (int i = 6; i < 10; i++) {
		ang = radians(angulo-60+float(aux*i));
		x = r*cos(ang);
		y = r*sin(ang);
		m->vertices[i] = dvec3(x, -l, y);
	}
	m->vertices[10] = dvec3(0, 0, 0);
	for (int i = 11; i < 15; i++) {
		ang = radians(angulo + float(aux*i));
		x = r*cos(ang);
		y = r*sin(ang);
		m->vertices[i] = dvec3(x, l, y);
	}
	m->vertices[15] = dvec3(0, 0, 0);
	for (int i = 16; i < 20; i++) {
		ang = radians(angulo-60 + float(aux*i));
		x = r*cos(ang);
		y = r*sin(ang);
		m->vertices[i] = dvec3(x, l, y);
	}
	for (int i = 0; i < m->numVertices; i++)
	{
		m->vertices[i] += dvec3(sepX, l, sepY);
	}

	m->colors = new dvec4[m->numVertices];
	for (int i = 0; i < 4; i++)
	{
		m->colors[i] = dvec4(1.0, 0.0, 0.0, 1.0);
	}
	for (int i = 5; i < 9; i++)
	{
		m->colors[i] = dvec4(0.0, 1, 0.0, 1.0);
	}
	for (int i = 10; i < 14; i++)
	{
		m->colors[i] = dvec4(0.0, 0, 1, 1.0);
	}
	for (int i = 15; i < 19; i++)
	{
		m->colors[i] = dvec4(0.0, 0.0, 0.0, 1.0);
	}
	return m;
}
Mesh * Mesh::generateDiaboloTex(GLdouble r, GLdouble l, float angulo, float sepX, float sepY)
{
	//Texturas
	Mesh* m = generateDiabolo(r, l, angulo, sepX, sepY);
	m->texCoords = new dvec2[m->numVertices];
	for (int i = 0; i < m->numVertices; i++)
	{
		if (i == 0) m->texCoords[0] = dvec2(0.5f, 1);
		else if (i % 5 == 0)m->texCoords[i] = dvec2(0.5f, 1);
		else if (i % 2 == 0)m->texCoords[i] = dvec2(1, 0);
		else m->texCoords[i] = dvec2(0, 0);
	}


	return m;
}
Mesh * Mesh::generateRectangle(GLdouble w, GLdouble h, float angle, float separacionX, float separacionY, GLdouble altura, GLdouble angulo)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 5;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m->vertices = new dvec3[m->numVertices];


	m->vertices[0] = dvec3(separacionX, sin(radians(angle))*h / 2 + w * 3 / 2 - (h / 2 + sin(radians(angle))*h / 2) +altura, -(h / 2 - cos(radians(angle))*h / 2) + h / 2 - cos(radians(angle))*h / 2+separacionY);
	m->vertices[1] = dvec3(separacionX, sin(radians(angle))*h / 2 + w * 3 / 2 - (h / 2 - sin(radians(angle))*h / 2)+altura, -(h / 2 - cos(radians(angle))*h / 2) + h / 2 + cos(radians(angle))*h / 2+separacionY);
	m->vertices[2] = dvec3(w+separacionX, sin(radians(angle))*h / 2 + w * 3 / 2 - (h / 2 - sin(radians(angle))*h / 2)+altura, -(h / 2 - cos(radians(angle))*h / 2) + h / 2 + cos(radians(angle))*h / 2+separacionY);
	m->vertices[3] = dvec3(w+separacionX, sin(radians(angle))*h / 2 + w * 3 / 2 - (h / 2 + sin(radians(angle))*h / 2)+altura, -(h / 2 - cos(radians(angle))*h / 2) + h / 2 - cos(radians(angle))*h / 2+separacionY);
	m->vertices[4] = m->vertices[0];



	m->colors = new dvec4[m->numVertices];
	return m;
}
Mesh* Mesh::generateNormalRectangle(GLdouble w, GLdouble h, int repeW, int repeH)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 5;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m->vertices = new dvec3[m->numVertices];


	m->vertices[0] = dvec3(-w/2, 0, -h/2);
	m->vertices[1] = dvec3(w/2, 0, -h/2);
	m->vertices[2] = dvec3(w/2, 0, h/2);
	m->vertices[3] = dvec3(-w/2, 0, h/2);
	m->vertices[4] = m->vertices[0];

	m->colors = new dvec4[m->numVertices];
	return m;
}
Mesh* Mesh::generateNormalRectangleTex(GLdouble w, GLdouble h, int repeticionesW, int repeticionesH)
{
	//Texturas
	Mesh* m = generateNormalRectangle(w, h, repeticionesW, repeticionesH);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(1 * repeticionesW, 0);
	m->texCoords[1] = dvec2(1 * repeticionesW, 1 * repeticionesH);
	m->texCoords[2] = dvec2(0, 1 * repeticionesH);
	m->texCoords[3] = dvec2(0, 0);
	m->texCoords[4] = dvec2(1 * repeticionesW, 0);



	return m;
}
Mesh* Mesh::generateRectangleTex(GLdouble w, GLdouble h, float angle, float repeticionesW, float repeticionesH, float sepX, float sepY, GLdouble altura, GLdouble angulo)
{
	//Texturas
	Mesh* m = generateRectangle(w, h, angle, sepX, sepY, altura, angulo);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(1*repeticionesW, 0);
	m->texCoords[1] = dvec2(1*repeticionesW, 1*repeticionesH);
	m->texCoords[2] = dvec2(0, 1*repeticionesH);
	m->texCoords[3] = dvec2(0, 0);
	m->texCoords[4] = dvec2(1*repeticionesW, 0);



	return m;
}

Mesh* Mesh::generateCubeTex(GLdouble w, float repeticionesW, float repeticionesH, float sepX, float sepY)
{
	//Texturas
	Mesh* m = generateContCubo(w, sepX, sepY);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 1*repeticionesH);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(1 * repeticionesW, 1 * repeticionesH);
	m->texCoords[3] = dvec2(1 * repeticionesW, 0);
	m->texCoords[4] = dvec2(0, 1 * repeticionesH);
	m->texCoords[5] = dvec2(0, 0);
	m->texCoords[6] = dvec2(1 * repeticionesW, 1 * repeticionesH);
	m->texCoords[7] = dvec2(1 * repeticionesW, 0);
	m->texCoords[8] = dvec2(0, 1 * repeticionesH);
	m->texCoords[9] = dvec2(0, 0);


	return m;
}
//-------------------------------------------------------------------------
