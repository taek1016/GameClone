#include "stdafx.h"
#include "MyLayer.h"

CMyLayer::CMyLayer()
	: m_fSpeed(0.f)
{
	AssertMember();
}


CMyLayer::~CMyLayer()
{
	AssertMember();
}

CMyLayer * CMyLayer::Create(
	const	std::wstring&	wStrObjectKey,
	const	std::wstring&	wStrObjectStatus,
	const	D3DXVECTOR3&	vecPos,
	const	D3DXVECTOR3&	vecSize)
{
	CMyLayer*	pInstance = new CMyLayer;

	pInstance->SetObjectKey(wStrObjectKey);
	pInstance->SetObjectStatus(wStrObjectStatus);
	pInstance->SetMatrix(vecPos, vecSize);

	return pInstance;
}

void CMyLayer::UpdateRect()
{
}

void CMyLayer::AssertMember()
{
	m_fSpeed = 0.f;
	assert(0.f == m_fSpeed);
}

int CMyLayer::Update()
{
	return 0;
}

void CMyLayer::LateUpdate()
{
	m_tInfo.vPos.x += m_fSpeed * CSINGLETON::pTimeMgr->GetDelta();

	m_tInfo.matWorld._41 = m_tInfo.vPos.x;
	m_tInfo.matWorld._42 = m_tInfo.vPos.y;

	m_tInfo.matWorld._11 = m_tInfo.vSize.x;
	m_tInfo.matWorld._22 = m_tInfo.vSize.y;
}

void CMyLayer::SetMatrix(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecSize)
{
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	m_tInfo.SetPos(vecPos);
	m_tInfo.SetSize(vecSize);

	UpdateRect();
}
