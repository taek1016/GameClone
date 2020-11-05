#include "stdafx.h"
#include "MiddleFairy.h"


CMiddleFairy::CMiddleFairy()
{
	SetObjectKey(L"Fairy");
	SetObjectStatus(L"Middle");

	m_tFrame.SetInitial();
	m_tFrame.SetMaxFrame(16.f);

	m_tInfo.SetSize(D3DXVECTOR3(30.f / 20.f, 30.f / 20.f, 0.f));

	SetWidth(20);
	SetHeight(20);

	SetHealPoint(30);
}


CMiddleFairy::~CMiddleFairy()
{
}

CMiddleFairy * CMiddleFairy::Create(const D3DXVECTOR3 & vecPos)
{
	CMiddleFairy* pInstance = new CMiddleFairy;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}
