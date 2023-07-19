#version 400
layout (location=0) in vec3 mPos;
layout (location=1) in vec2 mTex;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(mPos, 1);
	TexCoord = mTex;
}
