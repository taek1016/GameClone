#include "stdafx.h"
#include "SlotBase.h"

USING(Engine)

CSlotBase::CSlotBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pTargetSkill(nullptr)
	, m_pTexture(nullptr)
	, m_pBuffer(nullptr)
	, m_pLine(nullptr)

	, m_bClicked(false)
	, m_bCollided(false)
	, m_fClickTime(0.f)
{
}

CSlotBase::~CSlotBase(void)
{
}

HRESULT CSlotBase::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_STATIC);

	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);

	return S_OK;
}

HRESULT CSlotBase::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_STATIC);

	m_pBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);

	m_pLine = DLL::pGraphicDev->GetLine();
	m_pLine->AddRef();

	return S_OK;
}

Engine::_int CSlotBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	_vec2 vMousePos;
	memcpy(&vMousePos, DLL::pMouseMgr->Get_ViewportMouse(), sizeof(_vec2));

	if (m_bClicked)
	{
		m_fClickTime += fTimeDelta;
		if (m_fClickTime >= 0.15f)
		{
			m_bClicked = false;
		}
	}

	if (!m_bClicked && CollideFunc::MouseToRect(&m_tRect, &vMousePos))
	{
		m_bCollided = true;
		if (false == m_bClicked && DLL::pInputMgr->MouseDown(DIM_LB))
		{
			Click_Action();
		}
	}
	else
	{
		m_fClickTime = 0.f;
		m_bClicked = false;
		m_bCollided = false;
	}

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return iExit;
}

void CSlotBase::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	if (m_pTexture)
	{
		m_pTexture->Render_Texture();
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

const Engine::_bool CSlotBase::Get_Clicked(void) const
{
	return m_bClicked;
}

void CSlotBase::set_Data(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	m_pTransform->Set_Info(INFO_POS, pPos);
	m_pTransform->Set_Scale(pScale);

	m_pTransform->Update_Component(0.f);

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

Engine::CGameObject * CSlotBase::Clone(void)
{
	return nullptr;
}

inline void CSlotBase::Free(void)
{
	CGameObject::Free();
	Safe_Release(m_pTargetSkill);
	Safe_Release(m_pLine);
}
