
cbuffer UniformsBuffer : register(b0)
{
	matrix mvp;
	matrix projection;
	matrix view;
	matrix model;
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
	float3 pos : POSITION;
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR;
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;

	// Pass the position
    float4 pos = float4(input.pos, 1.0f);

	float3 color = input.pos;

	// Transform the vertex position into projected space.
	pos = mul(pos, mvp);
	//pos = mul(pos, model);
	//pos = mul(pos, view);
	//pos = mul(pos, projection);

	output.pos = pos;
	output.color = color;

	return output;
}
