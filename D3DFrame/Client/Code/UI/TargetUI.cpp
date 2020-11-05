#include "stdafx.h"
#include "TargetUI.h"

#include "HPBar.h"
#include "MPBar.h"
#include "SlotImage.h"

USING(Engine)

CTargetUI::CTargetUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_pHPBar(nullptr)
	, m_pMPBar(nullptr)
	, m_pSlotImage(nullptr)
{
	set_Name(L"TargetUI");
}

CTargetUI::~CTargetUI(void)
{
}

HRESULT CTargetUI::Set_Target(Engine::CGameObject * pObj)
{
	CUIBase::Set_Target(pObj);

	if (m_pHPBar)
	{
		m_pHPBar->Set_Target(pObj);
	}

	if (m_pMPBar)
	{
		m_pMPBar->Set_Target(pObj);
	}

	if (m_pSlotImage)
	{
		m_pSlotImage->Set_Texture(pObj->Get_Name());
	}

	return S_OK;
}

Engine::_int CTargetUI::Update_GameObject(const Engine::_float & fTimeDelta)
{
	m_pTarget = DLL::pMouseMgr->Get_PickTarget();

	if (nullptr == m_pTarget || false == is_MonsterTarget(m_pTarget->Get_Name()))
	{
		return 0;
	}

	CGameObject::Update_GameObject(fTimeDelta);

	auto pName = m_pTarget->Get_Name();
	print_TargetName(pName);

	if (m_pSlotImage)
	{
		m_pSlotImage->Set_Texture(pName);
		m_pSlotImage->Update_GameObject(fTimeDelta);
	}

	if (m_pHPBar)
	{
		m_pHPBar->Set_Target(m_pTarget);
		m_pHPBar->Update_GameObject(fTimeDelta);
	}

	if (m_pMPBar)
	{
		m_pMPBar->Set_Target(m_pTarget);
		m_pMPBar->Update_GameObject(fTimeDelta);
	}

	DLL::pRenderer->Add_RenderGroup(RENDERID::RENDER_UI, this);

	return 0;
}

void CTargetUI::print_TargetName(const Engine::_tchar * pName)
{
	::ZeroMemory(m_szName, sizeof(_tchar) * 64);

	if (0 == wcscmp(pName, L"Boar"))
	{
		wsprintf(m_szName, L"%s", L"돼지");
	}
	else if (0 == wcscmp(pName, L"Nefarian"))
	{
		wsprintf(m_szName, L"%s", L"네파리안");
	}
	else if (0 == wcscmp(pName, L"Infernal"))
	{
		wsprintf(m_szName, L"%s", L"인페르날");
	}
	else if (0 == wcscmp(pName, L"KodoBeast"))
	{
		wsprintf(m_szName, L"%s", L"코도비스트");
	}
	else if (0 == wcscmp(pName, L"Doomguard"))
	{
		wsprintf(m_szName, L"%s", L"둠가드");
	}

	const _int iStrLen = lstrlen(m_szName);

	auto pPos = m_pTransform->Get_Info(INFO_POS);
	auto pScale = m_pTransform->Get_Scale();

	const _float fHalf = 0.5f;
	
	const _float fPixelStartX = 64.f;
	const _float fPixelStartY = 21.f;

	const _float fTotalWidth = 188.f;
	const _float fTotalHeight = 69.f;

	_vec3 vScale(30.f, 30.f, 1.f);
	_vec3 vPos(pPos->x - pScale->x * fHalf + (fPixelStartX / fTotalWidth) * pScale->x - vScale.x * iStrLen * fHalf, 
		pPos->y + pScale->y * fHalf - (fPixelStartY / fTotalHeight) * pScale->y, 0.f);

	DLL::pFontMgr->Print_Font(&vPos, &vScale, 30, m_szName);
}

Engine::_bool CTargetUI::is_MonsterTarget(const Engine::_tchar * pName)
{
	const _tchar* pMonsterNames[] = { L"Boar", L"Nefarian", L"Infernal", L"KodoBeast", L"Doomguard" };
	const _int iCount = sizeof(pMonsterNames) / sizeof(pMonsterNames[0]);
	
	for (_int i = 0; i < iCount; ++i)
	{
		if (0 == wcscmp(pMonsterNames[i], pName))
		{
			return true;
		}
	}

	return false;
}

void CTargetUI::make_Bar(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	const _float fHalf = 0.5f;

	const _float fTotalWidth = 188.f;
	const _float fTotalHeight = 69.f;

	const _float fGapPercentWidth = 4.f / fTotalWidth;
	const _float fGapPercentHeight = 32.f / fTotalHeight;

	const _float fBarPercentWidth = 116.f / fTotalWidth;
	const _float fBarPercentHeight = 8.f / fTotalHeight;

	_vec3 vPos, vScale;
	
	vPos.x = pPos->x - pScale->x * fHalf + (fGapPercentWidth + fBarPercentWidth * fHalf) * pScale->x;
	vPos.y = pPos->y + pScale->y * fHalf - (fGapPercentHeight + fBarPercentHeight * fHalf) * pScale->y;
	vPos.z = 0.f;

	vScale.x = pScale->x * fBarPercentWidth;
	vScale.y = pScale->y * fBarPercentHeight;
	vScale.z = 1.f;

	m_pHPBar = CHPBar::Create(m_pGraphicDev, &vPos, &vScale);

	const _float fGapBetweenBar = 11.f / fTotalHeight;
	vPos.y -= pScale->y * fGapBetweenBar;
	m_pMPBar = CMPBar::Create(m_pGraphicDev, &vPos, &vScale);

	// 64, 69
	vPos = { pPos->x + pScale->x * fHalf - (32.f / fTotalWidth) * pScale->x, pPos->y + pScale->y * fHalf - 69.f * fHalf / fTotalHeight * pScale->y, 0.f };
	vScale = { 64.f / fTotalWidth * pScale->x, pScale->y, 1.f };

	m_pSlotImage = CSlotImage::Create(m_pGraphicDev, &vPos, &vScale);
}

CTargetUI * CTargetUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CTargetUI* pInstance = new CTargetUI(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->Get_Name())))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_InitializeUI(pPos, pScale)))
	{
		Safe_Release(pInstance);
	}

	pInstance->make_Bar(pPos, pScale);

	return pInstance;
}

Engine::CGameObject * CTargetUI::Clone(void)
{
	return nullptr;
}

inline void CTargetUI::Free(void)
{
	CUIBase::Free();
	Safe_Release(m_pHPBar);
	Safe_Release(m_pMPBar);
}