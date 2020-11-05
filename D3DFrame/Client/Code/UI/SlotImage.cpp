#include "stdafx.h"
#include "SlotImage.h"

USING(Engine)

CSlotImage::CSlotImage(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
{
}

CSlotImage::CSlotImage(const CSlotImage & rhs)
	: CUIBase(rhs)
{
}

HRESULT CSlotImage::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Sample")->Attach(L"Shader", this, ID_STATIC);
	return S_OK;
}

HRESULT CSlotImage::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);
	m_pShader = Get_Component<CShader>(L"Shader", ID_STATIC);
	return S_OK;
}

Engine::_int CSlotImage::Update_GameObject(const Engine::_float & fTimeDelta)
{
	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return CGameObject::Update_GameObject(fTimeDelta);
}

void CSlotImage::set_Vector(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	m_pTransform->Set_Info(INFO_POS, pPos);
	m_pTransform->Set_Scale(pScale);
}

void CSlotImage::Set_Texture(const Engine::_tchar * pName)
{
	auto iter = find_if(m_listComponent[ID_STATIC].begin(), m_listComponent[ID_STATIC].end(), CTag_Finder(L"Texture"));

	m_pTexture = DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, pName);

	if (m_listComponent[ID_STATIC].end() != iter)
	{
		Safe_Release(iter->second);

		if (nullptr != m_pTexture)
		{
			iter->second = m_pTexture;
		}
	}
	else
	{
		m_pTexture->Attach(L"Texture", this, ID_STATIC);
	}
}

CSlotImage * CSlotImage::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CSlotImage* pInstance = new CSlotImage(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->set_Vector(pPos, pScale);

	return pInstance;
}
