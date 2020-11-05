matrix		g_matWorld;			// ��� ���̺�
matrix		g_matView;
matrix		g_matProj;

texture		g_BaseTexture;

float		g_fUVX = 1.f;
float		g_fUVY = 1.f;
float		g_fAlpha = 1.f;

float4		g_fColor;

sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;

minfilter = linear;
magfilter = linear;
mipfilter = linear;

/*addressU = mirror;
addressV = mirror;*/
};

struct VS_IN
{
	vector		vPosition : POSITION;
	float2		vTexUV : TEXCOORD0;

};

struct VS_OUT
{
	vector		vPosition : POSITION;
	float2		vTexUV : TEXCOORD0;

};

// ���ؽ� ���̴� �Լ�
VS_OUT		VS_MAIN(VS_IN In)
{
	VS_OUT		Out = (VS_OUT)0;

	matrix		matWV, matWVP;

	matWV = mul(g_matWorld, g_matView);
	matWVP = mul(matWV, g_matProj);

	Out.vPosition = mul(vector(In.vPosition.xyz, 1.f), matWVP);
	Out.vTexUV = In.vTexUV;

	Out.vTexUV.x *= g_fUVX;
	Out.vTexUV.y *= g_fUVY;

	return Out;
}

struct PS_IN // �ȼ� ���̴� ����ü���� POSITION�̶� Semantic�� ����� �� ����.
{
	float2			vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector			vColor : COLOR0;
};

PS_OUT		PS_MAIN(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV);	// 2���� ������ �ؽ����� UV��ǥ�� �ش��ϴ� ���� �����ϴ� �Լ�(��ȯ Ÿ���� VECTOR)


	return Out;
}

PS_OUT		PS_ALPHA(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	Out.vColor = tex2D(BaseSampler, In.vTexUV);

	Out.vColor *= g_fAlpha;

	return Out;
}

technique Default_Device
{
	// ����� ĸ��ȭ
	pass		Temp
	{

		ALPHABLENDENABLE = true;
		SrcBlENd = srcalpha;
		DESTblend = invsrcalpha;

		alphatestenable = true;
		alphafunc = greater;
		alpharef = 0xc0;
		cullmode = none;

		vertexshader = compile vs_3_0 VS_MAIN();		// ���ؽ� ���̴��� ������ �Լ� ����
		pixelshader = compile ps_3_0 PS_MAIN();		// ���ؽ� ���̴��� ������ �Լ� ����
	}
	
	pass
	{
		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader = compile ps_3_0 PS_ALPHA();
	}

	pass ALPHA
	{
		ALPHABLENDENABLE = true;
		SrcBlENd = srcalpha;
		DESTblend = invsrcalpha;

		alphatestenable = true;
		alphafunc = greater;
		alpharef = 0xc0;
		cullmode = none;

		vertexshader = compile vs_3_0 VS_MAIN();
		pixelshader = compile ps_3_0 PS_ALPHA();
	}

};