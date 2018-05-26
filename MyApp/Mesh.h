//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <fstream>

//-------------------------------------------------------------------------

class Mesh 
{
public:
  static Mesh* generateTriangle(GLdouble l);
  static Mesh* generateTriangleRGB(GLdouble l);
  static Mesh* generateAxesRGB(GLdouble l);
  static Mesh* generatePyramid(GLdouble r, GLdouble l);
  static Mesh* generatePiramidTex(GLdouble w, GLdouble h, float repeticionesW, float repeticionesH);
  static Mesh* generateContCubo(GLdouble l, float separacionX, float separacionY);
  static Mesh* generateCubeTex(GLdouble w, float repeticionesW, float repeticionesH, float sepX, float sepY);
  static Mesh* generateDiabolo(GLdouble r,GLdouble l, float angul, float sepX, float sepY);
  static Mesh* generateDiaboloTex(GLdouble r, GLdouble l, float angul, float sepX, float sepY);
  static Mesh* generateRectangle(GLdouble w, GLdouble h, float angle, float separacionX, float separacionY, GLdouble altura, GLdouble angulo);
  static Mesh* generateNormalRectangle(GLdouble w, GLdouble h, int repeW, int repeH);
  static Mesh* generateNormalRectangleTex(GLdouble w, GLdouble h, int repeW, int repeH);
  static Mesh* generateRectangleTex(GLdouble w, GLdouble h, float angle, float repeticionesW, float repeticionesH, float sepX, float sepY, GLdouble altura, GLdouble angulo);



 
  Mesh(void) { };
  ~Mesh(void);
  void enable();
  void disable();
  virtual void draw();
  glm::dvec3* getVertices() { return vertices; };
  glm::dvec4* getColours() { return colors; };
  glm::dvec3* normals = nullptr;
   
protected:
   GLuint numVertices = 0;
   GLuint type = GL_POINTS;
   glm::dvec3* vertices = nullptr;
   glm::dvec4* colors = nullptr;
   glm::dvec2* texCoords = nullptr;
};

class IndexMesh : public Mesh
{
	IndexMesh()
	{
		numIndices = 0;
		indices = nullptr;
		type = GL_TRIANGLES;
	}
	~IndexMesh() {};
	GLuint* indices = nullptr;
	GLuint numIndices = 0;
	void enable()
	{
		Mesh::enable();
		if (indices != nullptr)
		{
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, indices);
		}
	}
	void disable()
	{
		Mesh::disable();
			glDisableClientState(GL_INDEX_ARRAY);
	}
public:
	virtual void draw()
	{
		enable();
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, indices);
		disable();
	}
	static IndexMesh* generateGrid(GLdouble lado, GLuint numDiv)
	{
		IndexMesh* m = new IndexMesh();
		GLdouble incr = lado / numDiv;
		GLuint numVer = numDiv + 1;
		m->numVertices = numVer*numVer;
		m->vertices = new glm::dvec3[m->numVertices];

		GLdouble z = -lado / 2;
		GLdouble x = -lado / 2;
		for (int i = 0; i < numVer; i++)
		{
			x = -lado / 2;
			for (int j = 0; j < numVer; j++)
			{
				m->vertices[i*numVer + j] = glm::dvec3(x, 0, z);
				x += incr;
			}
			z += incr;

		}


		m->numIndices = numDiv*numDiv * 6;
		GLuint aux = m->numIndices;
		m->indices = new GLuint[aux];

		int p = 0;
		for (int i = 0; i < numDiv; i++)
		{
			for (int j = 0; j < numDiv; j++)
			{
				GLuint iv = i*numVer+j;
				m->indices[p++] = iv;
				m->indices[p++] = iv+numVer;
				m->indices[p++] = iv+1;
				m->indices[p++] = iv+1;
				m->indices[p++] = iv + numVer;
				m->indices[p++] = iv +numVer+ 1;

			}
		}
		return m;
	}

	static IndexMesh* generateTerrain()
	{
		std::ifstream fileRead("..\\Bmps\\terrain.raw", std::ios::binary);
		if (!fileRead.is_open()) return nullptr;
		GLuint nDiv = 256;
		GLuint nVer = 257;
		GLdouble lado = nDiv * 8;
		IndexMesh* m = generateGrid(lado, nDiv);
		unsigned char* dataTerr = new unsigned char[m->numVertices];
		fileRead.read((char* )dataTerr, m->numVertices*sizeof (char));
		fileRead.close();

		for (int i = 0; i < m->numVertices; i++)
		{
			m->vertices[i].y = dataTerr[i];
		}
		m->texCoords = new glm::dvec2[m->numVertices];
		for (int i = 0; i < nVer; i++)
		{
			for (int j = 0; j < nVer; j++)
			{
				m->texCoords[i*nVer+j] = glm::dvec2(i*1.0/nDiv, 1-j*1.0/nDiv);
			}
		}
		delete dataTerr;

		m->normals = new glm::dvec3[m->numIndices];
		for (int i = 0; i < m->numVertices; i++)
		{
			m->normals[i] = {0, 0, 0};
		}
		for (int i = 0; i < m->numIndices; i+= 3)
		{
			glm::dvec3 a = m->vertices[m->indices[i]];
			glm::dvec3 b = m->vertices[m->indices[i+1]];
			glm::dvec3 c = m->vertices[m->indices[i+2]];
			glm::dvec3 n = (c - b)*(a - b);
			m->normals[m->indices[i]] += n;
			m->normals[m->indices[i+1]] += n;
			m->normals[m->indices[i+2]] += n;
		}
		for (int p = 0; p < m->numVertices; p++) {
			glm::normalize(m->normals[p]);
		}
		return m;
	}
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_