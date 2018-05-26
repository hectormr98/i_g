#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include "Texture.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
class Material
{
protected:
	fvec4 ambient, diffuse, specular;
	GLfloat expF;
	GLuint face = GL_FRONT_AND_BACK;
	GLuint sh = GL_SMOOTH;

public:
	virtual void load() {
		glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
		glShadeModel(sh);
	};
	Material() {};
	Material(fvec4 ambiente, fvec4 difusa, fvec4 especular)
	{
		ambient = ambiente;
		diffuse = difusa;
		specular = especular;
	};
	~Material();
};

