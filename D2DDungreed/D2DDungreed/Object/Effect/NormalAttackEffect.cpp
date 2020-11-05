#include "stdafx.h"
#include "NormalAttackEffect.h"

#include "../Monster/Monster.h"

CNormalAttackEffect::CNormalAttackEffect()
	: CGameObject()
{
}


CNormalAttackEffect::~CNormalAttackEffect()
{
}

CNormalAttackEffect* CNormalAttackEffect::Create
(
	const ATTACK_FROM	eFrom,
	const float			fDamage,
	const float			fAngle,
	const D3DXVECTOR3&	vecPos,
	const D3DXVECTOR3&	vecSize,
	const std::wstring& wStrKey,
	const std::wstring& wStrStatus,
	const WORD&			wIndex
)
{
	CNormalAttackEffect* pInstance = new CNormalAttackEffect;

	pInstance->SetFrom(eFrom);

	pInstance->SetObjectKey(wStrKey);
	pInstance->SetObjectStatus(wStrStatus);

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->m_tInfo.SetSize(vecSize);
	pInstance->m_tInfo.SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));

	pInstance->m_tFrame.SetMaxFrame(static_cast<float>(wIndex));

	pInstance->SetDamage(fDamage);
	pInstance->SetAngle(fAngle);

	pInstance->UpdateRect();

	CSINGLETON::pMathMgr->CalculateMove(pInstance->m_tInfo.matWorld, pInstance->m_tInfo.vPos, pInstance->m_tInfo.vSize, pInstance->m_fAngle);

	return pInstance;
}

int CNormalAttackEffect::Update()
{
	float fAnimationDelta = m_tFrame.fMaxFrame 
		* CSINGLETON::pTimeMgr->GetDelta()
		* MAKE_ZERO_POINT_THREE_SEC;

	m_tFrame.fCurFrame += fAnimationDelta;

	if (static_cast<int>(m_tFrame.fCurFrame) == 0)
	{
		CSINGLETON::pPhysicMgr->CollideWithObject
		(
			&m_tMainRect, 
			m_fDamage, 
			*CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_MONSTER)
		);
	}
	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		return DEAD_OBJ;
	}
	return NO_EVENT;
}

void CNormalAttackEffect::LateUpdate()
{
	UpdateRect();
}

void CNormalAttackEffect::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 255, 0, 0));
#endif // _DEBUG
}

void CNormalAttackEffect::UpdateRect()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	float fHalfX = m_tInfo.vSize.x * pTexInfo->tImgInfo.Width TO_HALF;
	float fHalfY = m_tInfo.vSize.y * pTexInfo->tImgInfo.Height TO_HALF;

	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - fHalfX);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + fHalfX);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - fHalfY);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + fHalfY);
}
