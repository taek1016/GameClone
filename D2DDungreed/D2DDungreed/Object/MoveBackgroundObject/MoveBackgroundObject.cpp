#include "stdafx.h"
#include "MoveBackgroundObject.h"


CMoveBackgroundObject::CMoveBackgroundObject()
{
}


CMoveBackgroundObject::~CMoveBackgroundObject()
{
}

CMoveBackgroundObject* CMoveBackgroundObject::Create(
	const std::wstring&		wstrObjectKey,
	const std::wstring&		wstrObjectStatus,
	const WORD&				wIndex,
	const D3DXVECTOR3&		vecPos, 
	const D3DXVECTOR3&		vecSize,
	const float				fSpeed)
{
	CMoveBackgroundObject*	pInstance = new CMoveBackgroundObject;

	pInstance->SetObjectKey(wstrObjectKey);
	pInstance->SetObjectStatus(wstrObjectStatus);
	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->m_tInfo.SetSize(vecSize);

	pInstance->SetAnimation(OBJECT_STATUS::IDLE, 0);
	pInstance->SetAnimation(OBJECT_STATUS::ATTACK, 0);
	pInstance->SetAnimation(OBJECT_STATUS::DIE, 0);
	pInstance->SetAnimation(OBJECT_STATUS::JUMP, 0);
	pInstance->SetAnimation(OBJECT_STATUS::MOVE, wIndex);
	pInstance->SetAnimation(OBJECT_STATUS::SKILL, 0);
	
	pInstance->SetSpeed(fSpeed);

	pInstance->m_eCurStatus = OBJECT_STATUS::MOVE;
	pInstance->SetFrame();

	return pInstance;
}

CMoveBackgroundObject * CMoveBackgroundObject::Create(const std::wstring & wstrObjectKey, const std::wstring & wstrObjectStatus, const WORD & wIndex, const float fSpeed)
{
	CMoveBackgroundObject*	pInstance = new CMoveBackgroundObject;

	pInstance->SetObjectKey(wstrObjectKey);
	pInstance->SetObjectStatus(wstrObjectStatus);

	pInstance->SetAnimation(OBJECT_STATUS::IDLE, 0);
	pInstance->SetAnimation(OBJECT_STATUS::ATTACK, 0);
	pInstance->SetAnimation(OBJECT_STATUS::DIE, 0);
	pInstance->SetAnimation(OBJECT_STATUS::JUMP, 0);
	pInstance->SetAnimation(OBJECT_STATUS::MOVE, wIndex);
	pInstance->SetAnimation(OBJECT_STATUS::SKILL, 0);

	pInstance->SetSpeed(fSpeed);

	pInstance->m_eCurStatus = OBJECT_STATUS::MOVE;
	pInstance->SetFrame();

	return pInstance;
}

int CMoveBackgroundObject::Update()
{
	int iEvent = NO_EVENT;
	CMoveObject::Animate();

	return iEvent;
}

void CMoveBackgroundObject::LateUpdate()
{
	m_tInfo.vPos.x += m_fSpeed * CSINGLETON::pTimeMgr->GetDelta();
	CSINGLETON::pMathMgr->CalculateMove(
		m_tInfo.matWorld,
		m_tInfo.vPos,
		m_tInfo.vSize,
		m_fAngle);
}