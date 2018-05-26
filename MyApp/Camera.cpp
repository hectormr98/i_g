#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>


//-------------------------------------------------------------------------

 void Viewport::setSize(GLsizei aw, GLsizei ah) 
 { 
   w = aw; 
   h = ah; 
   set(); 
 }
 //-------------------------------------------------------------------------

 void Viewport::set() 
 { 
   glViewport(x, y, w, h);
 }
 void Viewport::setPos(GLdouble l, GLdouble g)
 {
	 glViewport(l, g, w, h);
 }
//-------------------------------------------------------------------------

void Camera::setAZ() 
{
  eye= dvec3(100, 200, 500);
  look= dvec3(0, 0, 0);
  up= dvec3(0, 1, 0);
  n = normalize(eye - look);
  u = normalize(cross(up, n));
  v = cross(n, u);
  front = -n;
  right = u;
  up = v;
  viewMat = lookAt(eye, look, up);

  if (pitc > 89.5) pitc = 89.5;
  front.x = sin(radians(ya))*cos(radians(pitc));
  front.y = sin(radians(pitc));
  front.z = -cos(radians(ya))*cos(radians(pitc));
  front = glm::normalize(front);
  viewMat = lookAt(eye, eye + front, up);

  setVM();
}
//-------------------------------------------------------------------------
void Camera::set3D() 
{
  eye= dvec3(500, 500, 500);
  look= dvec3(0, 10, 0);
  up= dvec3(0, 1, 0);
  n = normalize(eye - look);
  u = normalize(cross(up, n));
  v = cross(n, u);
  front = -n;
  right = u;
  up = v;
  viewMat = lookAt(eye, look, up);

  if (pitc > 89.5) pitc = 89.5;
  front.x = sin(radians(ya))*cos(radians(pitc));
  front.y = sin(radians(pitc));
  front.z = -cos(radians(ya))*cos(radians(pitc));
  front = glm::normalize(front);
  viewMat = lookAt(eye, eye + front, up);

  setVM();
}

dvec3 Camera::getDir()
{
	return front;
}

dvec3 Camera::getEye()
{
	return eye;// -dvec3(200, 100, 0);
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{ 
  factScale -= s; 
  if (s < 0) s = 0.01;
  setPM(); 
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble aw, GLdouble ah) 
{
  xRight = aw / 2.0;
  xLeft = -xRight;
  yTop = ah / 2.0;
  yBot = -yTop;
 
  setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{
	if(orto)
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	else
		projMat = frustum(-500, 500, -250, 250, 500, 10000);
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixd(value_ptr(projMat));
  glMatrixMode(GL_MODELVIEW);
}

void Camera::moveLR(GLdouble cs)
{
	eye = eye + (front * cs);
	look = look + (front*cs);
	viewMat = lookAt(eye, eye +front, up);
}

void Camera::moveFB(GLdouble cs)
{
	eye = eye + (right * cs);
	viewMat = lookAt(eye, eye + front, up);
}

void Camera::moveUD(GLdouble cs)
{
	eye = eye + (up * cs);
	viewMat = lookAt(eye, eye + front, up);
}

void Camera::rotatePY(GLdouble incrPitch, GLdouble incrYaw)
{
	pitc += incrPitch;
	ya += incrYaw;
	if (pitc > 89.5) pitc = 89.5;
	front.x = sin(radians(ya))*cos(radians(pitc));
	front.y = sin(radians(pitc));
	front.z = -cos(radians(ya))*cos(radians(pitc));
	front = glm::normalize(front);
	viewMat = lookAt(eye, eye + front, up);
	right = normalize(cross(up, -front));
}

void Camera::setPrj()
{
	orto = !orto;
	setPM();
}


//-------------------------------------------------------------------------


