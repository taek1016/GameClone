#include "CubeTex.h"

USING(Engine)

CCubeTex::CCubeTex() : CVIBuffer()
{

}

CCubeTex::CCubeTex(const CCubeTex & rhs) : CVIBuffer(rhs)
{
}

CCubeTex::~CCubeTex(void)
{
}

HRESULT CCubeTex::Initialize_Buffer(void)
{
	m_dwVtxSize = sizeof(VTXCUBE);
	m_dwVtxCnt = 8;
	m_dwVtxFVF = FVF_CUBE;
	m_dwTriCnt = 12;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	CVIBuffer::Initialize_Buffer();

	VTXCUBE* pVertices = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPos = m_vVertices[0];
	pVertices[0].vTex = pVertices[0].vPos;
	pVertices[1].vPos = m_vVertices[1];
	pVertices[1].vTex = pVertices[1].vPos;
	pVertices[2].vPos = m_vVertices[2];
	pVertices[2].vTex = pVertices[2].vPos;
	pVertices[3].vPos = m_vVertices[3];
	pVertices[3].vTex = pVertices[3].vPos;

	pVertices[4].vPos = m_vVertices[4];
	pVertices[4].vTex = pVertices[4].vPos;
	pVertices[5].vPos = m_vVertices[5];
	pVertices[5].vTex = pVertices[5].vPos;
	pVertices[6].vPos = m_vVertices[6];
	pVertices[6].vTex = pVertices[6].vPos;
	pVertices[7].vPos = m_vVertices[7];
	pVertices[7].vTex = pVertices[7].vPos;

	m_pVB->Unlock();

	INDEX32* indices = nullptr;

	m_pIB->Lock(0, 0, (void**)&indices, 0);

	indices[0] = { 0, 1, 2 };	indices[1] = { 0, 2, 3 };

	indices[2] = { 1, 5, 6 };	indices[3] = { 1, 6, 2 };

	indices[4] = { 5, 4, 7 };	indices[5] = { 5, 7, 6 };

	indices[6] = { 4, 0, 3 };	indices[7] = { 4, 3, 7 };

	indices[8] = { 4, 5, 1 };	indices[9] = { 4, 1, 0 };

	indices[10] = { 3, 2, 6 };	indices[11] = { 3, 6, 7 };

	m_pIB->Unlock();
	return E_NOTIMPL;
}

HRESULT CCubeTex::Attach(CGameObject * pObj, COMPONENTID com_ID)
{
	m_pGameObject = pObj;
	m_pGameObject->Add_Component(COMPONENT_TYPE::BUFFER, this, com_ID);

	return S_OK;
}

CResources * CCubeTex::Clone(void)
{
	CCubeTex* tex = new CCubeTex(*this);
	return tex;
}

void CCubeTex::LoadData(HANDLE hFile)
{

}

CCubeTex * CCubeTex::Create()
{
	CCubeTex* tex = new CCubeTex();
	tex->m_eComType = COMPONENT_TYPE::BUFFER;

	tex->m_vVertices[0] = _vec3(-0.5f, 0.5f, -0.5f);
	tex->m_vVertices[1] = _vec3(0.5f, 0.5f, -0.5f);
	tex->m_vVertices[2] = _vec3(0.5f, -0.5f, -0.5f);
	tex->m_vVertices[3] = _vec3(-0.5f, -0.5f, -0.5f);

	tex->m_vVertices[4] = _vec3(-0.5f, 0.5f, 0.5f);
	tex->m_vVertices[5] = _vec3(0.5f, 0.5f, 0.5f);
	tex->m_vVertices[6] = _vec3(0.5f, -0.5f, 0.5f);
	tex->m_vVertices[7] = _vec3(-0.5f, -0.5, 0.5f);

	tex->Initialize_Buffer();
	
	return tex;
}