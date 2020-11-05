#include "stdafx.h"
#include "MouseMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CMouseManager)

CMouseManager::CMouseManager(void)
	: CGameObject(DLL::pGraphicDev->GetDevice())
	, m_pPickTarget(nullptr)
	, m_pMouseBuffer(nullptr)
	, m_pTargetBuffer(nullptr)
	, m_pTargetTexture(nullptr)
	, m_pMouseTexture{nullptr}
	
	, m_eCurMouseState(MOUSE_NORMAL)

	, m_bActivated(false)
	, m_bClicked(false)
	
	, m_fClickCool(0.f)
{
	ShowCursor(FALSE);

	D3DXMatrixIdentity(&m_matTargetWorld);
	D3DXMatrixIdentity(&m_matMouseWorld);
}

CMouseManager::~CMouseManager(void)
{
	ShowCursor(TRUE);
	Free();
}


HRESULT CMouseManager::Late_Initialize(void)
{
	m_pMouseTexture = Get_Component<CTexture>(L"Texture", ID_STATIC);
	m_pMouseBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);

	m_pTargetBuffer = Get_Component<CRcTex>(L"TargetBuffer", ID_STATIC);

	return S_OK;
}

HRESULT CMouseManager::Initialize_GameObject(void)
{
	DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, L"Cursor")->Attach(L"Texture", this, ID_STATIC);
	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);
	CRcTex::Create(m_pGraphicDev)->Attach(L"TargetBuffer", this, ID_STATIC);

	m_vMouseScale = { 30.f, 30.f, 1.f };
	m_vTargetScale = { 50.f, 50.f, 1.f };

	return S_OK;
}

_int CMouseManager::Update_GameObject(const _float & fTimeDelta)
{
	if (false == m_bActivated)
	{
		return 0;
	}

	Set_MouseMode(MOUSE_NORMAL);

	if (m_bClicked)
	{
		m_fClickCool += fTimeDelta;
		if (m_fClickCool >= 0.2f)
		{
			m_fClickCool = 0.f;
			m_bClicked = false;
		}
	}
	_int iExit = 0;

	get_MousePos();
	
	_matrix matTrans, matScale;

	const _float fMousePickPointGap = 15.f;
	D3DXMatrixScaling(&matScale, m_vMouseScale.x, m_vMouseScale.y, m_vMouseScale.z);
	D3DXMatrixTranslation(&matTrans, m_vMouseInViewport.x + fMousePickPointGap, m_vMouseInViewport.y - fMousePickPointGap, m_vMouseInViewport.z);

	m_matMouseWorld = matScale * matTrans;

	if (nullptr != m_pTargetTexture)
	{
		D3DXMatrixScaling(&matScale, m_vTargetScale.x, m_vTargetScale.y, m_vTargetScale.z);
		m_matTargetWorld = matScale * matTrans;
	}

	return iExit;
}

void CMouseManager::Late_Update(void)
{
	if (nullptr != m_pPickTarget && DLL::pInputMgr->MouseDown(DIM_LB))
	{
		m_pPickTarget = nullptr;
	}

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);
}

void CMouseManager::Render_GameObject(void)
{
	if (nullptr != m_pTargetTexture)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matTargetWorld);
		m_pTargetTexture->Render_Texture();
		m_pTargetBuffer->Render_Buffer();
	}

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_matMouseWorld);

	m_pMouseTexture->Render_Texture(m_eCurMouseState);
	m_pMouseBuffer->Render_Buffer();

}

void CMouseManager::Set_MouseMode(MOUSE_STATE eMode)
{
	m_eCurMouseState = eMode;
}

void CMouseManager::Set_PickTarget(Engine::CGameObject * pPick)
{
	DLL::pSoundMgr->PlaySound(L"SelectTarget.wav", CSoundMgr::EFFECT);
	DLL::pSoundMgr->SetVolume(CSoundMgr::EFFECT, 0.5f);

	m_pPickTarget = pPick;
}

void CMouseManager::Set_Activate(void)
{
	m_bActivated = !m_bActivated;
}

void CMouseManager::Set_ItemName(const Engine::_tchar * pName)
{
	if (m_bClicked)
	{
		return;
	}

	DLL::pSoundMgr->PlaySound(L"ItemPickUp.wav", CSoundMgr::EFFECT);
	DLL::pSoundMgr->SetVolume(CSoundMgr::EFFECT, 0.3f);

	if (false == m_wStrClickItemName.empty())
	{
		Safe_Release(m_pTargetTexture);
		m_wStrClickItemName.clear();
	}

	m_wStrClickItemName = pName;
	m_pTargetTexture = DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, m_wStrClickItemName.c_str());
}

const Engine::_vec3 * CMouseManager::Get_ViewportMouse(void) const
{
	return &m_vMouseInViewport;
}

const Engine::_vec3 * CMouseManager::Get_ViewspaceMouse(void) const
{
	return &m_vMouseInViewSpace;
}

Engine::CGameObject * CMouseManager::Get_PickTarget(void)
{
	return m_pPickTarget;
}

const Engine::_tchar * CMouseManager::Get_ItemName(void)
{
	return m_wStrClickItemName.c_str();
}

void CMouseManager::Clear_PickTarget(void)
{
	m_pPickTarget = nullptr;
}

void CMouseManager::Clear_Name(void)
{
	m_wStrName.clear();
}

void CMouseManager::get_MousePos(void)
{
	POINT			ptMouse{};
	_vec2			vPos;
	// 윈도우 영역 == 뷰포트 영역
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	vPos.x = static_cast<_float>(ptMouse.x);
	vPos.y = static_cast<_float>(ptMouse.y);

	D3DVIEWPORT9 tViewPort;
	m_pGraphicDev->GetViewport(&tViewPort);

	static const _float fToHalf = 0.5f;
	static const _float fHalfViewPort = 1.f;
	
	m_vMouseInViewport.x = ptMouse.x - (tViewPort.Width * fToHalf);
	m_vMouseInViewport.y = -ptMouse.y + (tViewPort.Height * fToHalf);
	m_vMouseInViewport.z = 0.f;

	m_vMouseInViewSpace.x = ptMouse.x / (tViewPort.Width * fToHalf) - fHalfViewPort;
	m_vMouseInViewSpace.y = -ptMouse.y / (tViewPort.Height * fToHalf) + fHalfViewPort;
	m_vMouseInViewSpace.z = 0.f;

	_matrix matProj;
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMatrixInverse(&matProj, nullptr, &matProj);
	D3DXVec3TransformCoord(&m_vMouseInViewSpace, &m_vMouseInViewSpace, &matProj);
}

inline void CMouseManager::Free()
{
	CGameObject::Free();
}