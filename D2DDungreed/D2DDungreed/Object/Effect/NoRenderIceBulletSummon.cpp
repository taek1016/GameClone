#include "stdafx.h"
#include "NoRenderIceBulletSummon.h"

#include "../Bullet/IceBullet.h"

CNoRenderIceBulletSummon::CNoRenderIceBulletSummon()
	: m_fCurTime(0.f)
	, m_iCurMakeBullet(0)
{
}


CNoRenderIceBulletSummon::~CNoRenderIceBulletSummon()
{
}

CNoRenderIceBulletSummon * CNoRenderIceBulletSummon::Create(const D3DXVECTOR3 & vecPos)
{
	CNoRenderIceBulletSummon* pInstance = new CNoRenderIceBulletSummon;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

int CNoRenderIceBulletSummon::Update()
{
	m_fCurTime += CSINGLETON::pTimeMgr->GetDelta();
	
	if (m_fCurTime >= 0.2)
	{
		m_iCurMakeBullet++;
		m_fCurTime = 0.f;
		D3DXVECTOR3 pPlayerPos = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front()->GetPos() - m_tInfo.vPos;
		
		D3DXVec3Normalize(&pPlayerPos, &pPlayerPos);
		D3DXVECTOR3 vLook(1.f, 0.f, 0.f);
		float fAngle = acosf(D3DXVec3Dot(&vLook, &pPlayerPos));

		if (pPlayerPos.y < 0)
		{
			fAngle *= -1;
		}

		vLook = { 0.f, -1.f, 0.f };
		float fRotation = acosf(D3DXVec3Dot(&vLook, &pPlayerPos));

		CSINGLETON::pSoundMgr->PlaySound(L"IceBall.wav", CSoundMgr::CHANNEL_ID::EFFECT);
		CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_BULLET, CIceBullet::Create(m_tInfo.vPos, fAngle, fRotation));
	}

	if (m_iCurMakeBullet >= 8)
	{
		return DEAD_OBJ;
	}
	return 0;
}

void CNoRenderIceBulletSummon::LateUpdate()
{

}

void CNoRenderIceBulletSummon::Render()
{
#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 0, 255, 0));
#endif // _DEBUG
}

void CNoRenderIceBulletSummon::UpdateRect()
{
	float fHalf = 20.f;

	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - fHalf);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + fHalf);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.y - fHalf);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.y + fHalf);
}
