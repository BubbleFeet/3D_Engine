//====================================================================================================
// Filename:	Skinning.fx
// Created by:	Peter Chan
// Description:	Simple skinning shader.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer ConstantBuffer : register( b0 )
{
	matrix world;
	matrix wvp;
	vector cameraPosition;
	vector lightDirection;
	vector lightAmbient;
	vector lightDiffuse;
	vector lightSpecular;
	vector materialAmbient;
	vector materialDiffuse;
	vector materialSpecular;
	vector materialEmissive;
	float materialPower;
}

cbuffer BoneConstantBuffer : register(b1)
{
	matrix boneTransforms[128];
}

static matrix Identity = 
{
	1, 0, 0, 0
	0, 1, 0, 0
	0, 0, 1, 0
	0, 0, 0, 1
}

Texture2D diffuseMap : register(t0);
SamplerState textureSampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4 position		: POSITION;
	float3 normal		: NORMAL;
	float3 tangent		: TANGENT;
	float4 color		: COLOR;
	float2 texCoord		: TEXCOORD;
	int4 blendIndices	: BLENDINDICES;
	float4 blendWeights : BLENDWEIGHTS;
};

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR;
	float2 texCoord	: TEXCOORD;
};

//====================================================================================================
// Helpers
//====================================================================================================

matrix GetBoneTransform(int4 indices, float4 weights)
{
	matrix transform;
	transform  = boneTransform[indices[0]] * weights[0];
	transform += boneTransform[indices[1]] * weights[1];
	transform += boneTransform[indices[2]] * weights[2];
	transform += boneTransform[indices[3]] * weights[3];
	return transform;
}

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	
	matrix boneTransform = GetBoneTransform(input.blendIndices, input.blendWeight);

	float4 posBone = input.position;
	float4 posLocal = mul(posBone, boneTransform);
	float4 posWorld = mul(posLocal, world);
	float4 posProj = mul(posLocal, wvp);

	float3 normalBone = input.normal;
	float3 normalLocal = mul(float4(normalBone, 0.0f), boneTransform).xyz;
	float3 normalWorld = mul(float4(normalLocal, 0.0f), world).xyz;
	
	float3 dirToLight = -normalize(lightDirection);
	float3 dirToView = normalize(cameraPosition - mul(input.position, world).xyz);

	output.position = posProj;
	output.normal = normalWorld;
	output.dirToLight = dirToLight;
	output.dirToView = dirToView;
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