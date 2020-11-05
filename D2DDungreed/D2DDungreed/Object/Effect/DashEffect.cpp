#include "stdafx.h"
#include "DashEffect.h"


CDashEffect::CDashEffect()
	: CGameObject()
	, m_iColor(250)
{
}


CDashEffect::~CDashEffect()
{
}

CDashEffect* CDashEffect::Create
(
	const D3DXVECTOR3&	vecPos, 
	const D3DXVECTOR3&	vecSize, 
	const std::wstring& wStrKey, 
	const std::wstring& wStrStatus, 
	const WORD&			wIndex
)
{
	CDashEffect* pInstance = new CDashEffect;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->m_tInfo.SetSize(vecSize);

	pInstance->SetObjectKey(wStrKey);
	pInstance->SetObjectStatus(wStrStatus);

	pInstance->m_tFrame.SetCurFrame(static_cast<FLOAT>(wIndex));

	return pInstance;
}

int CDashEffect::Update()
{
	if (m_iColor <= 0)
	{
		return DEAD_OBJ;
	}

	m_iColor -= 10;
	m_tInfo.SetColor(D3DCOLOR_ARGB(m_iColor, m_iColor, m_iColor, m_iColor));

	return NO_EVENT;
}

void CDashEffect::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
}

void CDashEffect::Render()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CDashEffect::UpdateRect()
{
}