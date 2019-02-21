

struct DirectionalLight
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 direction;
};

struct PointLight
{
	float4 color;
	float3 position;
};


cbuffer externalData : register(b0)
{
	DirectionalLight directionalLight;
	float shininess;
	float3 cameraPos;
	float tmpfloat;//Just to fix padding
	PointLight pointLight;
}

//Texture and sampler buffers
Texture2D DiffuseTexture: register(t0);
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
	//return float4(input.uv,0,1);
	input.normal = normalize(input.normal);
	float3 dirToCamera = normalize(input.normal - input.worldPos);

	
	///DIRECTIONAL LIGHT--------------------------------------------------------
	float3 tmpLightDir = normalize(-directionalLight.direction);

	//Texture Sampling
	float4 surfaceColor = DiffuseTexture.Sample(BasicSampler, input.uv);

	// N dot L (Lambert / Diffuse) lighting
	// Note: We need the direction TO the light
	float dirNdotL = dot(input.normal, tmpLightDir);
	dirNdotL = saturate(dirNdotL); // Remember to CLAMP between 0 and 1

	// Specular calc for reflections (Phong)
	float3 dirRefl = reflect(directionalLight.direction, input.normal);
	float dirSpec = pow(saturate(dot(dirRefl, dirToCamera)), shininess);

	// Combine the surface and lighting
	float3 finalDirLight = surfaceColor * directionalLight.diffuseColor.rgb * dirNdotL
		+ directionalLight.ambientColor.rgb+ dirSpec.rrr;

	///PointLight------------------------------------------------------------------
	// Direction TO the point light from the surface
	float3 dirToPointLight = normalize(pointLight.position - input.worldPos);

	float3 pointNdotL = dot(input.normal, dirToPointLight);
	pointNdotL = saturate(pointNdotL); // Remember to CLAMP between 0 and 1

	// Specular calc for reflections (Phong)
	float3 pointRefl = reflect(-dirToPointLight, input.normal);
	float pointSpec = pow(saturate(dot(pointRefl, dirToCamera)), shininess);



	

	// Combine the surface and lighting
	float3 finalPointLight =
		surfaceColor * pointLight.color.rgb  * pointNdotL  + pointSpec.rrr; // Making the spec value into a float3

	return float4(finalDirLight+finalPointLight,1);
}