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


//------------Utility functions by Prof. Cascioli------

// Range-based attenuation function
float Attenuate(Light light, float3 worldPos)
{
	float dist = distance(light.Position, worldPos);

	// Ranged-based attenuation
	float att = saturate(1.0f - (dist * dist / (light.Range * light.Range)));

	// Soft falloff
	return att * att;
}

///------------------------------------------------------------------

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

float3 BasicDirectLight(float3 normal, Light light, float3 cameraPos, float3 worldPos, float4 surfaceColor,float shininess, float roughness)
{
	float3 dirToCamera = normalize(cameraPos - worldPos);
	float3 dirToLight = normalize(-light.Direction);

	float diff = Diffuse(normal, dirToLight);
	float spec = SpecularLight(dirToLight, normal, dirToCamera, shininess);
	spec *= (1.0f - roughness);
	return (diff*surfaceColor.rgb + spec)*light.Color.rgb*light.Intensity;
}

float3 BasicPointLight(float3 normal, Light light, float3 cameraPos, float3 worldPos, float4 surfaceColor, float shininess, float roughness)
{
	float3 dirToCamera = normalize(cameraPos - worldPos);
	float3 dirToLight = normalize(light.Position - worldPos);

	float attn = Attenuate(light, worldPos);
	float diff = Diffuse(normal, dirToLight);
	float spec = SpecularLight(dirToLight, normal, dirToCamera, shininess);
	spec *= (1.0f - roughness);

	return (diff * surfaceColor.rgb + spec) * attn * light.Intensity * light.Color.rgb;

 }


float3 BasicSpotLight(float3 normal, Light light, float3 cameraPos, float3 worldPos, float4 surfaceColor, float shininess, float roughness)
{
	float3 dirToLight = normalize(light.Position - worldPos);
	float3 dirToCamera = normalize(cameraPos - worldPos);
	float cosineSourcePixel = dot(-dirToLight, light.Direction);

	
		float penumbra = pow(saturate(dot(-dirToLight, light.Direction)), light.SpotFalloff);
		float attn = Attenuate(light, worldPos);
		float diff = Diffuse(normal, dirToLight);
		float spec = SpecularLight(dirToLight, normal, dirToCamera, shininess);
		spec *= (1.0f - roughness);

		return (diff * surfaceColor.rgb + spec) * attn * light.Intensity * light.Color.rgb * penumbra;
}

#endif