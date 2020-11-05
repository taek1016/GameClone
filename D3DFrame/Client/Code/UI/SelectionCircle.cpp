#include "stdafx.h"
#include "SelectionCircle.h"

USING(Engine)

CSelectionCircle::CSelectionCircle(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
{
	set_Name(L"SelectionCircle");
}

CSelectionCircle::CSelectionCircle(const CSelectionCircle & rhs)
	: CUIBase(rhs)
{
}

HRESULT CSelectionCircle::Initialize_UI(const Engine::_tchar * pName)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, pName)->Attach(L"Texture", this, ID_STATIC);

	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Sample")->Attach(L"Shader", this, ID_STATIC);

	return S_OK;
}

HRESULT CSelectionCircle::Late_InitializeUI(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pTransform->Rotation(ROT_X, D3DXToRadian(90.f));
	m_pTransform->Set_Scale(&_vec3(1.5f, 1.f, 1.5f));

	m_pTexture = Get_Component<CTexture>(L"Texture", ID_STATIC);

	m_pBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);
	m_pShader = Get_Component<CShader>(L"Shader", ID_STATIC);
	return S_OK;
}

Engine::_int CSelectionCircle::Update_GameObject(const Engine::_float & fTimeDelta)
{
	m_pTarget = DLL::pMouseMgr->Get_PickTarget();

	if (nullptr != m_pTarget)
	{
		_vec3 vScale;
		auto pTargetName = m_pTarget->Get_Name();
		if (0 == wcscmp(pTargetName, L"Boar"))
		{
			vScale = { 10.f, 10.f, 1.f };
		}
		else if (0 == wcscmp(pTargetName, L"Infernal"))
		{
			vScale = { 100.f, 100.f, 1.f };

		}
		else if (0 == wcscmp(pTargetName, L"Nefarian"))
		{
			vScale = { 100.f, 100.f, 1.f };
		}
		else if (0 == wcscmp(pTargetName, L"Doomguard"))
		{
			vScale = { 100.f, 100.f, 1.f };
		}

		m_pTransform->Set_Scale(&vScale);
		const _float fRotationOneSec = 180.f * fTimeDelta;

		_vec3 vPos = *m_pTarget->Get_Pos();
		vPos.y += 2.f;
		m_pTransform->Set_Info(INFO_POS, &vPos);
		m_pTransform->Rotation(ROT_Y, D3DXToRadian(fRotationOneSec));

		CGameObject::Update_GameObject(fTimeDelta);

		// 플레이어 위치에 적당히 가리기 위함.
		DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);
	}

	return 0;
}

CSelectionCircle * CSelectionCircle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSelectionCircle* pInstance = new CSelectionCircle(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->Get_Name())))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_InitializeUI(nullptr, nullptr)))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

Engine::CGameObject * CSelectionCircle::Clone(void)
{
	return nullptr;
}
