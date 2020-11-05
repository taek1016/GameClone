#include "stdafx.h"
#include "BagBase.h"

#include "UI/ItemSlot.h"

USING(Engine)

CBagBase::CBagBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItemBase(pGraphicDev)
	, m_iHeightNum(0)
	, m_iWidthNum(0)

	, m_pBuffer(nullptr)
	, m_pTexture(nullptr)
{
}

CBagBase::CBagBase(const CBagBase & rhs)
	: CItemBase(rhs)
	, m_iHeightNum(rhs.m_iHeightNum)
	, m_iWidthNum(rhs.m_iWidthNum)

	, m_pBuffer(nullptr)
	, m_pTexture(nullptr)
{
}

HRESULT CBagBase::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_STATIC);

	DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, m_wStrName.c_str())->Attach(L"Texture", this, ID_STATIC);

	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);

	return S_OK;
}

HRESULT CBagBase::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_STATIC);

	m_pTexture = Get_Component<CTexture>(L"Texture", ID_STATIC);

	m_pBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);

	return S_OK;
}

Engine::_int CBagBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	CGameObject::Update_GameObject(fTimeDelta);
	
	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	for (auto iter : m_vecItemSlot)
	{
		iter->Update_GameObject(fTimeDelta);
	}

	return 0;
}

void CBagBase::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	if (m_pTexture)
	{
		m_pTexture->Render_Texture();
		m_pBuffer->Render_Buffer();
	}
}

Engine::_bool CBagBase::Add_Items(Engine::_tchar* pItems)
{
	_int iIndex = -1;
	for (_int i = 0; i < m_iHeightNum; ++i)
	{
		for (_int j = 0; j < m_iWidthNum; ++j)
		{
			iIndex = i * m_iHeightNum + j;
			// 비어있으면
			if (m_vecItemSlot[iIndex]->Is_Empty())
			{
				m_vecItemSlot[iIndex]->Set_Item(pItems);
				return true;
			}
		}
	}
	return false;
}

const Engine::_tchar* CBagBase::Get_PickItem(const Engine::_int & iIdx)
{
	wstring strTemp = m_vecItemSlot[iIdx]->Get_Item();
	m_vecItemSlot[iIdx]->Clear_Item();
	return strTemp.c_str();
}

void CBagBase::set_ItemSlots(const Engine::_int & iHeightNum, const Engine::_int & iWidthNum)
{
	m_iWidthNum = iWidthNum;
	m_iHeightNum = iHeightNum;

	m_vecItemSlot.resize(m_iWidthNum * m_iHeightNum);
}

void CBagBase::make_ItemSlot(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_float& fTotalWidth, const Engine::_float& fTotalHeight)
{
	m_pTransform->Set_Info(INFO_POS, pPos);
	m_pTransform->Set_Scale(pScale);
	m_pTransform->Update_Component(0.f);

	// 모든 인벤 슬롯이 위에서부터 47픽셀, 너비는 16픽셀부터 시작.
	const _float fPixelStartPosY = 47.f;
	const _float fPixelStartPosX = 16.f;

	const _float fStartXRatio = fPixelStartPosX / fTotalWidth;
	const _float fStartYRatio = fPixelStartPosY / fTotalHeight;

	// 한 칸은 35, 35픽셀
	const _float fPixelItemSlotWidth = 35.f;
	const _float fPixelItemSlotHeight = 35.f;

	const _float fHalf = 0.5f;

	_vec3 vPos, vScale;

	vPos.x = pPos->x - pScale->x * fHalf;
	vPos.y = pPos->y + pScale->y * fHalf;
	vPos.z = 0.f;

	vPos.x += (16.f + fPixelItemSlotWidth * fHalf) / fTotalWidth * pScale->x;
	vPos.y -= (50.f + fPixelItemSlotHeight * fHalf) / fTotalHeight * pScale->y;

	vScale.x = pScale->x * (fPixelItemSlotWidth / fTotalWidth);
	vScale.y = pScale->y * (fPixelItemSlotHeight / fTotalHeight);
	vScale.z = 1.f;

	const _float fXFirstPos = vPos.x;
	_int iIndex = -1;
	for (_int i = 0; i < m_iHeightNum; ++i)
	{
		for (_int j = 0; j < m_iWidthNum; ++j)
		{
			iIndex = i * m_iHeightNum + j;

			m_vecItemSlot[iIndex] = CItemSlot::Create(m_pGraphicDev, &vPos, &vScale);

			if (j != 0 && j % m_iWidthNum == 0)
			{
				vPos.x = fXFirstPos;
				vPos.y -= (6.f + fPixelItemSlotHeight) / fTotalHeight * pScale->y;
			}
			else
			{
				vPos.x += (7.f + fPixelItemSlotWidth) / fTotalWidth * pScale->x;
			}
		}
	}
}

Engine::CGameObject * CBagBase::Clone(void)
{
	return nullptr;
}

inline void CBagBase::Free(void)
{
	CGameObject::Free();

	for (auto iter : m_vecItemSlot)
	{

	}
}
