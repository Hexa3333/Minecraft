#version 400
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D mTexture;
uniform vec3 ambientLight;

struct DirectionalLight
{
	vec3 color;
	float intensity;
	vec3 direction;
};

uniform vec3 ambientColor;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientLight = vec4(ambientColor, 1.0f);
	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
	vec4 diffuseColor = vec4(ambientColor, 1.0f) * directionalLight.intensity * diffuseFactor;
	FragColor = texture(mTexture, TexCoord) * (ambientLight + diffuseColor);
}
