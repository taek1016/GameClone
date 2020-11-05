#include "stdafx.h"
#include "LargeFairy.h"


CLargeFairy::CLargeFairy()
{
	SetObjectKey(L"Fairy");
	SetObjectStatus(L"Large");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(16.f);

	m_tInfo.SetSize(D3DXVECTOR3(40.f / 24.f, 40.f / 25.f, 0.f));

	SetWidth(30);
	SetHeight(30);

	SetHealPoint(50);
}


CLargeFairy::~CLargeFairy()
{
}

CLargeFairy * CLargeFairy::Create(const D3DXVECTOR3 & vecPos)
{
	CLargeFairy* pInstance = new CLargeFairy;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}
