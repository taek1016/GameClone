#include "stdafx.h"
#include "Weapon.h"

CWeapon::CWeapon()
	: CBaseItem()
	, m_fAngle(0.f)

	, m_fWidth(0)
	, m_fHeight(0)
{
}

CWeapon::~CWeapon()
{
	m_fAngle = 0.f;
	m_fWidth = 0;
	m_fHeight = 0;
}

void CWeapon::Render()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey,
		m_wStrObjectStatus,
		0
	);
	NULL_CHECK(pTexInfo);

	CSINGLETON::pDirectMgr->RenderImage
	(
		pTexInfo,
		m_tInfo.matWorld,
		m_tInfo.iColorValue
	);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect);
#endif // _DEBUG
}