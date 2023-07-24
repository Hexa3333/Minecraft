#version 400
layout (location=0) in vec3 mPos;
layout (location=1) in vec3 mNorm;

out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(mPos, 1.0);
	Normal = mat3(model) * mNorm;
}