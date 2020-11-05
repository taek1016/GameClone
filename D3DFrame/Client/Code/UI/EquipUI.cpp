#include "stdafx.h"
#include "EquipUI.h"

#include "EquipSlot/EquipBase.h"
#include "EquipSlot/ChestEquip.h"
#include "EquipSlot/FeetEquip.h"
#include "EquipSlot/HeadEquip.h"
#include "EquipSlot/ShoulderEquip.h"
#include "EquipSlot/WeaponEquip.h"

USING(Engine)

CEquipUI::CEquipUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_bActivated(false)
{
	set_Name(L"EquipUI");
	m_vecEquip.resize(ITEM_END);
}

Engine::_int CEquipUI::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	for (auto iter : m_vecEquip)
	{
		iter->Update_GameObject(fTimeDelta);
	}

	return iExit;
}

void CEquipUI::Activate(void)
{
	m_bActivated = true;
}

void CEquipUI::DeActivate(void)
{
	m_bActivated = false;
}

const Engine::_bool& CEquipUI::Get_Activated(void) const
{
	return m_bActivated;
}

void CEquipUI::make_Slots(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	// 전체 너비 280, 높이 480
	// x 포지션은 30 픽셀 위치로 고정
	// y 포지션은 100픽셀부터 50픽셀 단위로 5개.
	// 100 ~ 140	- 120
	// 150 ~ 190	- 170
	// 200 ~ 240	- 220
	// 250 ~ 290	- 270
	// 300 ~ 340	- 320
	const _float fHalf = 0.5f;
	const _float fTotalWidth = 280.f;
	const _float fTotalHeight = 480.f;

	const _float fXLeft = pPos->x - pScale->x * fHalf;
	const _float fYTop = pPos->y + pScale->y * fHalf;
	const _float fYGap = 50.f / fTotalHeight * pScale->y;

	_vec3 vPos, vScale;
	vScale.x = 40.f / fTotalWidth * pScale->x;
	vScale.y = 40.f / fTotalHeight * pScale->y;

	vPos.x = fXLeft + 30.f / fTotalWidth * pScale->x;
	vPos.y = fYTop - 120.f / fTotalHeight * pScale->y;
	vPos.z = 0.f;
	
	m_vecEquip[ITEM_HEAD] = CHeadEquip::Create(m_pGraphicDev, &vPos, &vScale);

	vPos.y -= fYGap;
	m_vecEquip[ITEM_SHOULDER] = CShoulderEquip::Create(m_pGraphicDev, &vPos, &vScale);

	vPos.y -= fYGap;
	m_vecEquip[ITEM_CHEST] = CChestEquip::Create(m_pGraphicDev, &vPos, &vScale);

	vPos.y -= fYGap;
	m_vecEquip[ITEM_WEAPON] = CWeaponEquip::Create(m_pGraphicDev, &vPos, &vScale);

	vPos.y -= fYGap;
	m_vecEquip[ITEM_FEET] = CFeetEquip::Create(m_pGraphicDev, &vPos, &vScale);
}

CEquipUI * CEquipUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CEquipUI* pInstance = new CEquipUI(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->Get_Name())))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_InitializeUI(pPos, pScale)))
	{
		Safe_Release(pInstance);
	}

	pInstance->make_Slots(pPos, pScale);
	
	return pInstance;
}

inline void CEquipUI::Free(void)
{
	CUIBase::Free();

	for (auto iter : m_vecEquip)
	{
		Safe_Release(iter);
	}
	m_vecEquip.clear();
}
