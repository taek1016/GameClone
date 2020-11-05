#include "PtTex.h"

USING(Engine)

CPtTex::CPtTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
	, m_pVBTransform(nullptr)
	, m_pDeclaration(nullptr)
{
}

CPtTex::CPtTex(const CPtTex & rhs)
	: CVIBuffer(rhs)
	, m_pVBTransform(rhs.m_pVBTransform)
	, m_pDeclaration(rhs.m_pDeclaration)
{
	m_pVBTransform->AddRef();
	m_pDeclaration->AddRef();
}

CPtTex::~CPtTex(void)
{
}

HRESULT CPtTex::Initialize_Buffer(void)
{
	m_dwVtxCnt = 3;

	m_dwVtxSize = sizeof(VTXPTTEX);
	m_dwVtxFVF = 0;
	m_dwTriCnt = 3;

	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK_RETURN(CVIBuffer::Initialize_Buffer(), E_FAIL);

	VTXPTTEX*			pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);		// 1. �޸� ��״� ����, 2. 3���ڸ� ���ؼ� ����� ���ؽ� ���� ������ ����
												// ������ �� 
	pVertex[0].vPos = _vec3(0.f, 0.f, 0.f);
	pVertex[0].fPSize = 1.f;
	pVertex[0].vTexUV = _vec2(0.f, 0.f);

	pVertex[1].vPos = _vec3(0.f, 0.f, 0.f);
	pVertex[1].fPSize = 1.f;
	pVertex[1].vTexUV = _vec2(0.f, 0.f);

	pVertex[2].vPos = _vec3(0.f, 0.f, 0.f);
	pVertex[2].fPSize = 1.f;
	pVertex[2].vTexUV = _vec2(0.f, 0.f);

	m_pVB->Unlock();

	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexBuffer(sizeof(VTXMATRIX) * m_dwVtxCnt,
		0,
		m_dwVtxFVF,
		D3DPOOL_MANAGED,
		&m_pVBTransform,
		NULL),
		E_FAIL);

	D3DXMATRIX	matPivot;
	D3DXMatrixIdentity(&matPivot);


	VTXMATRIX* pVtxMatrix = NULL;

	m_pVBTransform->Lock(0, 0, (void**)&pVtxMatrix, 0);

	// 0�� ��ƼŬ
	pVtxMatrix[0].vRight = *(_vec4*)&matPivot.m[0][0];
	pVtxMatrix[0].vUp = *(_vec4*)&matPivot.m[1][0];
	pVtxMatrix[0].vLook = *(_vec4*)&matPivot.m[2][0];
	pVtxMatrix[0].vPos = *(_vec4*)&matPivot.m[3][0];

	// 1�� ��ƼŬ
	D3DXMatrixTranslation(&matPivot, 0.f, 0.f, 5.f);
	pVtxMatrix[1].vRight = *(_vec4*)&matPivot.m[0][0];
	pVtxMatrix[1].vUp = *(_vec4*)&matPivot.m[1][0];
	pVtxMatrix[1].vLook = *(_vec4*)&matPivot.m[2][0];
	pVtxMatrix[1].vPos = *(_vec4*)&matPivot.m[3][0];

	// 2�� ��ƼŬ
	D3DXMatrixTranslation(&matPivot, 0.f, 5.f, 5.f);
	pVtxMatrix[2].vRight = *(_vec4*)&matPivot.m[0][0];
	pVtxMatrix[2].vUp = *(_vec4*)&matPivot.m[1][0];
	pVtxMatrix[2].vLook = *(_vec4*)&matPivot.m[2][0];
	pVtxMatrix[2].vPos = *(_vec4*)&matPivot.m[3][0];

	m_pVBTransform->Unlock();

	D3DVERTEXELEMENT9		Element[MAX_FVF_DECL_SIZE] = {
		// 0�� ��Ʈ���� ����� ���ؽ��� ���� ���
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0 },
		{ 0, 12, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_PSIZE,		0 },
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0 },

		// 1�� ��Ʈ���� ����� ���ؽ��� ���� ���

		{ 1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT,	D3DDECLUSAGE_TEXCOORD,	1 },
		{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	2 },
		{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	3 },
		{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	4 },
		D3DDECL_END()

	};

	// ������ ������ ���� ������ �������� ������ ��ǥ�ϴ� �� ��ü ����
	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexDeclaration(Element, &m_pDeclaration), E_FAIL);

	INDEX16*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// 0
	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	// 1
	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}

void CPtTex::Render_Buffer(LPDIRECT3DVERTEXBUFFER9 pVB)
{
	m_pGraphicDev->SetVertexDeclaration(m_pDeclaration);	// setFVF�� ���������� ���� ������ �������ִ� �Լ�, 

															// ���� ������ 0�� ��Ʈ���� ���ε� ��Ű�� ����
	m_pGraphicDev->SetStreamSourceFreq(0, 1);	// ��ġ�� ��Ʈ���� � ���� ���ε���ų�� �����ϴ� �Լ�(1���� : ��Ʈ�� ��ȣ, 2���� : �ν��Ͻ� ������ŭ D3DSTREAMSOURCE_INDEXEDDATA �� OR ������ �Ͽ� �����ϸ� �������ϴ� �ν��Ͻ� ���� �������� ����, ��ƼŬ �ÿ� ���������� 1�� ���)
	m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);

	// ������ ������ 1�� ��Ʈ���� ���ε� ��Ű�� ����
	m_pGraphicDev->SetStreamSourceFreq(1, 1);	// ��ġ�� ��Ʈ���� � ���� ���ε���ų�� �����ϴ� �Լ�(1���� : ��Ʈ�� ��ȣ, 2���� : �ν��Ͻ� ������ŭ D3DSTREAMSOURCE_INSTANCEDATA �� OR ������ �Ͽ� �����ϸ� �������ϴ� �ν��Ͻ� ���� �������� ����, ��ƼŬ �ÿ� ���������� 1�� ���)
	m_pGraphicDev->SetStreamSource(1, m_pVBTransform, 0, sizeof(VTXMATRIX));

	m_pGraphicDev->DrawPrimitive(D3DPT_POINTLIST, 0, m_dwVtxCnt);

	// �ν��Ͻ� �����͸� ���������� ��ġ�� �� ��, ��Ʈ�� ���ļ��� �⺻ ���·� �������� �Ѵ�. 
	m_pGraphicDev->SetStreamSourceFreq(0, 1);
	m_pGraphicDev->SetStreamSourceFreq(1, 1);
}

CPtTex * CPtTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPtTex*	pInstance = new CPtTex(pGraphicDev);

	if (FAILED(pInstance->Initialize_Buffer()))
		Safe_Release(pInstance);

	return pInstance;
}

CResources * CPtTex::Clone(void)
{
	return new CPtTex(*this);
}

inline void CPtTex::Free(void)
{
	Safe_Release(m_pDeclaration);
	Safe_Release(m_pVBTransform);

	CVIBuffer::Free();
}
