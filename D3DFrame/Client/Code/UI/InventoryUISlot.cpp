#include "stdafx.h"
#include "InventoryUISlot.h"

#include "Item/BagBase.h"

USING(Engine)

CInventorySlot::CInventorySlot(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSlotBase(pGraphicDev)

	, m_pBagTexture(nullptr)
	, m_pBagBuffer(nullptr)
{
	set_Name(L"BagSlot");
}

CInventorySlot::CInventorySlot(const CInventorySlot & rhs)
	: CSlotBase(rhs)

	, m_pBagTexture(nullptr)
	, m_pBagBuffer(nullptr)
{
	set_Name(L"BagSlot");
}

HRESULT CInventorySlot::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_STATIC);
	DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, Get_Name())->Attach(L"Texture", this, ID_STATIC);
	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);
	CRcTex::Create(m_pGraphicDev)->Attach(L"BagBuffer", this, ID_STATIC);

	return S_OK;
}

HRESULT CInventorySlot::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_STATIC);
	m_pTexture = Get_Component<CTexture>(L"Texture", ID_STATIC);
	m_pBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);
	m_pBagBuffer = Get_Component<CRcTex>(L"BagBuffer", ID_STATIC);

	m_pLine = DLL::pGraphicDev->GetLine();
	m_pLine->AddRef();

	return S_OK;
}

Engine::_int CInventorySlot::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	_vec2 vMousePos;
	memcpy(&vMousePos, DLL::pMouseMgr->Get_ViewportMouse(), sizeof(_vec2));

	if (m_bClicked)
	{
		m_fClicked += fTimeDelta;

		_float fClickLimit = 0.2f;
		if (m_fClicked >= fClickLimit)
		{
			m_bClicked = false;
			m_fClicked = 0.f;
		}
	}

	if (false == m_bClicked && CollideFunc::MouseToRect(&m_tRect, &vMousePos))
	{
		m_bCollided = true;
		if (DLL::pInputMgr->MouseDown(DIM_LB))
		{
			Click_Action();
		}
		else if (DLL::pInputMgr->MouseDown(DIM_RB))
		{
			DLL::pInventory->Activate_Bag(m_iCurIdx);
		}
	}
	else
	{
		m_bClicked = false;
		m_bCollided = false;
	}

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return iExit;
}

void CInventorySlot::Render_GameObject(void)
{
	CSlotBase::Render_GameObject();

	if (m_pBagTexture)
	{
		m_pBagTexture->Render_Texture();
		m_pBagBuffer->Render_Buffer();
	}
}

void CInventorySlot::Click_Action(void)
{
	if (m_bClicked)
	{
		return;
	}

	wstring wStrName = DLL::pMouseMgr->Get_ItemName();
	if (wStrName.empty())
	{
		// 인벤토리 매니저에서 해당 슬롯 교체

		if (m_pBagTexture)
		{
			Safe_Release(m_pBagTexture);
		}
		DLL::pMouseMgr->Set_ItemName(m_wTextureName.c_str());
		DLL::pMouseMgr->Set_PickTarget(DLL::pInventory->Get_Bag(m_iCurIdx));

		m_pBagTexture = DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, m_wStrName.c_str());
	}
	else
	{
		DLL::pMouseMgr->Set_ItemName(m_wTextureName.c_str());
		m_wTextureName = wStrName;
		Set_BagName(wStrName.c_str());
		// 인벤토리에서 가방 활성화
		DLL::pInventory->Add_Bag(dynamic_cast<CBagBase*>(DLL::pMouseMgr->Get_PickTarget()), m_iCurIdx);
		DLL::pMouseMgr->Clear_PickTarget();
		DLL::pInventory->Activate_Bag(m_iCurIdx);
	}
}

void CInventorySlot::Set_BagName(const Engine::_tchar * pName)
{
	m_wTextureName = pName;

	if (m_pBagTexture)
	{
		Safe_Release(m_pBagTexture);
	}

	m_pBagTexture = DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, m_wTextureName.c_str());

}

void CInventorySlot::set_CurIdx(const Engine::_int & iIdx)
{
	m_iCurIdx = iIdx;
}

CInventorySlot * CInventorySlot::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_int& iIdx)
{
	CInventorySlot* pInstance = new CInventorySlot(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	pInstance->set_Data(pPos, pScale);
	pInstance->set_CurIdx(iIdx);

	return pInstance;
}
