#include "SpotLight.h"



SpotLight::SpotLight(float angle) : Light()
{
	GLfloat dir[3] = { 2.0, 1.0, -4.0 };
	glLightf(id, GL_SPOT_CUTOFF, angle);
	glLightf(id, GL_SPOT_EXPONENT, 4.0);
	glLightfv(id, GL_SPOT_DIRECTION, dir);
	angulo = angle;

}
SpotLight::~SpotLight()
{
}
void SpotLight::load(glm::dmat4 const& modelViewMat)
{
	Light::load(modelViewMat);
	glLightf(id, GL_SPOT_CUTOFF, angulo);
	glLightf(id, GL_SPOT_EXPONENT, 4.0);
	glLightfv(id, GL_SPOT_DIRECTION, glm::value_ptr(dir));

}

void SpotLight::setDirFoco(glm::dvec3 direccion)
{
	dir = direccion;
}
