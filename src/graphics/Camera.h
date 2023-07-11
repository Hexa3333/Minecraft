#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/struct.h>

extern mat4s g_Projection;
extern mat4s g_View;

struct Camera
{
	vec3s position;
	vec3s reverseDirection;
	vec3s front; // THIS IS THE LOOK DIRECTION
	vec3s right;
	vec3s up;
};
extern struct Camera g_MainCamera;

void SetView();
void UpdateView();


#endif // CAMERA_H
