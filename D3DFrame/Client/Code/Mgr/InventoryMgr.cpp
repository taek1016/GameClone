#include "stdafx.h"
#include "InventoryMgr.h"

#include "Item/BagBase.h"

#include "Item/OneFourBag.h"

USING(Engine)
IMPLEMENT_SINGLETON(CInventoryMgr)

CInventoryMgr::CInventoryMgr(void)
	: m_fSlotScaleWidth(0.f)
	, m_fSlotScaleHeight(0.f)
	, m_vStartPos(0.f, 0.f, 0.f)

	, m_iMoney(7000)
{
}

CInventoryMgr::~CInventoryMgr(void)
{
	Free();
}

void CInventoryMgr::Initialize_Inventory(LPDIRECT3DDEVICE9& pGraphicDev)
{
	const _int iMaxBags = 4;
	m_vecBags.resize(iMaxBags);

	D3DVIEWPORT9 tViewPort;
	pGraphicDev->GetViewport(&tViewPort);

	const _float fHalf = 0.5f;
	m_vStartPos.x = tViewPort.Width * fHalf * 0.8f;
	m_vStartPos.y = -(tViewPort.Height * fHalf * 0.1f);

	_vec3 vScale(200.f, 100.f, 1.f);

	m_vecBags[0] = (make_pair(COneFourBag::Create(DLL::pGraphicDev->GetDevice(), &m_vStartPos, &vScale), false));
}

void CInventoryMgr::Update_Inventory(const Engine::_float & fTimeDelta)
{
	if (nullptr == this)
	{
		return;
	}

	for (auto iter : m_vecBags)
	{
		if (nullptr == iter.first)
		{
			continue;
		}
		else if (true == iter.second)
		{
			iter.first->Update_GameObject(fTimeDelta);
		}
	}
}

void CInventoryMgr::Add_Money(const Engine::_int & iMoney)
{
	m_iMoney += iMoney;
}

CBagBase * CInventoryMgr::Get_Bag(const Engine::_int & iIndex)
{
	if (0 < iIndex || iIndex >= 4)
	{
		return nullptr;
	}

	CBagBase* pBag = m_vecBags[iIndex].first;

	m_vecBags[iIndex].first = nullptr;
	m_vecBags[iIndex].second = false;

	return pBag;
}

CBagBase* CInventoryMgr::Add_Bag(CBagBase * pBag, const Engine::_int & iIndex)
{
	CBagBase* pBagInIndex = nullptr;
	if (nullptr != m_vecBags[iIndex].first)
	{
		pBagInIndex = Get_Bag(iIndex);
	}

	m_vecBags[iIndex].first = pBag;

	return pBagInIndex;
}

Engine::_int CInventoryMgr::Get_Money(void) const
{
	return m_iMoney;
}

_bool CInventoryMgr::Can_BuyItem(const Engine::_int& iMoney)
{
	if (m_iMoney >= iMoney)
	{
		m_iMoney -= iMoney;
		return true;
	}

	DLL::pSoundMgr->PlaySound(L"NotEnoughMoney.wav", CSoundMgr::EFFECT);
	DLL::pSoundMgr->SetVolume(CSoundMgr::EFFECT, 0.3f);
	return false;
}

void CInventoryMgr::Convert_Money(Engine::_int iMoney)
{
	const _int iGoldConverter = 10000;
	m_iGold = iMoney / iGoldConverter;
	iMoney %= iGoldConverter;

	const _int iSilverConverter = 100;
	m_iSilver = iMoney / iSilverConverter;
	iMoney %= iSilverConverter;

	m_iCooper = iMoney;
}

void CInventoryMgr::Activate_Bag(const Engine::_int& iIndex)
{
	if (4 <= iIndex)
	{
		return;
	}

	m_vecBags[iIndex].second = !m_vecBags[iIndex].second;
}

inline void CInventoryMgr::Free(void)
{
	for (auto iter : m_vecBags)
	{
		Safe_Release(iter.first);
	}
	m_vecBags.clear();
}
