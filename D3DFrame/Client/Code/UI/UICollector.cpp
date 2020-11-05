#include "stdafx.h"
#include "UICollector.h"

#include "Button.h"

#include "UI/SkillUI.h"
#include "UI/EquipUI.h"

USING(Engine)

CUICollector::CUICollector(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
{
}

CUICollector::~CUICollector(void)
{
}

Engine::_int CUICollector::Update_GameObject(const Engine::_float & fTimeDelta)
{
	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	for (auto iter : m_mapButtons)
	{
		iter.second->Update_GameObject(fTimeDelta);
	}
	
	if (m_mapButtons[L"CharacterSlotUI"]->Get_Clicked())
	{
		if (false == m_pEquipUI->Get_Activated())
		{
			DLL::pSoundMgr->PlaySound(L"EquipUIOpen.wav", CSoundMgr::EFFECT);
			DLL::pSoundMgr->SetVolume(CSoundMgr::EFFECT, 0.3f);
			m_pEquipUI->Activate();
			m_pSkillUI->DeActivate();
		}
		else
		{
			DLL::pSoundMgr->PlaySound(L"EquipUIClose.wav", CSoundMgr::EFFECT);
			DLL::pSoundMgr->SetVolume(CSoundMgr::EFFECT, 0.3f);
			m_pEquipUI->DeActivate();
		}
	}
	if (m_mapButtons[L"SkillSlotUI"]->Get_Clicked())
	{
		if (false == m_pSkillUI->Get_Activated())
		{
			DLL::pSoundMgr->PlaySound(L"EquipUIOpen.wav", CSoundMgr::EFFECT);
			DLL::pSoundMgr->SetVolume(CSoundMgr::EFFECT, 0.3f);

			m_pSkillUI->Activate();
			m_pEquipUI->DeActivate();
		}
		else
		{
			DLL::pSoundMgr->PlaySound(L"AbilityClosed.wav", CSoundMgr::EFFECT);
			DLL::pSoundMgr->SetVolume(CSoundMgr::EFFECT, 0.3f);

			m_pSkillUI->DeActivate();
		}
	}

	if (nullptr != m_pSkillUI && m_pSkillUI->Get_Activated())
	{
		m_pSkillUI->Update_GameObject(fTimeDelta);
	}
	else if (nullptr != m_pEquipUI && m_pEquipUI->Get_Activated())
	{
		m_pEquipUI->Update_GameObject(fTimeDelta);
	}

	return 0;
}

void CUICollector::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	m_pTexture->Render_Texture();
	m_pBuffer->Render_Buffer();
}

void CUICollector::Change_UI(const Engine::_tchar * pKey)
{
	//for (auto iter : m_mapButtons)
	//{
	//	if (0 == wcscmp(iter.second->Get_Name(), pKey))
	//	{

	//	}
	//	else
	//	{

	//	}
	//}
}

void CUICollector::make_Buttons(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	TCHAR* szName[] = { L"CharacterSlotUI", L"SkillSlotUI", L"TraitSlotUI" };
	const _int iSize = sizeof(szName) / sizeof(szName[0]);

	const _float fHalf = 0.5f;

	// 전체 315 픽셀 중 실제 사용할 수 있는 건 305 픽셀. (양 옆 경계면 제외)
	// 305 픽셀 / (iSize + 1)이 x 스케일 값. -> 양 쪽 끝을 계산해야해서.
	const _float fGapX = 30.f / 305.f * pScale->x;
	const _float fGapY = 10.f / 305.f * pScale->y;

	_vec3 vPos = *pPos;
	
	// 시작점
	vPos.x -= pScale->x * fHalf - 2 * fGapX;

	const _float fEachXWidth = 305.f / (iSize + 1)- fGapX;
	const _float fEachYHeight = pScale->y - 2 * fGapY;

	_vec3 vScale(fEachXWidth, fEachYHeight, 1.f);

	for (_int i = 0; i < iSize; ++i)
	{
		m_mapButtons.emplace(szName[i], CButton::Create(m_pGraphicDev, szName[i], &vPos, &vScale));
		vPos.x += fGapX + fEachXWidth;
	}
}

void CUICollector::make_UI(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	map<const Engine::_tchar*, const Engine::_int> mapSkillName;
	
	mapSkillName.emplace(L"FrostBolt", 0);
	mapSkillName.emplace(L"FrostNova", 2);
	mapSkillName.emplace(L"Chicken", 0);
	mapSkillName.emplace(L"Gryphon", 0);

	_vec3 vPos, vScale;
	vScale.x = 300.f;
	vScale.y = 600.f;
	vScale.z = 1.f;

	const _float fHalf = 0.5f;
	vPos.x = -WINCX * fHalf + vScale.x * fHalf;
	vPos.y = 0.f;
	vPos.z = 0.f;

	m_pSkillUI = CSkillUI::Create(m_pGraphicDev, &mapSkillName, &vPos, &vScale);
	m_pEquipUI = CEquipUI::Create(m_pGraphicDev, &vPos, &vScale);
}

CUICollector * CUICollector::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CUICollector* pInstance = new CUICollector(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(L"SlotBase")))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_InitializeUI(pPos, pScale)))
	{
		Safe_Release(pInstance);
	}

	pInstance->make_Buttons(pPos, pScale);
	pInstance->make_UI(pPos, pScale);

	return pInstance;
}

Engine::CGameObject * CUICollector::Clone(void)
{
	return nullptr;
}

inline void CUICollector::Free(void)
{
	CUIBase::Free();
	for (auto iter : m_mapButtons)
	{
		Safe_Release(iter.second);
	}
}
