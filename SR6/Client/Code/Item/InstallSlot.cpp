#include "stdafx.h"
#include "InstallSlot.h"

USING(Engine)

CInstallSlot::CInstallSlot(void)
	: CGameObject()
{
}

CInstallSlot::CInstallSlot(const CInstallSlot & rhs)
	: CGameObject(rhs)
{
}

CInstallSlot::~CInstallSlot(void)
{
}

HRESULT CInstallSlot::Late_Initialize()
{
	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Slot"));
	m_pTexture->Attach(this, ID_STATIC);

	switch (m_eType)
	{
	case INSTALL_WALL:
		m_wStrRenderKey = L"Wall";
		break;
	case INSTALL_MACHINE_GUN:
		m_wStrRenderKey = L"MachineGun";
		break;
	}
	m_pNumTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Numbers"));
	_matrix matScale, matTrans;
	D3DXMatrixScaling(&matScale, 10.f, 10.f, 1.f);
	_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
	_float fDistance = 20.f;
	D3DXMatrixTranslation(&matTrans, vPos.x + fDistance, vPos.y - fDistance, vPos.z);
	m_matNumWorld = matScale * matTrans;

	return S_OK;
}

HRESULT CInstallSlot::Initialize_GameObject()
{
	CComponent*	pComponent = nullptr;

	m_pTransform = CTransform::Create();
	m_pTransform->Attach(this, ID_DYNAMIC);
	m_pTransform->Set_Scale(60.f, 60.f, 1.f);

	return S_OK;
}

Engine::_int CInstallSlot::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return Engine::_int();
}

void CInstallSlot::Render_GameObject(void)
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	m_pTexture->Render_Texture();
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");

	DLL::pResourceMgr->Render_Texture(RESOURCE_STAGE, m_wStrRenderKey.c_str());
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");

	pGraphicDev->SetTransform(D3DTS_WORLD, &m_matNumWorld);
	m_pNumTexture->Render_Texture(m_iCurItem);
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

void CInstallSlot::Add_Install(CGameObject * pObj)
{
	m_installList.push_back(pObj);
	m_iCurItem++;
}

CGameObject * CInstallSlot::Get_Install(void)
{
	CGameObject* pItem = m_installList.front();
	m_installList.pop_front();
	m_iCurItem--;
	return pItem;
}

void CInstallSlot::Set_Type(const INSTALL_TYPE & eType)
{
	m_eType = eType;
}

void CInstallSlot::Set_Pos(const Engine::_vec3 * pPos)
{
	m_pTransform->Set_Pos(pPos);
}

CInstallSlot * CInstallSlot::Create(const Engine::_vec3 * pPos, const INSTALL_TYPE & eType)
{
	CInstallSlot*	pInstance = new CInstallSlot;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	pInstance->Set_Pos(pPos);
	pInstance->Set_Type(eType);

	return pInstance;
}

Engine::CGameObject * CInstallSlot::Clone(const Engine::_vec3 * pPos)
{
	return nullptr;
}
