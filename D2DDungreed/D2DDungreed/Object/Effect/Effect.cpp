#include "stdafx.h"
#include "Effect.h"

CEffect::CEffect()
	: CGameObject()
	, m_fTime(0.f)
	, m_fAngle(0.f)
	, m_fHalfX(0.f)
	, m_fHalfY(0.f)
{
	m_tFrame.SetInitial();
}

CEffect::~CEffect()
{
}

CEffect* CEffect::Create
(
	const D3DXVECTOR3 & vecPos, 
	const D3DXVECTOR3 & vecSize, 
	const EFFECT_TYPE & eType, 
	const float			fAngle,
	const float			fTime
)
{
	CEffect* pInstance = new CEffect;

	pInstance->m_tInfo.SetPos(vecPos);

	pInstance->m_fHalfX = vecSize.x TO_HALF;
	pInstance->m_fHalfY = vecSize.y TO_HALF;

	pInstance->m_fTime = fTime;
	switch (eType)
	{
	case EFFECT_MOVE:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"Move");
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 16.f, vecSize.y / 16.f, 0.f));
		pInstance->m_tFrame.SetMaxFrame(6.f);
		break;

	case EFFECT_JUMP:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"Jump");
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 9.f, vecSize.y / 10.f, 0.f));
		pInstance->m_tFrame.SetMaxFrame(5.f);
		break;

	case EFFECT_DIE:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"Die");
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 64.f, vecSize.y / 64.f, 0.f));
		pInstance->m_tFrame.SetMaxFrame(11.f);
		break;

	case EFFECT_BULLET:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"Bullet");
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 5.f, vecSize.y / 13.f, 0.f));
		pInstance->m_tFrame.SetMaxFrame(6.f);
		break;

	case EFFECT_ICE_BULLET_CREATE:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"IceBulletCreate");
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 25.f, vecSize.y / 25.f, 0.f));
		pInstance->m_tFrame.SetMaxFrame(3.f);
		break;
	case EFFECT_ICE_PILLAR_DESTROY:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"IcePillarDestroy");
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 62.f, vecSize.y / 33.f, 0.f));
		pInstance->m_tFrame.SetMaxFrame(3.f);
		break;

	case EFFECT_ICICLE_DESTROY:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"IcicleDestroy");
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 35.f, vecSize.y / 48.f, 0.f));
		pInstance->m_tFrame.SetMaxFrame(3.f);
		break;

	case EFFECT_STUN:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"Stun");
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 13.f, vecSize.y / 9.f, 0.f));
		pInstance->m_tFrame.SetMaxFrame(6.f);
		break;

	case EFFECT_HIT:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"Hit");
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 38.f, vecSize.y / 50.f, 0.f));
		pInstance->m_tFrame.SetMaxFrame(6.f);
		break;

	case EFFECT_HECATE_SHOT:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"HecateShot");
		pInstance->m_tFrame.SetMaxFrame(3.f);
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 37.f, vecSize.y / 30.f, 0.f));
		break;

	case EFFECT_HECATE_SMOKE:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"HecateSmoke");
		pInstance->m_tFrame.SetMaxFrame(9.f);
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 36.f, vecSize.y / 56.f, 0.f));
		break;

	case EFFECT_BANSHEE_BULLET_DESTORY:
		pInstance->SetObjectKey(L"FX");
		pInstance->SetObjectStatus(L"BansheeBulletDestroy");
		pInstance->m_tFrame.SetMaxFrame(6.f);
		pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / 20.f, vecSize.y / 27.f, 0.f));
		break;
	}
	pInstance->m_fAngle = fAngle;

	return pInstance;
}

int CEffect::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta() * m_fTime;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		return DEAD_OBJ;
	}

	return NO_EVENT;
}

void CEffect::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fAngle);
	UpdateRect();
}

void CEffect::Render()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey, 
		m_wStrObjectStatus, 
		static_cast<WORD>(m_tFrame.fCurFrame)
	);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 0, 255, 0));
#endif // _DEBUG
}

void CEffect::UpdateRect()
{
	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - m_fHalfX);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + m_fHalfX);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.y - m_fHalfY);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.y + m_fHalfY);
}