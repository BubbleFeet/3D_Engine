//====================================================================================================
// Filename:	Skybox.fx
// Created by:	Peter Chan
// Description:	Shader performing cube mapping to a skybox.
//====================================================================================================

//====================================================================================================
// Constant Buffers
//====================================================================================================

cbuffer ConstantBuffer : register( b0 )
{
	matrix WVP;
}

TextureCube TextureSkybox : register(t0);
SamplerState SamplerLinear : register(s0);

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
	float3 texCoord	: TEXCOORD;
};

//====================================================================================================
// Vertex Shader
//====================================================================================================

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.position = mul(input.position, WVP);
	output.texCoord = input.position.xyz;

	return output;
}

//====================================================================================================
// Pixel Shader
//====================================================================================================

float4 PS(VS_OUTPUT input) : SV_Target
{
	return TextureSkybox.Sample(SamplerLinear, input.texCoord);
}