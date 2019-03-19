#ifndef _LIGHTING_HLSL
#define _LIGHTING_HLSL

#define LIGHT_TYPE_DIRECTIONAL	0
#define LIGHT_TYPE_POINT		1
#define LIGHT_TYPE_SPOT			2

struct Light
{
	int		Type;
	float3	Direction;	// 16 bytes

	float	Range;
	float3	Position;	// 32 bytes

	float	Intensity;
	float3	Color;		// 48 bytes

	float	SpotFalloff;
	float3	Padding;	// 64 bytes
};


//Diffuse Light with Lambart
float Diffuse(float3 normal, float3 dirToLight)
{
	return saturate(dot(normal, dirToLight));
}

//Blinn-Phong Specular
float SpecularLight(float3 lightDirection,float3 normal,float3 dirToCamera,float shininess)
{
	float3 dirRefl = reflect(lightDirection, normal);
	return (shininess)? 0: pow(saturate(dot(dirRefl, dirToCamera)), shininess);
}

//Basic Lighiting

float4 BasicDirectLight(float3 normal, float3 lightDir, float3 dirToCamera, Light light, float4 surfaceColor,float shininess, float roughness)
{
	float dirNdotL = Diffuse(normal, lightDir);
	float dirSpec = SpecularLight(light.Direction, normal, dirToCamera, shininess);
	dirSpec *= (1.0f - roughness);
	return (dirNdotL*surfaceColor + dirSpec)*float4(light.Color, 1)*light.Intensity;
}

#endif