#include "stdafx.h"
#include "IceSpear.h"

#include "../Player.h"
#include "../Effect/MissileWarningEffect.h"

CIceSpear::CIceSpear()
	: m_bDead(false)
	, m_bTargeting(false)
	, m_fCurTime(0.f)
	, m_fAngle(D3DXToRadian(90.f))
{
	SetObjectKey(L"Bullet");
	SetObjectStatus(L"IceSpear");

	m_tInfo.SetDir(D3DXVECTOR3(1.f, 0.f, 0.f));

	m_tInfo.SetSize(D3DXVECTOR3(50.f / 25.f, 150.f / 111.f, 0.f));
}


CIceSpear::~CIceSpear()
{
}

CIceSpear * CIceSpear::Create(const D3DXVECTOR3 & vecPos)
{
	CIceSpear* pInstance = new CIceSpear;

	pInstance->m_tInfo.SetPos(vecPos);

	return pInstance;
}

int CIceSpear::Update()
{
	m_fCurTime += CSINGLETON::pTimeMgr->GetDelta();

	if (m_bTargeting && m_fCurTime >= ICE_SPEAR_CREATE_TIME)
	{
		m_bDead = true;
	}

	if (!m_bTargeting && m_fCurTime >= SET_TARGET_TIME)
	{
		m_fCurTime = 0.f;
		m_tInfo.SetDir(LEFT_LOOK_VECTOR);
		m_bTargeting = true;
		m_fAngle = D3DXToRadian(-90.f);

		CGameObject* pPlayer = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front();

		D3DXVECTOR3 pos(pPlayer->GetPos());
		pos.x += START_POS_X;

		m_tInfo.SetPos(pos);

		pos.x -= WARNING_MESSAGE_START_POS_X;
		CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_EFFECT, CMissileWarningEffect::Create(D3DXVECTOR3(pos), D3DXToRadian(90.f)));
	}

	if (m_bDead)
	{
		return DEAD_OBJ;
	}

	return 0;
}

void CIceSpear::LateUpdate()
{
	float fMoveSpeed = SPAER_SPEED * CSINGLETON::pTimeMgr->GetDelta();
	if (!m_bTargeting)
	{
		m_tInfo.vDir = RIGHT_LOOK_VECTOR * fMoveSpeed;
	}
	else
	{
		m_tInfo.vDir = LEFT_LOOK_VECTOR * fMoveSpeed;
	}

	m_tInfo.vPos += m_tInfo.vDir;

	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fAngle);
	UpdateRect();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front());

	RECT rc{};
	if (IntersectRect(&rc, &pPlayer->GetRect(), &m_tMainRect))
	{
		pPlayer->GetDamage(SPEAR_DAMAGE);
		m_bDead = true;
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_TYPE::OBJECT_EFFECT, 
			CEffect::Create
			(
				m_tInfo.vPos, 
				ICE_SPEAR_SIZE,
				EFFECT_TYPE::EFFECT_ICE_SPEAR_DESTROY,
				NO_ROTATION
			)
		);
	}
}

void CIceSpear::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 255, 0, 0));
#endif // _DEBUG

}

void CIceSpear::UpdateRect()
{
	float fHalfX = 75.f;
	float fHalfY = 25.f;

	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - fHalfX);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + fHalfX);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.y - fHalfY);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.y + fHalfY);
}
