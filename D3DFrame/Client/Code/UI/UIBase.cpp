#include "stdafx.h"
#include "UIBase.h"

USING(Engine)
CUIBase::CUIBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pTexture(nullptr)
	, m_pBuffer(nullptr)
	, m_pTransform(nullptr)
	, m_pTarget(nullptr)
	, m_iIndex(0)
	, m_iPass(0)
	, m_pShader(nullptr)
{
}

CUIBase::~CUIBase(void)
{
}

HRESULT CUIBase::Initialize_UI(const Engine::_tchar * pName)
{
	CTransform::Create()->Attach(L"Transform", this, ID_STATIC);

	wstring strName = pName;
	if (!strName.empty())
	{
		DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, pName)->Attach(L"Texture", this, ID_STATIC);
	}

	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Sample")->Attach(L"Shader", this, ID_STATIC);

	return S_OK;
}

HRESULT CUIBase::Late_InitializeUI(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_STATIC);
	m_pTransform->Set_Info(INFO_POS, pPos);
	m_pTransform->Set_Scale(pScale);
	m_pTransform->Update_Component(0.f);

	m_pTexture = Get_Component<CTexture>(L"Texture", ID_STATIC);

	m_pBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);
	m_pShader = Get_Component<CShader>(L"Shader", ID_STATIC);

	return S_OK;
}

HRESULT CUIBase::Set_Target(Engine::CGameObject * pObj)
{
	m_pTarget = pObj;
	
	return S_OK;
}

void CUIBase::Render_GameObject(void)
{
	//m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	//if (m_pTexture)
	//{
	//	m_pTexture->Render_Texture(m_iIndex);
	//	m_pBuffer->Render_Buffer();
	//}
	if (nullptr != m_pTexture)
	{
		LPD3DXEFFECT	pEffect = m_pShader->Get_EffectHandle();
		NULL_CHECK(pEffect);
		pEffect->AddRef();

		_uint	iPassMax = 0;


		FAILED_CHECK_RETURN(setUp_ConstantTable(pEffect), );

		pEffect->Begin(&iPassMax, 0);	// 1인자 : 현재 쉐이더 파일 갖고 있는 최대 패스의 개수

		pEffect->BeginPass(m_iPass);

		m_pBuffer->Render_Buffer();

		pEffect->EndPass();

		pEffect->End();

		Engine::Safe_Release(pEffect);
	}
}

void CUIBase::Change_UI(const Engine::_tchar* pKey)
{
	m_pTransform->Update_Component(0.f);
}

HRESULT CUIBase::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	_matrix			matWorld, matView, matProj;

	matWorld = *m_pTransform->Get_World();
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	m_pTexture->Set_Texture(pEffect, "g_BaseTexture", (_uint)0);

	return S_OK;
}

void CUIBase::set_Data(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
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
	// 좌하단
	m_vColLine[0] = { m_tRect.fLeft + fWidth, -m_tRect.fBottom + fHeight };
	// 좌상단
	m_vColLine[1] = { m_tRect.fLeft + fWidth, -m_tRect.fTop + fHeight };
	// 우상단
	m_vColLine[2] = { m_tRect.fRight + fWidth, -m_tRect.fTop + fHeight };
	// 우하단
	m_vColLine[3] = { m_tRect.fRight + fWidth, -m_tRect.fBottom + fHeight };
	// 좌하단
	m_vColLine[4] = { m_tRect.fLeft + fWidth, -m_tRect.fBottom + fHeight };

	m_tColor[0] = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	m_tColor[1] = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
}

inline void CUIBase::Free(void)
{
	CGameObject::Free();
	m_pTarget = nullptr;

	m_pTexture = nullptr;
	m_pTransform = nullptr;
	m_pBuffer = nullptr;
}