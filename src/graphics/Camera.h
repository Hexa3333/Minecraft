#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/struct.h>

struct Camera
{
	vec3s position;
	vec3s reverseDirection;
	vec3s front; // THIS IS THE LOOK DIRECTION
	vec3s right;
	vec3s up;
};
extern struct Camera g_MainCamera;

mat4s SetView();
mat4s UpdateView();


#endif // CAMERA_H
