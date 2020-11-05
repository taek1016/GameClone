#include "stdafx.h"
#include "Button.h"

USING(Engine)

CButton::CButton(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pLine (nullptr)

	, m_bClicked(false)
	, m_bCollided(false)

	, m_iIndex(0)

	, m_fDebugDelta(0.f)
{
}

CButton::CButton(const CButton & rhs)
	: CGameObject(rhs)

	, m_bClicked(false)
	, m_bCollided(false)

	, m_iIndex(0)
{
}

CButton::~CButton(void)
{
}

HRESULT CButton::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	if (!m_wStrName.empty())
	{
		DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, m_wStrName.c_str())->Attach(L"Texture", this, ID_STATIC);
	}
	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);

	m_pLine = DLL::pGraphicDev->GetLine();
	m_pLine->AddRef();

	return S_OK;
}

HRESULT CButton::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);

	m_pTexture = Get_Component<CTexture>(L"Texture", ID_STATIC);

	m_pBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);

	return S_OK;
}

Engine::_int CButton::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	const _vec3* pMouseVec3 = DLL::pMouseMgr->Get_ViewportMouse();
	_vec2 vMousePos(pMouseVec3->x, pMouseVec3->y);

	if (!m_bClicked && CollideFunc::MouseToRect(&m_tRect, &vMousePos))
	{
		m_bCollided = true;
		if (DLL::pInputMgr->MouseDown(DIM_LB))
		{
			m_iIndex = 1;
		}
		else if (DLL::pInputMgr->MouseUp(DIM_LB))
		{
			m_bClicked = true;
		}
	}
	else
	{
		m_iIndex = 0;
		m_bClicked = false;
		m_bCollided = false;
	}

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	if (nullptr != m_tInfo.pTextData)
	{
		DLL::pFontMgr->Print_Font(&m_tInfo.vPos, &m_tInfo.vScale, m_tInfo.iLinePerText, m_tInfo.pTextData, m_tInfo.tColor);
	}

	return 0;
}

void CButton::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	if (m_pTexture)
	{
		m_pTexture->Render_Texture(m_iIndex);
		m_pBuffer->Render_Buffer();
	}

	if (g_bCollider)
	{
		_int iIdx = 0;

		if (m_bCollided)
		{
			iIdx = 1;
		}
		m_pLine->Draw(m_vColLine, 5, m_tColor[iIdx]);
	}
}

void CButton::Print_Content(const _tchar* pContent)
{
	_int iSize = lstrlen(pContent);

	_vec3 vPos(*m_pTransform->Get_Info(INFO_POS));
	_vec3 vScale(30.f, 20.f, 1.f);
	vPos.x -= vScale.x * iSize * 0.5f;

	m_tInfo = FONT_INFO(&vPos, &vScale, 30, pContent/*, D3DXCOLOR(1.f, 1.f, 1.f, 1.f)*/);
}

//void CButton::Print_Content(const Engine::_tchar * pText, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const D3DXCOLOR & tColor)
//{
//	_int iStrLen = lstrlen(pText);
//	_vec3 vPos(*pPos);
//	vPos.x -= pScale->x * iStrLen * 0.5f;
//
//	m_tInfo.vPos = vPos;
//	m_tInfo.vScale = *pScale;
//	m_tInfo.iLinePerText = 30;
//	m_tInfo.pTextData = pText;
//	m_tInfo.tColor = tColor;
//}

const Engine::_bool CButton::Get_Clicked(void) const
{
	return m_bClicked;
}

void CButton::Cancel_Clicked(void)
{
	m_bClicked = false;
}

void CButton::set_MinMax(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	// left top right bottom
	const _float fHalf = 0.5f;
	m_tRect = { pPos->x - pScale->x * fHalf,
				pPos->y + pScale->y * fHalf,
				pPos->x + pScale->x * fHalf,
				pPos->y - pScale->y * fHalf };
	
	D3DVIEWPORT9 tViewport;
	m_pGraphicDev->GetViewport(&tViewport);

	const _float fWidth = tViewport.Width * fHalf;
	const _float fHeight = tViewport.Height * fHalf;
	// ÁÂÇÏ´Ü
	m_vColLine[0] = { m_tRect.fLeft + fWidth, -m_tRect.fBottom + fHeight };
	// ÁÂ»ó´Ü
	m_vColLine[1] = { m_tRect.fLeft + fWidth, -m_tRect.fTop + fHeight };
	// ¿ì»ó´Ü
	m_vColLine[2] = { m_tRect.fRight + fWidth, -m_tRect.fTop + fHeight };
	// ¿ìÇÏ´Ü
	m_vColLine[3] = { m_tRect.fRight + fWidth, -m_tRect.fBottom + fHeight };
	// ÁÂÇÏ´Ü
	m_vColLine[4] = { m_tRect.fLeft + fWidth, -m_tRect.fBottom + fHeight };

	m_tColor[0] = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	m_tColor[1] = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
}

CButton * CButton::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar * pName, const Engine::_vec3 * vPos, const Engine::_vec3 * vScale)
{
	CButton* pInstance = new CButton(pGraphicDev);

	pInstance->set_Name(pName);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();

	pInstance->Set_Pos(vPos);
	pInstance->Set_Scale(vScale);

	pInstance->set_MinMax(vPos, vScale);

	return pInstance;
}

Engine::CGameObject * CButton::Clone(void)
{
	return nullptr;
}

inline void CButton::Free(void)
{
	CGameObject::Free();
	Safe_Release(m_pLine);
}
