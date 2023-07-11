#version 400
layout (location = 0) in vec3 mVerts;
layout (location = 1) in vec3 mColors;

out vec3 Colors;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	Colors = mColors;
	gl_Position = projection * view * model * vec4(mVerts, 1.0f);
}
