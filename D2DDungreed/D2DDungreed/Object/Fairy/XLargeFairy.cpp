#include "stdafx.h"
#include "XLargeFairy.h"


CXLargeFairy::CXLargeFairy()
{
	SetObjectKey(L"Fairy");
	SetObjectStatus(L"Large");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(16.f);

	m_tInfo.SetSize(D3DXVECTOR3(50.f / 30.f, 50.f / 30.f, 0.f));

	SetWidth(50);
	SetHeight(50);

	SetHealPoint(9999);
}


CXLargeFairy::~CXLargeFairy()
{
}

CXLargeFairy * CXLargeFairy::Create(const D3DXVECTOR3 & vecPos)
{
	CXLargeFairy* pInstance = new CXLargeFairy;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}
