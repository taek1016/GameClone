float4		g_vColor = float4(1.f, 1.f, 1.f, 1.f);

float4x4	g_matWorld;
float4x4	g_matView;
float4x4	g_matProj;

texture g_BaseTexture;
sampler FontSampler = sampler_state
{
	texture = g_BaseTexture;
};

struct VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vTexCoord : TEXCOORD0;
};

VS_OUTPUT VS_MAIN(VS_INPUT Input)
{
	VS_OUTPUT Output = (VS_OUTPUT)0;

	Output.vPosition.w = 1.f;

	Output.vPosition = mul(Input.vPosition, g_matWorld);
	Output.vPosition = mul(Output.vPosition, g_matView);
	Output.vPosition = mul(Output.vPosition, g_matProj);

	Output.vTexCoord = Input.vTexCoord;

	return Output;
}

struct PS_INPUT
{
	float4 vPosition : POSITION;
	float2 vTexCoord : TEXCOORD0;
};

struct PS_OUT
{
	vector			vColor : COLOR0;
};

PS_OUT PS_MAIN(PS_INPUT Input)
{
	PS_OUT Out = (PS_OUT)0;

	Out.vColor = tex2D(FontSampler, Input.vTexCoord);

	Out.vColor = Out.vColor * g_vColor;

	return Out;
}

technique 
{
	pass 
	{
		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader = compile ps_3_0 PS_MAIN();
	}
}