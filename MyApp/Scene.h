//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <vector>
#include "Camera.h"
#include "Entities.h"
#include "Light.h"
#include "SpotLight.h"

//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene(Camera* cam): camera(cam) { };
	  ~Scene();
    void init();
	  void render();  
	  Diabolo* getDiabolo();

	  void linearLightSwitch() { 
	  linearSwitch = !linearSwitch;
	  if (linearSwitch)light->enable();
	  else light->disable(); 
	  };
	  void cameraLightSwitch() {
		  cameraSwitch = !cameraSwitch;
		  if (cameraSwitch)cameraLight->enable();
		  else cameraLight->disable();
	  };

	  EsferaLuz* getEsferaLuz() { return esferaLuz; };
	  
protected:
	Diabolo* diabolo = nullptr;
	Terreno* terr = nullptr;

	EsferaLuz* esferaLuz;
	  Camera* camera;
	  Light* light;
	  SpotLight* cameraLight;
	  std::vector<Entity*> objetos;
	  bool linearSwitch = true;
	  bool cameraSwitch = true;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

