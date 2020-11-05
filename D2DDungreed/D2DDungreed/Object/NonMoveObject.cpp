#include "stdafx.h"
#include "NonMoveObject.h"

CNonMoveObject::CNonMoveObject()
	: CGameObject()
	, m_tFrame{}
{
	AssertMember();
}


CNonMoveObject::~CNonMoveObject()
{
	AssertMember();
}

void CNonMoveObject::Render()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(
		m_wStrObjectKey,
		m_wStrObjectStatus,
		static_cast<WORD>(m_tFrame.fCurFrame)
	);

	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CSINGLETON::pDirectMgr->GetSprite()->Draw(
		pTexInfo->pTexture,
		nullptr,
		nullptr,
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CNonMoveObject::AssertMember()
{
	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 0.f;

	m_wStrObjectKey.clear();
	m_wStrObjectStatus.clear();

	assert(0.f == m_tFrame.fCurFrame);
	assert(0.f == m_tFrame.fMaxFrame);
}
