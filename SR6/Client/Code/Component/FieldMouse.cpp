#include "stdafx.h"
#include "FieldMouse.h"

USING(Engine)

CFieldMouse::CFieldMouse(void)
{
}

CFieldMouse::~CFieldMouse(void)
{
}

HRESULT CFieldMouse::Late_Initialize()
{
	m_pGameObject = DLL::pSearchMgr->Get_Object(L"Player");
	m_pTargetTransform = m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);

	m_pTransform = CTransform::Create();
	m_pTransform->Attach(this, ID_DYNAMIC);
	m_pTransform->Set_Pos(0.f, 0.f, 0.f);
	m_pTransform->Set_Scale(25.f, 25.f, 1.f);

	Set_MouseState();

	return S_OK;
}

HRESULT CFieldMouse::Initialize_GameObject()
{
	return S_OK;
}

Engine::_int CFieldMouse::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (DLL::pDirectInput->KeyDown(DIK_F11))
	{
		m_bFixed = !m_bFixed;
	}
	// 마우스 고정
	if (m_bFixed)
	{
		POINT		ptMouse{ WINCX >> 1, WINCY >> 1 };

		ClientToScreen(g_hWnd, &ptMouse);
		SetCursorPos(ptMouse.x, ptMouse.y);
	}

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return 0;
}

void CFieldMouse::Render_GameObject()
{
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	DLL::pResourceMgr->Render_Texture(RESOURCE_STAGE, Get_Name());
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

void CFieldMouse::Set_MouseState()
{
	if (m_iCurState == 0)
	{
		m_iCurState = 1;
		SetName(L"Cursor");
	}
	else
	{
		m_iCurState = 0;
		SetName(L"Cursor_no");
	}
}

CFieldMouse * CFieldMouse::Create()
{
	CFieldMouse*	pInstance = new CFieldMouse;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFieldMouse::LoadData(HANDLE hFile)
{
}

CGameObject * CFieldMouse::Clone(const _vec3 * pPos)
{
	return nullptr;
}
