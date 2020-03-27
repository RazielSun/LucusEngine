
// Texture2D<float4> Tex : register(t0);
Texture2D textureDiffuse : register(t0);
SamplerState samplerLinear : register(s0);

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input) : SV_TARGET
{
	float4 color = textureDiffuse.Sample(samplerLinear, input.uv);
	return color;
}
