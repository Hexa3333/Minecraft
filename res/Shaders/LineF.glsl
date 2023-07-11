#version 400

out vec4 FragColor;

in vec3 Colors;

void main()
{
	FragColor = vec4(Colors, 1.0f);
}
