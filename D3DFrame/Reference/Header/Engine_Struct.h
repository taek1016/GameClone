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
		_vec3			vNormal;
		_vec2		 	vTexUV;

	}VTXTEX;

	const _ulong		FVF_TEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	typedef	struct tagVertexCubeTexture
	{
		_vec3			vPos;
		_vec3		 	vTex;

	} VTXCUBE;

	const _ulong		FVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

	typedef struct tagVertexSphereTexture
	{
		_vec3			vPos;
	} VTX_DEBUG_SPHERE;

	const _ulong		FVF_DEBUG_SPHERE = D3DFVF_XYZ | D3DFVF_DIFFUSE;

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

	typedef struct D3DXFRAME_DERIVED : public D3DXFRAME
	{
		_matrix				CombinedTransformationMatrix;

	}D3DXFRAME_DERIVED;

	typedef struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER
	{
		LPDIRECT3DTEXTURE9*		ppTexture;

		LPD3DXMESH				pOriMesh;		// �ִϸ��̼� ��Ű���� ���� ���� �޽� ������ �����ϱ� ����(������ �޽��� ���� ���� ���� �ִ� �޽� ���� ��ü(���� �Һ�))

		_ulong					dwNumBones;		// ���� ����



		_matrix*				pFrameOffsetMatrix;			// ������ ������� ���� �ִ� ���(�ִϸ��̼��� ������ ���)


		_matrix**				ppFrameCombinedMatrix;		// ������ ���� �ִ� CombinedTransformationMatrix�� �ּҰ��� �����ϱ� ���� ���� ������(�� �����Ӹ��� ������ �ؾ��ϱ� ������ �Ź� ���� �������� ����� ������ ������ �� �ո����̴�. �׷��� �Ѳ����� �����Ϸ� �ϴ� ���̴�.)
		_matrix*				pRenderingMatrix;		   // �ᱹ ���� ���� ���� ���� �����ϴ� ���(pFrameOffsetMatrix * ppFrameCombinedMatrix[i])


	}D3DXMESHCONTAINER_DERIVED;

	typedef struct tagLine3D
	{
		tagLine3D()
			: dx(0.f), dy(0.f), dz(0.f)
			, px(0.f), py(0.f), pz(0.f)
		{

		}
		union
		{
			_vec3 vDir;
			struct
			{
				_float dx, dy, dz;
			};
			struct
			{
				_float a, b, c;
			};
		};

		union
		{
			_vec3 vPos;
			struct
			{
				_float px, py, pz;
			};
		};
	}LINE3D, *PLINE3D;

	typedef	struct tagVertexPointTexture
	{
		_vec3			vPos;
		_float			fPSize;
		_vec2			vTexUV;

	}VTXPTTEX;

	typedef	struct tagVertexMatrix
	{
		_vec4		vRight;
		_vec4		vUp;
		_vec4		vLook;
		_vec4		vPos;

	}VTXMATRIX;

}

#endif // Engine_Struct_h__
