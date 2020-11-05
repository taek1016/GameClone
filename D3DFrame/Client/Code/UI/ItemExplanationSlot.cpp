#include "stdafx.h"
#include "ItemExplanationSlot.h"

#include "UI/ShoppingSlot.h"

USING(Engine)

CItemExplanationSlot::CItemExplanationSlot(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_pItemSlot(nullptr)
{
}

HRESULT CItemExplanationSlot::Initialize_UI(const Engine::_tchar * pName)
{
	CTransform::Create()->Attach(L"Transform", this, ID_STATIC);

	return S_OK;
}

HRESULT CItemExplanationSlot::Late_InitializeUI(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_STATIC);
	m_pTransform->Set_Info(INFO_POS, pPos);
	m_pTransform->Set_Scale(pScale);
	m_pTransform->Update_Component(0.f);

	return S_OK;
}

Engine::_int CItemExplanationSlot::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (nullptr != m_pItemSlot)
	{
		m_pItemSlot->Update_GameObject(fTimeDelta);
	}

	return 0;
}

void CItemExplanationSlot::Render_GameObject(void)
{
}

void CItemExplanationSlot::make_ItemExplanation(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_tchar* pName)
{
	_vec3 vPos = *pPos;
	_vec3 vScale = *pScale;

	const _float fHalf = 0.5f;
	// 150 ÇÈ¼¿ Áß 40ÇÈ¼¿, 40ÇÈ¼¿ÀÌ »çÀÌÁî.
	const _float fStartXPos = pPos->x + 20.f / 150.f * pScale->x;
	const _float fStartYPos = pPos->y - pScale->y * fHalf;

	const _float fGapX = 10.f / 150.f * pScale->x;
	const _float fGapY = 5.f / 50.f * pScale->y;

	//vPos.x = fStartXPos + fGapX;
	//vPos.y = fStartYPos - fGapY;
	vPos.x = fStartXPos;
	vPos.y = fStartYPos;
	vScale = { 40.f, 40.f, 1.f };

	m_pItemSlot = CShoppingSlot::Create(m_pGraphicDev, &vPos, &vScale);
	m_pItemSlot->Set_Item(pName);
	m_pItemSlot->Initialize_Name();
}

CItemExplanationSlot * CItemExplanationSlot::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_tchar* pName)
{
	CItemExplanationSlot* pInstance = new CItemExplanationSlot(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(L"")))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_InitializeUI(pPos, pScale)))
	{
		Safe_Release(pInstance);
	}

	pInstance->make_ItemExplanation(pPos, pScale, pName);

	return pInstance;
}

Engine::CGameObject * CItemExplanationSlot::Clone(void)
{
	return nullptr;
}

inline void CItemExplanationSlot::Free(void)
{
	CUIBase::Free();

	Safe_Release(m_pItemSlot);
}
