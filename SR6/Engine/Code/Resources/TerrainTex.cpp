#include "TerrainTex.h"
#include <iostream>
USING(Engine)

CTerrainTex::CTerrainTex(void)
	: CVIBuffer()
{
}

CTerrainTex::CTerrainTex(const CTerrainTex & rhs)
	: CVIBuffer(rhs)
{
}

CTerrainTex::~CTerrainTex(void)
{
}

void CTerrainTex::QuakeTerrain(_vec3 vPos, float fRange)
{
	BasicVertex* vertex = nullptr;
	m_pVB->Lock(0, 0, (void**)&vertex, 0);

	BasicVertex** arrVertex = new BasicVertex*[m_vecTerrainTex.size()];

	for (int i = 0; i < m_vecTerrainTex.size(); i++)
	{
		m_vecTerrainTex[i].pVB->Lock(0, 0, (void**)&arrVertex[i], 0);
	}

	
	
	// 해당 범위만큼 y값을 변경
	//for (int i = 0; i < fRange; i++)
	{
		int curIndex = 0;
		// 흔들 좌표의 중심으로 이동
		int index = (m_iXWidth * (int)vPos.z + (int)vPos.x);

		//현재 범위의(i) 최 좌측 최 상단으로 이동
		int leftTopIndex = (index + (fRange * m_iXWidth)) - fRange;
		/*for (int xIndex = 0; xIndex < fRange * 2; xIndex++)
		{
			
			curIndex = leftTopIndex++;
			(vertex + curIndex)->vPos.y = -y;
			for (int i = 0; i < m_vecTerrainTex.size(); i++)
			{
				(arrVertex[i] + curIndex)->vPos.y = -y;
			}
		}

		for (int zIndex = 0; zIndex < fRange * 2; zIndex++)
		{
			curIndex = leftTopIndex - (zIndex * m_iXWidth);
			for (int i = 0; i < m_vecTerrainTex.size(); i++)
			{
				(arrVertex[i] + curIndex)->vPos.y = -y;
			}
		}

		for (int xIndex = 0; xIndex < fRange * 2; xIndex++)
		{
			curIndex = leftTopIndex--;
			for (int i = 0; i < m_vecTerrainTex.size(); i++)
			{
				(arrVertex[i] + curIndex)->vPos.y = -y;
			}
		}

		for (int zIndex = 0; zIndex < fRange * 2; zIndex++)
		{
			curIndex = leftTopIndex + (zIndex * m_iXWidth);
			for (int i = 0; i < m_vecTerrainTex.size(); i++)
			{
				(arrVertex[i] + curIndex)->vPos.y = -y;
			}
		}*/

		/*최 좌측 상단부터 열 단위로 y값 변경
		1. ---------->
		2. ---------->
		3. ---------->
		4. ---------->
		5. ---------->*/

		int zIndex = 0;
		for (int moveZIndex = 0; moveZIndex < fRange * 2; moveZIndex++)
		{
			zIndex = -m_iXWidth * moveZIndex;
			for (int moveXIndex = 0; moveXIndex < fRange * 2; moveXIndex++)
			{
				curIndex = leftTopIndex + zIndex + moveXIndex;
				if (curIndex < 0 || curIndex > m_dwVtxCnt)
					continue;
				float y = 0.3f;
				if (y <= 0)
					y = 0.01f;
				(vertex + curIndex)->vPos.y -= y;
				for (int i = 0; i < m_vecTerrainTex.size(); i++)
				{
					(arrVertex[i] + curIndex)->vPos.y -= y;
				}
			}
		}
	}

	m_pVB->Unlock();

	for (int i = 0; i < m_vecTerrainTex.size(); i++)
	{
		m_vecTerrainTex[i].pVB->Unlock();
		
	}
	delete[] arrVertex;
}

HRESULT CTerrainTex::Initialize_Buffer()
{
	m_dwVtxSize = sizeof(BasicVertex);
	m_dwVtxFVF = FVF_TERRAIN;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;


	if (m_dwVtxCnt != 0 && m_dwTriCnt != 0)
	{
		if (CVIBuffer::Initialize_Buffer() == E_FAIL)
			MessageBox(NULL, L"CVIBuffer Init Failed", NULL, NULL);
	}
	return S_OK;
}

CTerrainTex * CTerrainTex::Create(const _ulong & dwCntX, const _ulong & dwCntZ, const _ulong & dwVtxItv)
{
	CTerrainTex*	pInstance = new CTerrainTex;
	pInstance->m_dwVtxCnt = 0;
	pInstance->m_dwTriCnt = 0;
	if (FAILED(pInstance->Initialize_Buffer()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

CResources * CTerrainTex::Clone()
{
	CTerrainTex* m_pTerrain = new CTerrainTex(*this);

	return m_pTerrain;
}
int i = 0;
int j = 0;
void CTerrainTex::Render_Buffer(LPDIRECT3DVERTEXBUFFER9 pVB)
{
	if (m_bQuake)
	{
		i++;
		
		if (i > 0)
		{
			QuakeTerrain(m_vQuakePoint, (int)j++);
			i = 0;
			if (j > m_fQuakeTime)
			{
				m_bQuake = false;
				j = 0;
			}
			
		}
	}

	m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	m_pGraphicDev->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	m_pGraphicDev->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pGraphicDev->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pGraphicDev->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	// 0번 인덱스 알파 텍스쳐는 전체에 한번만 그려져야 하므로
	// 타일화 셋팅 하지 않음
	m_pGraphicDev->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	m_pGraphicDev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	m_pGraphicDev->SetTextureStageState(1, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
	m_pGraphicDev->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
	m_pGraphicDev->SetSamplerState(1, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pGraphicDev->SetSamplerState(1, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	CVIBuffer::Render_Buffer();

	for (_ulong i = 0; i < m_vecTerrainTex.size(); i++)
	{
		m_pGraphicDev->SetTexture(0, m_vecTerrainTex[i].alphaTex);
		m_pGraphicDev->SetTexture(1, m_vecTerrainTex[i].blendedTex);
		CVIBuffer::Render_Buffer(m_vecTerrainTex[i].pVB);
	}

	m_pGraphicDev->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	m_pGraphicDev->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void CTerrainTex::SetVB(AlphamapTexture & alphaMap)
{
	if (alphaMap.pVB != nullptr)
		alphaMap.pVB->Release();
	FAILED_CHECK_RETURN(m_pGraphicDev->CreateVertexBuffer(m_dwVtxSize * m_dwVtxCnt,	// 생성할 버퍼의 크기
		0,					// 버퍼의 종류(숫자가 0인 경우 정적 버퍼)
		m_dwVtxFVF,			// 생성하는 버텍스의 속성값
		D3DPOOL_MANAGED,	// 메모리 풀의 설정
		&alphaMap.pVB,
		NULL),
		);

	BasicVertex* pVertices = nullptr;
	BasicVertex* pCurVertex = nullptr;
	BasicVertex vertex;
	alphaMap.pVB->Lock(0, 0, (void**)&pVertices, 0);
	pCurVertex = pVertices;
	for (int z = 0; z < m_iZWidth; z++)
	{
		for (int x = 0; x < m_iXWidth; x++)
		{
			vertex.vPos.x = _float(x);
			vertex.vPos.y = 0;
			vertex.vPos.z = _float(z);

			memcpy(&vertex.vVertical, &vertex.vPos, sizeof(_vec3));
			D3DXVec3Normalize(&vertex.vVertical, &vertex.vVertical);

			vertex.vTexPos.x = (float)x / (m_iXWidth - 1);
			vertex.vTexPos.y = (float)z / (m_iZWidth - 1);

			vertex.vBlendUV.x = (float)x / (m_iXWidth - 1) * alphaMap.fSize;
			vertex.vBlendUV.y = (float)z / (m_iZWidth - 1)* alphaMap.fSize;

			*pCurVertex++ = vertex;
		}

	}

	alphaMap.pVB->Unlock();
}

void CTerrainTex::LoadData(HANDLE hFile)
{
	DWORD dwBytes = 0;

	int garbage;
	_tchar* strGarbage[255];

	ReadFile(hFile, &garbage, sizeof(garbage), &dwBytes, nullptr);

	ReadFile(hFile, &m_dwVtxCnt, sizeof(m_dwVtxCnt), &dwBytes, nullptr);
	ReadFile(hFile, &m_dwTriCnt, sizeof(m_dwTriCnt), &dwBytes, nullptr);

	ReadFile(hFile, &m_iXWidth, sizeof(m_iXWidth), &dwBytes, nullptr);
	ReadFile(hFile, &m_iZWidth, sizeof(m_iZWidth), &dwBytes, nullptr);

	
	ReadFile(hFile, &garbage, sizeof(garbage), &dwBytes, nullptr);

	int size;
	ReadFile(hFile, &size, sizeof(size), &dwBytes, nullptr);
	ReadFile(hFile, strGarbage, size, &dwBytes, nullptr);

	Initialize_Buffer();

	ReadFile(hFile, &size, sizeof(size), &dwBytes, nullptr);

	for (int i = 0; i < size; i++)
	{
		int strSize;
		AlphamapTexture texture;
		ReadFile(hFile, &strSize, sizeof(strSize), &dwBytes, nullptr);
		ReadFile(hFile, texture.strAlphaTex, 255, &dwBytes, nullptr);
		ReadFile(hFile, &strSize, sizeof(strSize), &dwBytes, nullptr);
		ReadFile(hFile, texture.strBlendedTex, 255, &dwBytes, nullptr);
		ReadFile(hFile, &texture.fSize, sizeof(float), &dwBytes, nullptr);
		D3DXCreateTextureFromFile(m_pGraphicDev, texture.strAlphaTex, &texture.alphaTex);
		D3DXCreateTextureFromFile(m_pGraphicDev, texture.strBlendedTex, &texture.blendedTex);

		SetVB(texture);

		texture.pVB->Lock(0, 0, (void**)&m_pVertices, 0);

		for (_ulong i = 0; i < m_dwVtxCnt; i++)

		{
			ReadFile(hFile, &m_pVertices[i], sizeof(BasicVertex), &dwBytes, nullptr);
		}

		texture.pVB->Unlock();

		m_vecTerrainTex.push_back(texture);
	}
	m_pVertices = nullptr;
	m_pVB->Lock(0, 0, (void**)&m_pVertices, 0);

	for (_ulong i = 0; i < m_dwVtxCnt; i++)
	{
		ReadFile(hFile, &m_pVertices[i], sizeof(BasicVertex), &dwBytes, nullptr);
	}

	m_pVB->Unlock();

	m_pIndices = nullptr;
	m_pIB->Lock(0, 0, (void**)&m_pIndices, 0);

	for (_ulong i = 0; i < m_dwTriCnt; i++)
	{
		ReadFile(hFile, &m_pIndices[i], sizeof(m_pIndices[i]), &dwBytes, nullptr);
	}

	m_pIB->Unlock();
}

HRESULT CTerrainTex::Attach(CGameObject* pObj, COMPONENTID com_ID)
{
	m_pGameObject = pObj;
	m_pGameObject->Add_Component(COMPONENT_TYPE::BODY, this, com_ID);

	return S_OK;
}

inline void CTerrainTex::freeMem(void)
{
	CVIBuffer::freeMem();

}