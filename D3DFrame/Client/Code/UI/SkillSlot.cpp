#include "stdafx.h"
#include "SkillSlot.h"

#include "Character/Player.h"

USING(Engine)

CSkillSlot::CSkillSlot(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSlotBase(pGraphicDev)
	, m_iInputNum(0)
	, m_bCopyOnly(false)
{
}

Engine::_int CSkillSlot::Update_GameObject(const Engine::_float & fTimeDelta)
{
	CSlotBase::Update_GameObject(fTimeDelta);

	if (-1 != m_iInputNum)
	{
		if (DLL::pInputMgr->KeyDown(m_iInputNum))
		{
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front());
			DLL::pSkillMgr->Casting_Skill(m_wTextureName.c_str());
		}
	}

	_vec3 vPos(*m_pTransform->Get_Info(INFO_POS));
	vPos.x += 10.f;
	vPos.x -= (lstrlen(m_szSkillNum) - 1) * 10.f;
	vPos.y += 20.f;
	_vec3 vScale(15.f, 20.f, 1.f);

	if (-1 != m_iInputData)
	{
		DLL::pFontMgr->Print_Font(&vPos, &vScale, 8, m_szSkillNum);
	}
	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return NO_EVENT;
}

void CSkillSlot::Set_Texture(const Engine::_tchar* pName)
{
	if (m_pTexture)
	{
		Safe_Release(m_pTexture);
	}

	m_wTextureName = pName;
	m_pTexture = DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, m_wTextureName.c_str());
}

void CSkillSlot::Click_Action(void)
{
	if (m_bClicked)
	{
		return;
	}

	m_bClicked = true;
	CStatCom* pPlayerStat = DLL::pObjMgr->Get_ObjList(L"Player")->front()->Get_Component<CStatCom>(L"Stat", ID_STATIC);

	if (pPlayerStat->Get_Level() < m_iLevelLimit)
	{
		return;
	}
	wstring wStrName = m_wTextureName;
	if (false == m_bCopyOnly)
	{
		wStrName = DLL::pMouseMgr->Get_ItemName();
	}
	DLL::pMouseMgr->Clear_Name();
	DLL::pMouseMgr->Set_ItemName(m_wTextureName.c_str());
	Set_Texture(wStrName.c_str());
}

void CSkillSlot::Set_LevelLimit(const Engine::_int & iLevelLimit)
{
	m_iLevelLimit = iLevelLimit;
}

void CSkillSlot::set_ActNum(const Engine::_int& iInputNum)
{
	m_iInputData = iInputNum;
	::ZeroMemory(m_szSkillNum, sizeof(_tchar) * 8);
	if (0 != iInputNum)
	{
		wsprintf(m_szSkillNum, L"%d", iInputNum);
	}

	switch (iInputNum)
	{
	case 1:
		m_iInputNum = DIK_1;
		break;

	case 2:
		m_iInputNum = DIK_2;
		break;

	case 3:
		m_iInputNum = DIK_3;
		break;

	case 4:
		m_iInputNum = DIK_4;
		break;

	case 5:
		m_iInputNum = DIK_5;
		break;

	case 6:
		m_iInputNum = DIK_6;
		break;

	case 7:
		m_iInputNum = DIK_7;
		break;

	case 8:
		m_iInputNum = DIK_8;
		break;

	case 9:
		m_iInputNum = DIK_9;
		break;

	case 10:
		m_iInputNum = DIK_0;
		break;

	case 11:
		m_iInputNum = DIK_MINUS;
		break;
	}
}

void CSkillSlot::set_CopyOnly(const Engine::_bool & bCopyOnly)
{
	m_bCopyOnly = bCopyOnly;
}

CSkillSlot * CSkillSlot::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_int& iInputNum, const Engine::_bool& bCopyOnly)
{
	CSkillSlot* pInstance = new CSkillSlot(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	pInstance->set_Data(pPos, pScale);
	pInstance->set_ActNum(iInputNum);
	pInstance->set_CopyOnly(bCopyOnly);

	return pInstance;
}
