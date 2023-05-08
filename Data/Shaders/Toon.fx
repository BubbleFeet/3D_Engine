//====================================================================================================
// Filename:	Toon.fx
// Created by:	Peter Chan & Michael Logan
// Description:	Simple shader for toon shading.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer ConstantBuffer : register( b0 )
{
	matrix world;
	matrix wvp;
	float3 cameraPosition;
	float3 lightDirection;
	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
}

Texture2D diffuseMap : register(t0);
Texture2D gradientMap : register(t1);
SamplerState textureSampler : register(s0);
SamplerState textureSampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4 position	: POSITION;
	float3 normal	: NORMAL;
	float4 color	: COLOR;
	float2 texCoord	: TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR;
	float2 texCoord	: TEXCOORD;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.position = mul( input.position, wvp );
	
	float3 dirToLight = -normalize(lightDirection);
	float3 dirToView = normalize(cameraPosition - mul(input.position, world).xyz);
	float3 normal = normalize(mul(float4(input.normal, 0.0f), world).xyz);

	// Ambient
	float4 ambient = lightAmbient * materialAmbient;

	// Diffuse
	float d = saturate(dot(dirToLight, normal));
	float4 diffuse = d * lightDiffuse * materialDiffuse;

	// Specular
	float3 r = reflect(dirToLight, normal);
	float s = saturate(dot(dirToView, r));
	float4 specular = s * lightSpecular * materialSpecular;

	output.color = input.color;
	output.texCoord = input.texCoord;

	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	return input.color * diffuseMap.Sample(textureSampler, input.texCoord);
}