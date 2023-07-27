#version 400
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D mTexture;

struct AmbientLight
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	vec3 color;
	float intensity;
	vec3 direction;
};

uniform AmbientLight ambientLight;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientFactor = vec4(ambientLight.color, 1.0f) * ambientLight.intensity;
	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
	vec4 diffuseColor = vec4(ambientLight.color, 1.0f) * directionalLight.intensity * diffuseFactor;
	FragColor = texture(mTexture, TexCoord) * (ambientFactor + diffuseColor);
}