#include "TerrainTex.h"

USING(Engine)

CTerrainTex::CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
	, m_pPos(nullptr)
	, m_bClone(false)
	, m_dwCntX(0)
	, m_dwCntZ(0)
	, m_dwVtxItv(0)
{
}

CTerrainTex::CTerrainTex(const CTerrainTex& rhs)
	: CVIBuffer(rhs)
	, m_pPos(rhs.m_pPos)
	, m_bClone(true)
	, m_fH(rhs.m_fH)
	, m_iH(rhs.m_iH)

	, m_dwCntX(rhs.m_dwCntX)
	, m_dwCntZ(rhs.m_dwCntZ)
	, m_dwVtxItv(rhs.m_dwVtxItv)
{
}

CTerrainTex::~CTerrainTex(void)
{
}

HRESULT CTerrainTex::Initialize_Buffer(void)
{
	m_dwVtxCnt = m_dwCntX * m_dwCntZ;
	m_dwVtxFVF = FVF_TEX;
	m_dwTriCnt = (m_dwCntX - 1) * (m_dwCntZ - 1) * 2;

	m_pPos = new _vec3[m_dwVtxCnt];

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::Initialize_Buffer(), E_FAIL);

	_ulong			dwIndex = 0;
	VTXTEX*			pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);		// 1. 메모리 잠그는 역할, 2. 3인자를 통해서 저장된 버텍스 접근 권한을 얻음
												// 오른쪽 위 

	_float fPosX, fPosZ;
	for (_ulong z = 0; z < m_dwCntZ; ++z)
	{
		for (_ulong x = 0; x < m_dwCntX; ++x)
		{
			dwIndex = z * m_dwCntX + x;

			fPosX = static_cast<_float>(x * m_dwVtxItv);
			fPosZ = static_cast<_float>(z * m_dwVtxItv);
			pVertex[dwIndex].vPos = _vec3(fPosX, 0.f, fPosZ);

			m_pPos[dwIndex] = pVertex[dwIndex].vPos;

			pVertex[dwIndex].vNormal = _vec3(0.f, 0.f, 0.f);

			pVertex[dwIndex].vTexUV = _vec2(_float(x) / (m_dwCntX - 1) * 20.f,
				_float(z) / (m_dwCntZ - 1) * 20.f);
		}
	}

	_ulong	dwTriCnt = 0;

	INDEX32*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	for (_ulong z = 0; z < m_dwCntZ - 1; ++z)
	{
		for (_ulong x = 0; x < m_dwCntX - 1; ++x)
		{
			dwIndex = z * m_dwCntX + x;

			// 오른쪽 위
			pIndex[dwTriCnt]._0 = dwIndex + m_dwCntX;
			pIndex[dwTriCnt]._1 = dwIndex + m_dwCntX + 1;
			pIndex[dwTriCnt]._2 = dwIndex + 1;

			_vec3		vDest, vSour, vNormal;

			vDest = pVertex[pIndex[dwTriCnt]._1].vPos - pVertex[pIndex[dwTriCnt]._0].vPos;
			vSour = pVertex[pIndex[dwTriCnt]._2].vPos - pVertex[pIndex[dwTriCnt]._1].vPos;
			D3DXVec3Cross(&vNormal, &vDest, &vSour);

			pVertex[pIndex[dwTriCnt]._0].vNormal += vNormal;
			pVertex[pIndex[dwTriCnt]._1].vNormal += vNormal;
			pVertex[pIndex[dwTriCnt]._2].vNormal += vNormal;
			dwTriCnt++;

			// 왼쪽 아래
			pIndex[dwTriCnt]._0 = dwIndex + m_dwCntX;
			pIndex[dwTriCnt]._1 = dwIndex + 1;
			pIndex[dwTriCnt]._2 = dwIndex;

			vDest = pVertex[pIndex[dwTriCnt]._1].vPos - pVertex[pIndex[dwTriCnt]._0].vPos;
			vSour = pVertex[pIndex[dwTriCnt]._2].vPos - pVertex[pIndex[dwTriCnt]._1].vPos;
			D3DXVec3Cross(&vNormal, &vDest, &vSour);

			pVertex[pIndex[dwTriCnt]._0].vNormal += vNormal;
			pVertex[pIndex[dwTriCnt]._1].vNormal += vNormal;
			pVertex[pIndex[dwTriCnt]._2].vNormal += vNormal;

			dwTriCnt++;
		}
	}

	for (_ulong i = 0; i < m_dwVtxCnt; ++i)
		D3DXVec3Normalize(&pVertex[i].vNormal, &pVertex[i].vNormal);

	m_pVB->Unlock();
	m_pIB->Unlock();
	return S_OK;
}

void CTerrainTex::set_Data(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv)
{
	m_dwCntX = dwCntX;
	m_dwCntZ = dwCntZ;
	m_dwVtxItv = dwVtxItv;
}

CTerrainTex* CTerrainTex::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar * pFilePath)
{
	CTerrainTex* pInstance = new CTerrainTex(pGraphicDev);

	_ulong* pPixel = nullptr;
	if (nullptr != pFilePath)
	{
		pInstance->LoadFile(pFilePath, &pPixel);
	}

	if (FAILED(pInstance->Initialize_Buffer()))
	{
		Safe_Release(pInstance);
	}

	Safe_Delete_Array(pPixel);

	return pInstance;
}

CResources* CTerrainTex::Clone(void)
{
	return new CTerrainTex(*this);
}

void CTerrainTex::LoadFile(const _tchar* pFilePath, _ulong** ppPixel)
{
	_ulong	dwByte = 0;

#pragma region ReadFile
	HANDLE hFile = CreateFile(pFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	ReadFile(hFile, &m_fH, sizeof(BITMAPFILEHEADER), &dwByte, NULL);
	ReadFile(hFile, &m_iH, sizeof(BITMAPINFOHEADER), &dwByte, NULL);

	ReadFile(hFile, &m_dwCntX, sizeof(_ulong), &dwByte, NULL);
	ReadFile(hFile, &m_dwCntZ, sizeof(_ulong), &dwByte, NULL);
	ReadFile(hFile, &m_dwVtxItv, sizeof(_ulong), &dwByte, NULL);

	_ulong dwDrawIDNum = m_dwCntX * m_dwCntZ;

	//ReadFile(hFile, m_pByDrawID, sizeof(_byte) * dwDrawIDNum, &dwByte, NULL);

	*ppPixel = new _ulong[m_iH.biHeight * m_iH.biWidth];

	ReadFile(hFile, *ppPixel, sizeof(_ulong) * m_iH.biHeight * m_iH.biWidth, &dwByte, NULL);

	CloseHandle(hFile);
#pragma endregion
}

void CTerrainTex::Free(void)
{
	CVIBuffer::Free();

	if (false == m_bClone)
	{
		Safe_Delete_Array(m_pPos);
	}
}
