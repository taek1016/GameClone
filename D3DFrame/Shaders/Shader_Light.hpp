texture			g_NormalTexture;

sampler NormalSampler = sampler_state		// ���͸��� ���� ���ƾ� �Ѵ�. �븻 ���͸� ���͸��ϰ� �Ǹ� ��� ���� ��߳� ���ɼ��� �ִ�.
{
	texture = g_NormalTexture;
};

texture			g_DepthTexture;

sampler DepthSampler = sampler_state		
{
	texture = g_DepthTexture;
};


vector		g_vLightDir;
vector		g_vLightDiffuse;
vector		g_vLightAmbient;

vector		g_vMtrlDiffuse = (vector)1.f;
vector		g_vMtrlAmbient = (vector)1.f;


vector		g_vCamPos;
float		g_fPower;

matrix		g_matViewInv;
matrix		g_matProjInv;

vector		g_vLightPos;
float		g_fRange;


struct PS_IN					// screen ������ xyzrhwf �����ǰ� �ؽ��� uv�� �����Ǿ� �־���. �ȼ����̴����� ��ġ ���� ����� �� ���� ������ �ؽ��� uv���� �������� �ִ�.
{
	float2		vTexUV : TEXCOORD0;
};

struct PS_OUT
{
	vector			vShade		: COLOR0;
	vector			vSpecular	: COLOR1;
};

PS_OUT		PS_MAIN_DIRECTIONAL(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;
	
	vector		vNormal = tex2D(NormalSampler, In.vTexUV);

	vNormal = vector(vNormal.xyz * 2.f - 1.f, 0.f);

	vector vDir = g_vLightDir * -1.f;

	Out.vShade = max(dot(normalize(vDir), vNormal), 0.f)
		* (g_vLightDiffuse * g_vMtrlDiffuse) + (g_vLightAmbient * g_vMtrlAmbient);
	
	Out.vShade.a = 1.f;

	vector		vReflect = reflect(normalize(vector(g_vLightDir.xyz, 0.f)), vNormal);

	vector		vDepth = tex2D(DepthSampler, In.vTexUV);
	float		vViewZ = vDepth.y * 1000.f;	// �� �����̽�

	vector		vPosition;

	vPosition.x = (In.vTexUV * 2.f - 1.f) * vViewZ;
	vPosition.y = (In.vTexUV * -2.f + 1.f) * vViewZ;
	vPosition.z = vDepth.x * vViewZ;
	vPosition.w = vViewZ;

	vPosition = mul(vPosition, g_matProjInv);
	vPosition = mul(vPosition, g_matViewInv);

	vector		vLook = normalize(g_vCamPos - vPosition);


	Out.vSpecular = pow(saturate(dot(vReflect, vLook)), g_fPower);


	return Out;
}

PS_OUT		PS_MAIN_POINT(PS_IN In)
{
	PS_OUT		Out = (PS_OUT)0;

	vector		vNormal = tex2D(NormalSampler, In.vTexUV);

	vNormal = vector(vNormal.xyz * 2.f - 1.f, 0.f);
		
	vector		vDepth = tex2D(DepthSampler, In.vTexUV);
	float		vViewZ = vDepth.y * 1000.f;	// �� �����̽�

	vector		vPosition;

	vPosition.x = (In.vTexUV * 2.f - 1.f) * vViewZ;
	vPosition.y = (In.vTexUV * -2.f + 1.f) * vViewZ;
	vPosition.z = vDepth.x * vViewZ;
	vPosition.w = vViewZ;

	vPosition = mul(vPosition, g_matProjInv);
	vPosition = mul(vPosition, g_matViewInv);

	vector vDir = vPosition - g_vLightPos;

	float fDistance = length(vDir);

	float	fAtt = saturate((g_fRange - fDistance) / g_fRange);

	Out.vShade = (max(dot(normalize(vDir), vNormal), 0.f)
		* (g_vLightDiffuse * g_vMtrlDiffuse) + (g_vLightAmbient * g_vMtrlAmbient)) * fAtt;
	
	Out.vShade.a = 1.f;

	vector		vReflect = reflect(normalize(vector(g_vLightDir.xyz, 0.f)), vNormal);
	vector		vLook = normalize(g_vCamPos - vPosition);
	
	Out.vSpecular = (pow(saturate(dot(vReflect, vLook)), g_fPower)) * fAtt;
	Out.vSpecular.a = 0.f;

	return Out;
}

technique Default_Device
{
	pass	Directional
	{
		alphablendenable = true;
		srcblend = one;
		destblend = one;

		zwriteEnable = false;
		vertexshader = NULL;
		pixelshader = compile ps_3_0 PS_MAIN_DIRECTIONAL();
	}

	pass Point
	{
		alphablendenable = true;
		srcblend = one;
		destblend = one;

		zwriteEnable = false;
		vertexshader = NULL;
		pixelshader = compile ps_3_0 PS_MAIN_POINT();
	}

};