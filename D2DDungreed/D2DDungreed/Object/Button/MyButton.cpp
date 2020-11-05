#include "stdafx.h"
#include "MyButton.h"

CMyButton::CMyButton()
	: CNonMoveObject()
	, m_bClicked(false)
{
	Assertmember();
}

CMyButton::~CMyButton()
{
	Assertmember();
}

CMyButton* CMyButton::Create(
	const	std::wstring&	wStrObjectKey,
	const	std::wstring&	wStrObjectStatus,
	const	D3DXVECTOR3&	vecPos, 
	const	D3DXVECTOR3&	vecSize)
{
	CMyButton*	pInstance = new CMyButton;

	pInstance->SetObjectKey(wStrObjectKey);
	pInstance->SetObjectStatus(wStrObjectStatus);
	pInstance->SetMatrix(vecPos, vecSize);
	pInstance->UpdateRect();

	return pInstance;
}

int CMyButton::Update()
{
	m_tFrame.fCurFrame = 0.f;
	if (CSINGLETON::pPhysicMgr->IntersectMouseToRect(m_tMainRect, CSINGLETON::pMouseMgr->GetMousePos()))
	{
		m_tFrame.fCurFrame = 1.f;
		if (CSINGLETON::pKeyMgr->KeyPressing(KEY_LBUTTON))
		{
			m_bClicked = true;
		}
	}
	return 0;
}

void CMyButton::LateUpdate()
{
}

void CMyButton::SetMatrix(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecSize)
{
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	m_tInfo.matWorld._41 = vecPos.x;
	m_tInfo.matWorld._42 = vecPos.y;

	m_tInfo.matWorld._11 = vecSize.x;
	m_tInfo.matWorld._22 = vecSize.y;
}

void CMyButton::UpdateRect()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus);

	m_tMainRect.left	= static_cast<LONG>(m_tInfo.matWorld._41);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.matWorld._42);
	m_tMainRect.right	= static_cast<LONG>(m_tMainRect.left + m_tInfo.matWorld._11 * pTexInfo->tImgInfo.Width);
	m_tMainRect.bottom	= static_cast<LONG>(m_tMainRect.top + m_tInfo.matWorld._22 * pTexInfo->tImgInfo.Height);
}

void CMyButton::Assertmember()
{
	m_bClicked = false;
	assert(false == m_bClicked);
}
