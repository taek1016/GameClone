#include "stdafx.h"
#include "MaterialSlot.h"

USING(Engine)

CMaterialSlot::CMaterialSlot(void)
	: CGameObject()
{
}

CMaterialSlot::CMaterialSlot(const CMaterialSlot & rhs)
	: CGameObject(rhs)
{
}

CMaterialSlot::~CMaterialSlot(void)
{
}

HRESULT CMaterialSlot::Late_Initialize()
{
	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Slot"));
	m_pTexture->Attach(this, ID_STATIC);

	switch (m_eType)
	{
	case MATERIAL_WOOD:
		m_wStrRenderKey = L"WoodIcon";
		break;
	case MATERIAL_STONE:
		m_wStrRenderKey = L"IronIcon";
		break;
	}
	m_pNumTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Numbers"));
	return S_OK;
}

HRESULT CMaterialSlot::Initialize_GameObject()
{
	CComponent*	pComponent = nullptr;

	m_pTransform = CTransform::Create();
	m_pTransform->Attach(this, ID_DYNAMIC);
	m_pTransform->Set_Scale(60.f, 60.f, 1.f);

	return S_OK;
}

Engine::_int CMaterialSlot::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return Engine::_int();
}

void CMaterialSlot::Render_GameObject(void)
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	m_pTexture->Render_Texture();
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");

	DLL::pResourceMgr->Render_Texture(RESOURCE_STAGE, m_wStrRenderKey.c_str());
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");

	pGraphicDev->SetTransform(D3DTS_WORLD, &m_matNumWorld);
	m_pNumTexture->Render_Texture(m_iCurMaterialNum);
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

void CMaterialSlot::Add_MaterialNum(void)
{
	m_iCurMaterialNum++;
}

Engine::_bool CMaterialSlot::Delete_MaterialNum(const _int& iCnt)
{
	m_iCurMaterialNum -= iCnt;
	return true;
}

void CMaterialSlot::Set_NumData()
{
	_matrix matScale, matTrans;
	D3DXMatrixScaling(&matScale, 10.f, 10.f, 1.f);
	_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
	_float fDistance = 20.f;
	D3DXMatrixTranslation(&matTrans, vPos.x + fDistance, vPos.y - fDistance, vPos.z);
	m_matNumWorld = matScale * matTrans;
}

void CMaterialSlot::Set_Type(const MATERIAL_TYPE& iType)
{
	m_eType = iType;
}

void CMaterialSlot::Set_Pos(const Engine::_vec3 * pPos)
{
	m_pTransform->Set_Pos(pPos);
}

CMaterialSlot * CMaterialSlot::Create(const Engine::_vec3 * pPos, const MATERIAL_TYPE& eType)
{
	CMaterialSlot*	pInstance = new CMaterialSlot;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	pInstance->Set_Pos(pPos);
	pInstance->Set_Type(eType);
	pInstance->Set_NumData();

	return pInstance;
}

Engine::CGameObject * CMaterialSlot::Clone(const Engine::_vec3 * pPos)
{
	return nullptr;
}

inline void CMaterialSlot::freeMem()
{
	CGameObject::freeMem();
	Safe_Release(m_pNumTexture);
}
