#pragma once
#include "Light.h"
class SpotLight: public Light
{
public:
	SpotLight(float angle);
	~SpotLight();
	virtual void load(glm::dmat4 const& modelViewMat);
	void setDirFoco(glm::dvec3 direccion);
private:
	float angulo;
	glm::fvec3 dir;
};

