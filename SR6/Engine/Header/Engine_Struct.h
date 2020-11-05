#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	typedef	struct tagVertexColor
	{
		_vec3			vPos;
		_ulong			dwColor;

	}VTXCOL;

	const _ulong		FVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	typedef	struct tagVertexTexture
	{
		_vec3			vPos;
		_vec2		 	vTexUV;

	}VTXTEX;

	const _ulong		FVF_TEX = D3DFVF_XYZ  | D3DFVF_TEX1;

	const _ulong		FVF_TERRAIN = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2;

	typedef	struct tagVertexCubeTexture
	{
		_vec3			vPos;
		_vec3		 	vTex;

	}VTXCUBE;


	const _ulong		FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

	typedef struct tagScreenVertex
	{
		_vec4				vPos;
		_vec2				vTexUV;

	}VTXSCREEN;

	const _ulong		FVF_SCREEN = D3DFVF_XYZRHW | D3DFVF_TEX1;

	typedef	struct tagIndex16
	{
		_ushort	_0, _1, _2;

	}INDEX16;

	typedef	struct tagIndex32
	{
		_ulong	_0, _1, _2;

	}INDEX32;

	struct AlphamapTexture
	{
		LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;
		LPDIRECT3DTEXTURE9	alphaTex;
		LPDIRECT3DTEXTURE9	blendedTex;

		_float				fSize = 1.f;

		_tchar				strAlphaTex[255];
		_tchar				strBlendedTex[255];
		AlphamapTexture()
		{
			ZeroMemory(strAlphaTex, sizeof(_tchar) * 255);
			ZeroMemory(strBlendedTex, sizeof(_tchar) * 255);
		}
	};

	struct BasicVertex
	{
		_vec3 vPos;
		_vec3 vVertical;
		_vec2 vTexPos;
		_vec2 vBlendUV;
	};

	typedef struct tagAnimTransformInfo
	{
		// 애니메이션이 시작하고부터 끝나는 시간까지의 변화량
		_vec3		vPosition;
		_vec3		vScale;
		_vec3		vRotation;
	}ANIM_TRANSFORM_INFO;

	typedef struct tagGravityInfo
	{
		float	fPower;
		float	fAcc;

		tagGravityInfo() : fPower(0.f) , fAcc(0.f) {}

		inline void	SetPower(const float& fValue) { fPower = fValue; }
		inline void	SetAcc(const float& fValue) { fAcc = fValue; }
		inline void	SetInitial() { fPower = 2.f; fAcc = 0.f; }
	}GRAVITY_INFO;

	typedef struct tagParticleAttribute
	{
		_vec3         vPos;
		_vec3         vVelocity;
		_vec3         vAcc;
		_float         fLifeTime;
		_float         fAge;
		_float         fFadeTime;
		_float         fCurFadeTime;
		D3DCOLOR      color;
		D3DXCOLOR      colorFade;
		bool         bIsAlive;

	}PARTICLEATTRIBUTE;

	typedef struct tagParticleTex
	{
		_vec3         vPos;
		float         fSize;
		D3DCOLOR      color;

	}VTX_PARTICLE;

	const _ulong      FVF_PARTICLE = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE;
}

#endif // Engine_Struct_h__
