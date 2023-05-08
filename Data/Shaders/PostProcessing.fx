//====================================================================================================
// Filename:	NormalMapping.fx
// Created by:	Peter Chan
// Description:	Shader performing normal mapping.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer ConstantBuffer : register( b0 )
{
	int postProcessIndex;
	float timer;
};
//====================================================================================================
// Textures and Samplers
//====================================================================================================

Texture2D textureScene : register(t0);
SamplerState textureSampler : register(s0);

//====================================================================================================
// Structs
//====================================================================================================

struct VS_INPUT
{
	float4 position	: POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float4 color : COLOR;
	float2 texCoord	: TEXCOORD;
};

//----------------------------------------------------------------------------------------------------

struct VS_OUTPUT
{
	float4 position		: SV_POSITION;
	float2 texCoord		: TEXCOORD;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.position = input.position;
	output.texCoord = input.texCoord;
	
	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 color = textureScene.Sample(samplerLinear, input.texcoord);
	return color;
}
