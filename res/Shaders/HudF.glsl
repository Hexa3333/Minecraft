#version 400

out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D texSample;

void main()
{
	FragColor = texture(texSample, TexCoord);
}
