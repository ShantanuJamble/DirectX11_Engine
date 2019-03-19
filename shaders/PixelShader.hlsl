#include "Lighting.hlsli"




cbuffer externalData : register(b0)
{
	Light lights[10];
	int numberOfLights;
	float shininess;
	float3 cameraPos;
}

//Texture and sampler buffers
Texture2D DiffuseTexture: register(t0);
Texture2D RoughnessTexture:register(t1);
SamplerState BasicSampler : register(s0);

// Defines the input to this pixel shader
// - Should match the output of our corresponding vertex shader
struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;
	float3 worldPos		: POSITION;
	float2 uv			: TEXCOORD;
};


float4 main(VertexToPixel input) : SV_TARGET
{
	// Just return the input color
	// - This color (like most values passing through the rasterizer) is 
	//   interpolated for each pixel between the corresponding vertices 
	//   of the triangle we're rendering
	//return float4(lights[0].Color,1);
	input.normal = normalize(input.normal);
	float3 dirToCamera = normalize(input.normal - input.worldPos);

	//Texture Sampling
	float4 surfaceColor = DiffuseTexture.Sample(BasicSampler, input.uv);
	
	float roughness = RoughnessTexture.Sample(BasicSampler, input.uv).r;
	roughness = lerp(0, roughness, 1);// x*(1-s) + y*s lerp(x,y,s)

	/////DIRECTIONAL LIGHT--------------------------------------------------------
	float3 tmpLightDir = normalize(-lights[0].Direction);
	


	

	
	
	//// Combine the surface and lighting
	/*float3 finalDirLight = surfaceColor.rgb * directionalLight.diffuseColor.rgb * dirNdotL
		+ directionalLight.Color.rgb + dirSpec.rrr;
*/
	

	float4 FinalDirectLight = BasicDirectLight(input.normal, tmpLightDir, dirToCamera, lights[0],surfaceColor, shininess, roughness);
	return FinalDirectLight;

	/////PointLight------------------------------------------------------------------
	//// Direction TO the point light from the surface
	//float3 dirToPointLight = normalize(pointLight.position - input.worldPos);

	//float3 pointNdotL = dot(input.normal, dirToPointLight);
	//pointNdotL = saturate(pointNdotL); // Remember to CLAMP between 0 and 1

	//// Specular calc for reflections (Phong)
	//float3 pointRefl = reflect(-dirToPointLight, input.normal);
	//float pointSpec = pow(saturate(dot(pointRefl, dirToCamera)), shininess);


	//// Combine the surface and lighting
	//float3 finalPointLight =
	//	surfaceColor.rgb * pointLight.color.rgb  * pointNdotL + pointSpec.rrr; // Making the spec value into a float3

	//return float4(finalDirLight + finalPointLight,1);
}