#include "stdafx.h"
#include "HPWarning.h"

#include "Character/Player.h"

USING(Engine)

CHPWarning::CHPWarning(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_fAlpha(0.f)
	, m_bUp(true)
{
	m_iPass = 1;
}

CHPWarning::CHPWarning(const CHPWarning & rhs)
	: CUIBase(rhs)
{
}

Engine::_int CHPWarning::Update_GameObject(const Engine::_float & fTimeDelta)
{
	auto pPlayer = dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front());

	if (pPlayer->Get_HPPercent() > 0.3f)
	{
		m_fAlpha = 0.f;
		m_bUp = true;
		return 0;
	}

	if (m_bUp)
	{
		m_fAlpha += fTimeDelta;
		if (m_fAlpha >= 1.f)
		{
			m_fAlpha = 1.f;
			m_bUp = false;
		}
	}
	else
	{
		m_fAlpha -= fTimeDelta;

		if (m_fAlpha <= 0.f)
		{
			m_fAlpha = 0.f;
			m_bUp = true;
		}
	}

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return Engine::_int();
}

HRESULT CHPWarning::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	CUIBase::setUp_ConstantTable(pEffect);

	pEffect->SetFloat("g_fAlpha", m_fAlpha);

	return S_OK;
}

CHPWarning * CHPWarning::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHPWarning* pInstance = new CHPWarning(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(L"LowHealth")))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_InitializeUI(&_vec3(0.f, 0.f, 0.f), &_vec3(WINCX, WINCY, 1.f));

	return pInstance;
}
