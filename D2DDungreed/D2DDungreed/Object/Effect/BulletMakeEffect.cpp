#include "stdafx.h"
#include "BulletMakeEffect.h"

#include "../Bullet/IceBullet.h"

CBulletMakeEffect::CBulletMakeEffect()
{
}

void CBulletMakeEffect::SummonBullet(const D3DXVECTOR3 & vecPos, const float fWayAngle, const float fRotationAngle)
{
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_BULLET,
		CIceBullet::Create
		(
			vecPos,
			fWayAngle,
			fRotationAngle
		)
	);
}


CBulletMakeEffect::~CBulletMakeEffect()
{
}

CBulletMakeEffect * CBulletMakeEffect::Create
(
	const D3DXVECTOR3 & vecPos,
	const D3DXVECTOR3 & vecSize,
	const std::wstring & wstrKey,
	const std::wstring & wstrStatus,
	const WORD & wMaxIndex)
{
	CBulletMakeEffect* pInstance = new CBulletMakeEffect;

	pInstance->SetObjectKey(wstrKey);
	pInstance->SetObjectStatus(wstrStatus);

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x, vecSize.y, vecSize.z));

	pInstance->m_tFrame.SetInitial();
	pInstance->m_tFrame.SetMaxFrame(static_cast<float>(wMaxIndex));

	return pInstance;
}

int CBulletMakeEffect::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta() * 0.75f;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		float fWayAngle = D3DXToRadian(-90.f);
		float fRotationAngle = D3DXToRadian(0.f);

		for (int i = 0; i < 6; ++i)
		{
			float angleIndex = D3DXToRadian(60.f) * i;
			SummonBullet(m_tInfo.vPos, fWayAngle + angleIndex, fRotationAngle + angleIndex);
		}
		return DEAD_OBJ;
	}

	return NO_EVENT;
}

void CBulletMakeEffect::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
	UpdateRect();
}

void CBulletMakeEffect::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CBulletMakeEffect::UpdateRect()
{
	float fX = 25.f;
	float fY = 25.f;

	m_tMainRect.left = static_cast<LONG>(m_tInfo.vPos.x - fX);
	m_tMainRect.right = static_cast<LONG>(m_tInfo.vPos.x + fX);
	m_tMainRect.top = static_cast<LONG>(m_tInfo.vPos.y - fY);
	m_tMainRect.bottom = static_cast<LONG>(m_tInfo.vPos.y + fY);
}
