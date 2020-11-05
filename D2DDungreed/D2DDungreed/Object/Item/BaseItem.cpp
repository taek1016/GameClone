#include "stdafx.h"
#include "BaseItem.h"

CBaseItem::CBaseItem()
	: CGameObject()
{
}

CBaseItem::~CBaseItem()
{
}

void CBaseItem::Render()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey,
		m_wStrObjectStatus
	);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect);
#endif // _DEBUG
}