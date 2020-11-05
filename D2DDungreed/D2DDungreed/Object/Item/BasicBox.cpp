#include "stdafx.h"
#include "BasicBox.h"

CBasicBox::CBasicBox()
{
	SetObjectKey(L"Box");
	SetObjectStatus(L"BasicTresure");

	m_tInfo.SetSize(D3DXVECTOR3(50.f / 27.f, 30.f / 16.f, 0.f));
}

CBasicBox::~CBasicBox()
{
}

CBasicBox* CBasicBox::Create(const D3DXVECTOR3& vecPos, CBaseItem* pItem)
{
	CBasicBox* pInstance = new CBasicBox;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->SetItem(pItem);

	pInstance->UpdateRect();

	return pInstance;
}