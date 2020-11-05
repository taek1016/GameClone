#include "stdafx.h"
#include "CoinBase.h"

USING(Engine)

CCoinBase::CCoinBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_iCoinNum(0)
	, m_iFontHeight(0)
	, m_iFontWidth(0)
{
}

Engine::_int CCoinBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	_vec3 vScale(*m_pTransform->Get_Scale());
	_vec3 vPos(*m_pTransform->Get_Info(INFO_POS));
	vPos.x += vScale.x * 1.5f;

	wsprintf(m_szCoinNum, L"%d", m_iCoinNum);
	DLL::pFontMgr->Print_Font(&vPos, &vScale, 5, m_szCoinNum);
	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return iExit;
}

void CCoinBase::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	if (m_pTexture)
	{
		m_pTexture->Render_Texture();
		m_pBuffer->Render_Buffer();
	}

	// fontMgr ¤¡¤¡
}

void CCoinBase::set_FontSize(const Engine::_int & iFontWidth, const Engine::_int & iFontHeight)
{
	m_iFontWidth = iFontWidth;
	m_iFontHeight = iFontHeight;
}
