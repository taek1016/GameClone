#include "stdafx.h"
#include "SkillExplaneSlot.h"

#include "UI/SkillSlot.h"

USING(Engine)

CSkillExplaneSlot::CSkillExplaneSlot(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
{
}

HRESULT CSkillExplaneSlot::Initialize_UI(const Engine::_tchar * pName)
{
	CTransform::Create()->Attach(L"Transform", this, ID_STATIC);

	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);

	return S_OK;
}

HRESULT CSkillExplaneSlot::Late_InitializeUI(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_STATIC);
	m_pTransform->Set_Info(INFO_POS, pPos);
	m_pTransform->Set_Scale(pScale);
	m_pTransform->Update_Component(0.f);

	m_pBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);

	return S_OK;
}

Engine::_int CSkillExplaneSlot::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (nullptr != m_pSkillSlot)
	{
		m_pSkillSlot->Update_GameObject(fTimeDelta);
	}

	_vec3 vPos(*m_pTransform->Get_Info(INFO_POS));
	vPos.x -= 15.f;
	vPos.y += 15.f;
	vPos.z = 0.f;

	_vec3 vScale(10.f, 15.f, 1.f);

	DLL::pFontMgr->Print_Font(&vPos, &vScale, 20, m_szSkillName, D3DXCOLOR(1.f, 1.f, 0.f, 1.f));

	vPos.y -= 25.f;
	DLL::pFontMgr->Print_Font(&vPos, &vScale, 20, m_szSkillLevelLimit, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	return 0;
}

void CSkillExplaneSlot::make_Slots(const Engine::_vec3* pPos, const Engine::_vec3* pScale, const Engine::_tchar* pSkillName, const Engine::_int& iLevelLimit)
{
	// 124, 38 픽셀
	const _float fTextureSize = 34.f;
	const _float fTotalWidth = 124.f;
	const _float fTotalHeight = 40.f;
	
	_vec3 vPos = *pPos;
	vPos.x -= 42.f / fTotalWidth * pScale->x;

	_vec3 vScale(fTextureSize / fTotalWidth * pScale->x, fTextureSize / fTotalHeight * pScale->y, 1.f);
	m_pSkillSlot = CSkillSlot::Create(m_pGraphicDev, &vPos, &vScale, -1, true);
	m_pSkillSlot->Set_Texture(pSkillName);
	m_pSkillSlot->Set_LevelLimit(iLevelLimit);

	::ZeroMemory(m_szSkillLevelLimit, sizeof(_tchar) * 32);
	wsprintf(m_szSkillLevelLimit, L"레벨제한:%d", iLevelLimit);

	::ZeroMemory(m_szSkillName, sizeof(_tchar) * 32);

	if (0 == wcscmp(pSkillName, L"FrostBolt"))
	{
		wsprintf(m_szSkillName, L"얼음 화살");
	}
	else if (0 == wcscmp(pSkillName, L"FrostNova"))
	{
		wsprintf(m_szSkillName, L"얼음 회오리");
	}
	else if (0 == wcscmp(pSkillName, L"Chicken"))
	{
		wsprintf(m_szSkillName, L"치킨 소환");
	}
	else if (0 == wcscmp(pSkillName, L"Gryphon"))
	{
		wsprintf(m_szSkillName, L"그리폰 소환");
	}
	//else if (0 == wcscmp(pSkillName, L""))
	//{

	//}
}

CSkillExplaneSlot * CSkillExplaneSlot::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_tchar * pSkillName, const Engine::_int iLevelLimit, const Engine::_tchar * pSkillExplanation)
{
	CSkillExplaneSlot* pInstance = new CSkillExplaneSlot(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->Get_Name())))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_InitializeUI(pPos, pScale)))
	{
		Safe_Release(pInstance);
	}

	pInstance->make_Slots(pPos, pScale, pSkillName, iLevelLimit);

	return pInstance;
}

Engine::CGameObject * CSkillExplaneSlot::Clone(void)
{
	return nullptr;
}

inline void CSkillExplaneSlot::Free(void)
{
	CUIBase::Free();

	Safe_Release(m_pSkillSlot);
}
