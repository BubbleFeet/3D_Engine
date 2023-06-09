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

	// Sobel Edge detection
	float deltaU = 1.0f / 1024.0f;
	float deltaV = 1.0f / 768.0f;
	float2 offset[9] =
	{
		float2(-deltaU, -deltaV),
		float2(0.0f, -deltaV),
		float2(deltaU, -deltaV),
		float2(-deltaU, 0.0f),
		float2(0.0f, 0.0f),
		float2(deltaU, 0.0f),
		float2(-deltaU, deltaV),
		float2(0.0f, deltaV),
		float2(deltaU, deltaV),
	};
	float kernelX[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	float kernelY[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

	float3 valX = (float3)0;
	float3 valY = (float3)0;
	for (int i = 0; i < 9; ++i)
	{
		float4 texColor = TextureScene.Sample(SamplerLinear, input.texcoord + offset[i]);
		valX += kernelX[i] * texColor.xyz;
		valY += kernelY[i] * texColor.xyz;
	}
	color *= (length((valX * valX) + (valY * valY)) > 0.3f) ? 0.0f : 1.0f;

	return color;
}
