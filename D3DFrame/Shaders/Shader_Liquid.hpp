float g_fTime;

float4x4 g_matWorld;
float4x4 g_matView;
float4x4 g_matProj;

float4 g_vLightPos;
float4 g_vCameraPos;

texture g_DiffuseSampler_Tex;

sampler DiffuseSampler = sampler_state
{
	texture = g_DiffuseSampler_Tex;

	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};


struct VS_INPUT
{
	float4 vPosition : POSITION;
	float2 vUV : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 vPosition : POSITION;
	float2 vUV : TEXCOORD0;
};

VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT	Output = (VS_OUTPUT)0;

	matrix		matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Output.vPosition = mul(vector(Input.vPosition.xyz, 1.f), matWVP);

	Output.vUV = Input.vUV;

	return Output;
}

struct PS_INPUT
{
	float2 vUV			: TEXCOORD0;
	//float3 vDiffuse		: TEXCOORD1;
	//float3 vViewDir		: TEXCOORD2;
	//float3 vReflection	: TEXCOORD3;
};

float3 g_LightColor;

float4 ps_main(PS_INPUT Input) : COLOR
{
	return tex2D(DiffuseSampler, Input.vUV);
}

technique
{
	pass 
	{
		alphatestenable = true;
		alphafunc = greater;
		alpharef = 0xc0;
		cullmode = none;

		ALPHABLENDENABLE = true;
		SrcBlENd = srcalpha;
		DESTblend = invsrcalpha;

		vertexshader = compile vs_3_0 vs_main();
		pixelshader = compile ps_3_0 ps_main();
	}
}