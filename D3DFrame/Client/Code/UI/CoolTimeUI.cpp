#include "stdafx.h"
#include "CoolTimeUI.h"

#include "Bar.h"
#include "SlotImage.h"
#include "Character/Player.h"

USING(Engine)

CCoolTimeUI::CCoolTimeUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_bActivated(false)
	, m_bSound(false)
	, m_fCurTime(0.f)
	, m_fCurSkillCoolTime(0.f)
	, m_fSoundTime(3.f)
	, m_pBar(nullptr)
	, m_pSlotImage(nullptr)
{
	set_Name(L"CastingUI");
}

Engine::_int CCoolTimeUI::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (false == m_bActivated && DLL::pSkillMgr->Is_SkillUsing())
	{
		auto pSkill = DLL::pSkillMgr->Get_CurrentSkillInfo();

		auto pSkillName = pSkill->pSkill->Get_Name();
		m_pSlotImage->Set_Texture(pSkillName);
		m_pBar->Set_Percent(0.f);
		m_fCurSkillCoolTime = pSkill->fCastingTime;

		if (false == m_bSound && 0 == wcscmp(L"FrostBolt", pSkillName))
		{
			m_bSound = true;
			m_pSoundName = L"FrostBolt.wav";
			m_fSoundTime = 3.f;
			m_fSoundLifeTime = 0.f;

			DLL::pSoundMgr->PlaySound(m_pSoundName, CSoundMgr::PLAYER);
			DLL::pSoundMgr->SetVolume(CSoundMgr::PLAYER, 0.3f);
		}
		else if (false == m_bSound && 0 == wcscmp(L"FrostNova", pSkillName))
		{
			m_bSound = true;
			m_pSoundName = L"FrostNova.wav";
			m_fSoundTime = 1.f;
			m_fSoundLifeTime = 0.f;

			DLL::pSoundMgr->PlaySound(m_pSoundName, CSoundMgr::PLAYER);
			DLL::pSoundMgr->SetVolume(CSoundMgr::PLAYER, 0.3f);
		}

		if (m_fCurSkillCoolTime < FLT_EPSILON)
		{
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front());
			if (pPlayer->Is_AnimationEnd())
			{
				DLL::pSkillMgr->Use_Skill();
				m_bActivated = false;
			}
			return 0;
		}
		m_bActivated = true;
	}
	else if (false == m_bActivated)
	{
		return 0;
	}

	m_fCurTime += fTimeDelta;

	if (m_bSound)
	{
		m_fSoundTime += fTimeDelta;
		if (m_fSoundLifeTime >= m_fSoundTime)
		{
			DLL::pSoundMgr->PlaySound(m_pSoundName, CSoundMgr::PLAYER);
			DLL::pSoundMgr->SetVolume(CSoundMgr::PLAYER, 0.3f);
		}
	}

	if (m_pBar)
	{
		m_pBar->Set_Percent(m_fCurTime / m_fCurSkillCoolTime);
		m_pBar->Update_GameObject(fTimeDelta);
	}

	if (m_pSlotImage)
	{
		m_pSlotImage->Update_GameObject(fTimeDelta);
	}

	if (m_fCurTime >= m_fCurSkillCoolTime)
	{
		CPlayer* pPlayer = dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front());
		if (pPlayer->Is_AnimationEnd())
		{
			DLL::pSoundMgr->PlaySound(L"IceCast.wav", CSoundMgr::PLAYER);
			DLL::pSoundMgr->SetVolume(CSoundMgr::PLAYER, 1.f);

			m_fCurTime = 0.f;
			DLL::pSkillMgr->Use_Skill();
			m_bSound = false;
		}
		m_bActivated = false;
	}

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return 0;
}

void CCoolTimeUI::make_Bar(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	// 전체 너비 256 전체 높이 64
	const _float fHalf = 0.5f;

	const _float fTotalWidth = 256.f;
	const _float fTotalHeight = 64.f;

	const _float fStartPosX = pPos->x - pScale->x * fHalf;

	_vec3 vPos = *pPos;
	vPos.x = fStartPosX;
	_vec3 vScale = *pScale;

	// 슬롯 너비, 높이는 20 20
	// 슬롯 시작 위치는 가로 21픽셀부터, 세로 31픽셀
	vScale.x = pScale->x * (20.f / fTotalWidth);
	vScale.y = pScale->y * (20.f / fTotalHeight);

	vPos.x += pScale->x * (20.f / fTotalWidth);
	vPos.y += pScale->y * (1.f / fTotalHeight);
	m_pSlotImage = CSlotImage::Create(m_pGraphicDev, &vPos, &vScale);

	vScale.x = 178.f / fTotalWidth * pScale->x;
	vScale.y = 12.f / fTotalHeight * pScale->y;

	vPos.x = fStartPosX + (217.f - 178.f * fHalf) / fTotalWidth * pScale->x;
	vPos.y = pPos->y;

	m_pBar = CCoolTimeBar::Create(m_pGraphicDev, &vPos, &vScale);
}

CCoolTimeUI * CCoolTimeUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CCoolTimeUI* pInstance = new CCoolTimeUI(pGraphicDev);

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
