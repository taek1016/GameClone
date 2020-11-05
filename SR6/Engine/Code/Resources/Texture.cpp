#include "Texture.h"

USING(Engine)

CTexture::CTexture(void)
	: CResources()
{
}

CTexture::CTexture(const CTexture& rhs)
	: CResources(rhs)
{
	_uint	iContainerSize = rhs.m_vecTexture.size();
	m_vecTexture.reserve(iContainerSize);

	m_vecTexture = rhs.m_vecTexture;

	for (_uint i = 0; i < iContainerSize; ++i)
		m_vecTexture[i]->AddRef();
}

CTexture::~CTexture(void)
{
}

HRESULT CTexture::Initialize_Texture(const _tchar * pPath, TEXTURETYPE eType, const _uint & iCnt)
{
	m_vecTexture.reserve(iCnt);

	IDirect3DBaseTexture9*		pTexture = nullptr;

	for (_uint i = 0; i < iCnt; ++i)
	{
		TCHAR		szFileName[256] = L"";
		wsprintf(szFileName, pPath, i);

		switch (eType)
		{
		case TEX_NORMAL:
			FAILED_CHECK_RETURN(D3DXCreateTextureFromFile(m_pGraphicDev, szFileName, (LPDIRECT3DTEXTURE9*)&pTexture), E_FAIL);
			break;

		case TEX_CUBE:
			FAILED_CHECK_RETURN(D3DXCreateCubeTextureFromFile(m_pGraphicDev, szFileName, (LPDIRECT3DCUBETEXTURE9*)&pTexture), E_FAIL);
			break;
		}

		m_vecTexture.push_back(pTexture);
	}

	return S_OK;
}

void CTexture::Render_Texture(const _uint & iIndex)
{
	if (m_vecTexture.size() < iIndex)
		return;

	m_pGraphicDev->SetTexture(0, m_vecTexture[iIndex]);
}

CTexture * CTexture::Create(const _tchar * pPath, TEXTURETYPE eType, const _uint & iCnt)
{
	CTexture*		pInstance = new CTexture();

	if (FAILED(pInstance->Initialize_Texture(pPath, eType, iCnt)))
		Safe_Release(pInstance);

	return pInstance;
}

CResources * CTexture::Clone(void)
{
	return new CTexture(*this);
}

HRESULT CTexture::Attach(CGameObject * pObj, COMPONENTID com_ID)
{
	m_pGameObject = pObj;
	m_pGameObject->Add_Component(COMPONENT_TYPE::TEXTURE, this, com_ID);

	return S_OK;
}

inline void CTexture::freeMem(void)
{
	for_each(m_vecTexture.begin(), m_vecTexture.end(), CDeleteObj());
	m_vecTexture.clear();
	CResources::freeMem();
}
