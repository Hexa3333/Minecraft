#version 400
layout(location = 0) in vec3 mPos;
layout(location = 1) in vec2 mTex;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(mPos, 1.0);
	TexCoord = mTex;
}

$$$

#version 400

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D mTexture;

void main()
{
	FragColor = texture(mTexture, TexCoord);
}
