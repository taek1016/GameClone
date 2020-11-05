#include "stdafx.h"
#include "SmallFairy.h"


CSmallFairy::CSmallFairy()
{
	SetObjectKey(L"Fairy");
	SetObjectStatus(L"Small");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(16.f);

	m_tInfo.SetSize(D3DXVECTOR3(20.f / 9.f, 20.f / 11.f, 0.f));

	SetWidth(10);
	SetHeight(10);

	SetHealPoint(10);
}


CSmallFairy::~CSmallFairy()
{
}

CSmallFairy* CSmallFairy::Create(const D3DXVECTOR3 & vecPos)
{
	CSmallFairy* pInstance = new CSmallFairy;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}
