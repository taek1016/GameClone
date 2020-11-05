#include "stdafx.h"
#include "FontMgr.h"

#include "Font.h"

USING(Engine)
IMPLEMENT_SINGLETON(CFontMgr)

CFontMgr::CFontMgr(void)
{
}

CFontMgr::~CFontMgr(void)
{
	Free();
}

void CFontMgr::Update_Font(const Engine::_float & fTimeDelta)
{
	if (false == m_wstrActivateKey.empty())
	{
		m_Font[m_wstrActivateKey]->Update_GameObject(fTimeDelta);
	}
}

void CFontMgr::Add_SingleFont(const Engine::_tchar * pFontType, const Engine::_tchar * pKey, Engine::CTexture * pTexture)
{
	CFont* pFont = find_Font(pFontType);

	if (nullptr == pFont)
	{
		return;
	}
	else
	{
		pFont->Add_Font(pKey, pTexture);
	}
}

void CFontMgr::Create_Font(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar * pKey)
{
	CFont* pFont = find_Font(pKey);

	if (nullptr == pFont)
	{
		pFont = CFont::Create(pGraphicDev);

		m_Font.emplace(pKey, pFont);
	}
	else
	{
		return;
	}
}

void CFontMgr::Activate_Font(const Engine::_tchar * pKey)
{
	m_wstrActivateKey = pKey;
}

void CFontMgr::Print_Font(const Engine::_vec3* pPos, const Engine::_vec3* pScale,
						const Engine::_int& _iLinePerCount, const Engine::_tchar* pText,
						const D3DXCOLOR& _tColor)
{
	m_Font[m_wstrActivateKey.c_str()]->Push_FontData(FONT_INFO(pPos, pScale, _iLinePerCount, pText, _tColor));
}



CFont * CFontMgr::find_Font(const Engine::_tchar * pKey)
{
	auto iter = m_Font.find(pKey);

	if (m_Font.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

inline void CFontMgr::Free(void)
{
	for (auto iter : m_Font)
	{
		Safe_Release(iter.second);
	}
	m_Font.clear();
}
