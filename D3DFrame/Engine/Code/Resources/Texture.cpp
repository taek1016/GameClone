#include "Texture.h"

USING(Engine)

CTexture::CTexture(LPDIRECT3DDEVICE9 pGraphicDev)
	: CResources(pGraphicDev)
	, m_iHeight(0)
	, m_iWidth(0)
{
}

CTexture::CTexture(const CTexture& rhs)
	: CResources(rhs)
	, m_iHeight(rhs.m_iHeight)
	, m_iWidth(rhs.m_iWidth)
{
	_uint	iContainerSize = static_cast<_uint>(rhs.m_vecTexture.size());
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
		D3DXIMAGE_INFO tInfo;
		D3DXGetImageInfoFromFile(szFileName, &tInfo);
		
		m_iHeight = tInfo.Height;
		m_iWidth = tInfo.Width;

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

void CTexture::Set_Texture(LPD3DXEFFECT & pEffect, const char * pShaderName, const _uint & iIndex)
{
	if (m_vecTexture.size() < iIndex)
		return;

	pEffect->SetTexture(pShaderName, m_vecTexture[iIndex]);
}

_int CTexture::Get_Height(void) const
{
	return m_iHeight;
}

_int CTexture::Get_Width(void) const
{
	return m_iWidth;
}

CTexture * CTexture::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar * pPath, TEXTURETYPE eType, const _uint & iCnt)
{
	CTexture*		pInstance = new CTexture(pGraphicDev);

	if (FAILED(pInstance->Initialize_Texture(pPath, eType, iCnt)))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CResources * CTexture::Clone(void)
{
	return new CTexture(*this);
}

inline void CTexture::Free(void)
{
	for_each(m_vecTexture.begin(), m_vecTexture.end(), CDeleteObj());
	m_vecTexture.clear();

	CResources::Free();
}