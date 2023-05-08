//====================================================================================================
// Filename:	DepthMap.fx
// Created by:	Peter Chan
// Description:	Shader for generating a depth map.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer CBPerObject : register( b0 )
{
	matrix WVP;
	float DisplacementScale;
}

Texture2D displacementMap : register(t0);
SamplerState textureSampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4 position	: POSITION;
	float3 normal	: NORMAL;
	float3 tangent	: TANGENT;
	float2 texCoord	: TEXCOORD;
};

//----------------------------------------------------------------------------------------------------

struct VS_OUTPUT
{
	float4 position	: SV_POSITION;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float displacement = displacementMap.SampleLevel(textureSampler, input.texCoord, 0).x;
	float4 position = input.position + (float4(input.normal, 0.0f) * DisplacementScale * displacement);
	float4 posProj = mul(position, WVP);

	output.position = posProj;
	
	return output;
}