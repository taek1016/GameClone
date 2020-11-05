#include "stdafx.h"
#include "PlayerUI.h"

#include "HPBar.h"
#include "MPBar.h"

USING(Engine)

CPlayerUI::CPlayerUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_pHPBar(nullptr)
	, m_pMPBar(nullptr)
	, m_pTargetStat(nullptr)
{
	set_Name(L"PlayerUI");
}

CPlayerUI::~CPlayerUI(void)
{
}

HRESULT CPlayerUI::Set_Target(Engine::CGameObject * pObj)
{
	CUIBase::Set_Target(pObj);
	m_pTargetStat = m_pTarget->Get_Component<CStatCom>(L"Stat", ID_STATIC);

	if (m_pHPBar)
	{
		m_pHPBar->Set_Target(pObj);
	}

	if (m_pMPBar)
	{
		m_pMPBar->Set_Target(pObj);
	}

	auto pPos = m_pTransform->Get_Info(INFO_POS);
	auto pScale = m_pTransform->Get_Scale();

	m_vLevelScale = { 20.f, 30.f, 1.f };

	m_vLevelPos = { pPos->x - pScale->x * 0.5f, pPos->y - pScale->y * 0.5f, 0.f };
	m_vLevelPos.x += 45.f / 128.f * pScale->x;
	m_vLevelPos.y += 28.f / 64.f * pScale->y;

	return S_OK;
}

Engine::_int CPlayerUI::Update_GameObject(const Engine::_float & fTimeDelta)
{
	Set_Target(DLL::pObjMgr->Get_ObjList(L"Player")->front());

	CGameObject::Update_GameObject(fTimeDelta);

	if (m_pHPBar)
	{
		m_pHPBar->Update_GameObject(fTimeDelta);
	}

	if (m_pMPBar)
	{
		m_pMPBar->Update_GameObject(fTimeDelta);
	}

	wsprintf(m_szLevel, L"%d", m_pTargetStat->Get_Level());
	
	DLL::pFontMgr->Print_Font(&m_vLevelPos, &m_vLevelScale, 30, m_szLevel);

	DLL::pRenderer->Add_RenderGroup(RENDERID::RENDER_UI, this);

	return 0;
}

void CPlayerUI::Render_GameObject(void)
{
	m_iIndex = 0;
	CUIBase::Render_GameObject();

	//m_iIndex = 1;
	//CUIBase::Render_GameObject();
}

void CPlayerUI::Change_UI(const Engine::_tchar * pKey)
{
	if (0 == wcscmp(pKey, L"HPBar"))
	{
		m_pHPBar->Calculate_HPBar();
	}

	else if (0 == wcscmp(pKey, L"MPBar"))
	{
		m_pMPBar->Calculate_MPBar();
	}
}

void CPlayerUI::make_Bar(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	_vec3 vPos = *pPos;
	_vec3 vScale = *pScale;
	const _float fHalf = 0.5f;

	// 시작점 잡기
	vPos.x -= vScale.x * fHalf;
	vPos.y += vScale.y * fHalf;

	// 전체 가로 128픽셀, 세로 64픽셀
	const _float fPixelWidth = 128.f;
	const _float fPixelHeight = 64.f;
	const _float fBarHeightInPixel = 5.f;
	const _float fPixelBarWidth = 68.f;
	const _float fPixelBarHeight = 9.f;

	const _float fPixelStartWidth = 47.f;
	const _float fPixelStartHeight = 15.f;

	_float fXRatio = (fPixelBarWidth * fHalf + fPixelStartWidth) / fPixelWidth;
	_float fYRatio = (fPixelStartHeight) / fPixelHeight;

	const _float fCorrection = fBarHeightInPixel / fPixelHeight;
	// 위치값 지정
	vPos.x += vScale.x * fXRatio;
	vPos.y -= pScale->y * fYRatio;

	// 가로 47 픽셀 이후, 69픽셀만큼 HP바.
	// 높이 총 64 픽셀, 바 높이 5픽셀
	fXRatio = fPixelBarWidth / fPixelWidth;
	fYRatio = fPixelBarHeight / fPixelHeight;

	vScale.x = pScale->x * fXRatio;
	vScale.y = pScale->y * fYRatio;
	// 위에서부터 12픽셀 이후 HP 바.
	// HP 바 :	위에서 12픽셀 이후 높이 5픽셀
	//			가로 총 68픽셀
	m_pHPBar = CHPBar::Create(m_pGraphicDev, &vPos, &vScale);

	const _float fHpBetweenMp = 9.f;
	// MP 바 :	HP바 끝난 뒤 3픽셀
	// 전체 높이 / 높이 + 전체 y 스케일 중 5픽셀 비율 * 반
	vPos.y -= pScale->y * (fHpBetweenMp / fPixelBarWidth);
	m_pMPBar = CMPBar::Create(m_pGraphicDev, &vPos, &vScale);
}

CPlayerUI * CPlayerUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CPlayerUI* pInstance = new CPlayerUI(pGraphicDev);

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

Engine::CGameObject * CPlayerUI::Clone(void)
{
	return nullptr;
}

inline void CPlayerUI::Free(void)
{
	CUIBase::Free();
	Safe_Release(m_pHPBar);
	Safe_Release(m_pMPBar);
}