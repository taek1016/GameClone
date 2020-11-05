#include "BoxCollider.h"

USING(Engine)
CBoxCollider::CBoxCollider(LPDIRECT3DDEVICE9 pGraphic)
	: CCollider(pGraphic)
{
}

CBoxCollider::CBoxCollider(const CBoxCollider & rhs)
	: CCollider(rhs)
	, m_vMax(rhs.m_vMax)
	, m_vMin(rhs.m_vMin)
{
}

CBoxCollider::~CBoxCollider(void)
{
}

HRESULT CBoxCollider::Initialize_Collider(const _float& fWidth, const _float& fHeight, const _float& fDepth)
{
	//D3DXCreateBox
	D3DXCreateBox(m_pGraphicDev, fWidth, fHeight, fDepth, &m_pMesh, nullptr);

	set_Material();
	set_Texture();
	//VTXCUBE*		pVtxCube = nullptr;

	//m_pVB->Lock(0, 0, (void**)&pVtxCube, 0);

	//pVtxCube[0].vPos = _vec3(m_vMin.x, m_vMax.y, m_vMin.z);
	//pVtxCube[0].vTex = pVtxCube[0].vPos;

	//pVtxCube[1].vPos = _vec3(m_vMax.x, m_vMax.y, m_vMin.z);
	//pVtxCube[1].vTex = pVtxCube[1].vPos;

	//pVtxCube[2].vPos = _vec3(m_vMax.x, m_vMin.y, m_vMin.z);
	//pVtxCube[2].vTex = pVtxCube[2].vPos;

	//pVtxCube[3].vPos = _vec3(m_vMin.x, m_vMin.y, m_vMin.z);
	//pVtxCube[3].vTex = pVtxCube[3].vPos;


	//pVtxCube[4].vPos = _vec3(m_vMin.x, m_vMax.y, m_vMax.z);
	//pVtxCube[4].vTex = pVtxCube[4].vPos;

	//pVtxCube[5].vPos = _vec3(m_vMax.x, m_vMax.y, m_vMax.z);
	//pVtxCube[5].vTex = pVtxCube[5].vPos;

	//pVtxCube[6].vPos = _vec3(m_vMax.x, m_vMin.y, m_vMax.z);
	//pVtxCube[6].vTex = pVtxCube[6].vPos;

	//pVtxCube[7].vPos = _vec3(m_vMin.x, m_vMin.y, m_vMax.z);
	//pVtxCube[7].vTex = pVtxCube[7].vPos;

	//m_pVB->Unlock();

	//INDEX32*	pIndex = NULL;

	//m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	//// +x
	//pIndex[0]._0 = 1;
	//pIndex[0]._1 = 5;
	//pIndex[0]._2 = 6;

	//pIndex[1]._0 = 1;
	//pIndex[1]._1 = 6;
	//pIndex[1]._2 = 2;

	//// -x
	//pIndex[2]._0 = 4;
	//pIndex[2]._1 = 0;
	//pIndex[2]._2 = 3;

	//pIndex[3]._0 = 4;
	//pIndex[3]._1 = 3;
	//pIndex[3]._2 = 7;

	//// +y
	//pIndex[4]._0 = 4;
	//pIndex[4]._1 = 5;
	//pIndex[4]._2 = 1;

	//pIndex[5]._0 = 4;
	//pIndex[5]._1 = 1;
	//pIndex[5]._2 = 0;

	//// -y	 
	//pIndex[6]._0 = 3;
	//pIndex[6]._1 = 2;
	//pIndex[6]._2 = 6;

	//pIndex[7]._0 = 3;
	//pIndex[7]._1 = 6;
	//pIndex[7]._2 = 7;

	//// +z
	//pIndex[8]._0 = 7;
	//pIndex[8]._1 = 6;
	//pIndex[8]._2 = 5;

	//pIndex[9]._0 = 7;
	//pIndex[9]._1 = 5;
	//pIndex[9]._2 = 4;

	//// -z
	//pIndex[10]._0 = 0;
	//pIndex[10]._1 = 1;
	//pIndex[10]._2 = 2;

	//pIndex[11]._0 = 0;
	//pIndex[11]._1 = 2;
	//pIndex[11]._2 = 3;

	//m_pIB->Unlock();

	//for (_uint i = 0; i < COL_END; ++i)
	//{
	//	m_pGraphicDev->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_pTexture[i], NULL);

	//	D3DLOCKED_RECT	tLockRect;
	//	ZeroMemory(&tLockRect, sizeof(D3DLOCKED_RECT));

	//	m_pTexture[i]->LockRect(0, &tLockRect, NULL, NULL);

	//	*((_ulong*)tLockRect.pBits) = D3DXCOLOR(1.f * i, 1.f * (1.f - i), 0.f, 1.f);

	//	m_pTexture[i]->UnlockRect(0);
	//}

	return S_OK;
}

CBoxCollider * CBoxCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _float& fWidth, const _float& fHeight, const _float& fDepth)
{
	CBoxCollider* pInstance = new CBoxCollider(pGraphicDev);

	if (FAILED(pInstance->Initialize_Collider(fWidth, fHeight, fDepth)))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CBoxCollider::Clone(void)
{
	return new CBoxCollider(*this);
}
