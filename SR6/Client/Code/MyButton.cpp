#include "stdafx.h"
#include "MyButton.h"

USING(Engine)

CMyButton::CMyButton(void)
	: CGameObject()
{
}

CMyButton::CMyButton(const CMyButton & rhs)
	: CGameObject(rhs)
{
}

CMyButton::~CMyButton(void)
{
}

HRESULT CMyButton::Initialize_GameObject()
{
	CComponent*	pComponent = nullptr;

	m_pTransform = CTransform::Create();
	m_pTransform->Attach(this, ID_DYNAMIC);

	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_LOGO, m_wStrObjRenderKey.c_str()));

	return S_OK;
}

Engine::_int CMyButton::Update_GameObject(const Engine::_float & fTimeDelta)
{
	m_iIndex = 0;

	if (DLL::pColMgr->Collision_Mouse_To_Rect(&m_tRc, DLL::pMouseMgr->GetMousePos()))
	{
		m_iIndex = 1;
		if (DLL::pDirectInput->MousePress(DIM_LB))
		{
			m_bClicked = true;
		}
	}
	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return Engine::_int();
}

void CMyButton::Render_GameObject()
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();
	
	pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	m_pTexture->Render_Texture(m_iIndex);
}

Engine::_bool CMyButton::Get_Activate(void) const
{
	return m_bActivate;
}

void CMyButton::Set_RenderKey(const wstring & strObjRenderKey)
{
	m_wStrObjRenderKey = strObjRenderKey;
}

const wstring & CMyButton::Get_RenderKey(void) const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_wStrObjRenderKey;
}

void CMyButton::Setup_Btn(const Engine::_vec3 * pPos, 
	const Engine::_vec3 * pSize, 
	const Engine::_float& fWidth,
	const Engine::_float& fHeight)
{
	m_pTransform->Set_Pos(pPos);
	m_pTransform->Set_Scale(pSize);

	m_tRc.left = static_cast<LONG>(pPos->x);
	m_tRc.right = static_cast<LONG>(m_tRc.left + static_cast<LONG>(fWidth));
	m_tRc.top = static_cast<LONG>(pPos->y);
	m_tRc.bottom = static_cast<LONG>(m_tRc.top + static_cast<LONG>(fHeight));
}

CMyButton * CMyButton::Create(const wstring & wStrRenderKey, 
	const Engine::_vec3 * pPos, 
	const Engine::_vec3 * pSize, 
	const Engine::_float& fWidth,
	const Engine::_float& fHeight)
{
	CMyButton* pInstance = new CMyButton;
	pInstance->Set_RenderKey(wStrRenderKey);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (pInstance)
	{
		pInstance->Setup_Btn(pPos, pSize, fWidth, fHeight);
	}

	return pInstance;
}

Engine::CGameObject * CMyButton::Clone(const Engine::_vec3 * pPos)
{
	return nullptr;
}

void CMyButton::freeMem()
{
}

void CMyButton::LoadData(HANDLE hFile)
{
}
