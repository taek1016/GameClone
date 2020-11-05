#include "stdafx.h"
#include "InventoryRender.h"

CInventoryRender::CInventoryRender()
	: m_wStrKey()
	, m_wStrStatus()
	
	, m_vecPos{}
	, m_vecSize{}
	
	, m_matWorld{}

	, m_wIndex(0)
{
}

CInventoryRender::~CInventoryRender()
{
}

CInventoryRender * CInventoryRender::Create
(
	const D3DXVECTOR3	vecPos,
	const D3DXVECTOR3	vecSize,
	const WORD&			wIndex,
	const std::wstring&	wStrKey,
	const std::wstring&	wStrStatus
)
{
	CInventoryRender* pInstance = new CInventoryRender;

	pInstance->m_vecPos = vecPos;
	pInstance->m_vecSize = vecSize;
	pInstance->m_wIndex = wIndex;

	pInstance->SetKey(wStrKey);
	pInstance->SetStatus(wStrStatus);

	CSINGLETON::pMathMgr->CalculateMove
	(
		pInstance->m_matWorld, 
		pInstance->m_vecPos, 
		pInstance->m_vecSize, 
		0.f, 
		false
	);

	return pInstance;
}

void CInventoryRender::Update()
{

}

void CInventoryRender::Render()
{
	const TEX_INFO* pTexInfo = nullptr;
	for (WORD i = 0; i < m_wIndex; ++i)
	{
		pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
		(
			m_wStrKey,
			m_wStrStatus,
			i
		);

		CSINGLETON::pDirectMgr->RenderImage
		(
			pTexInfo,
			m_matWorld,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
}