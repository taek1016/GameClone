#include "stdafx.h"
#include "LargeLayer.h"

CLargeLayer::CLargeLayer()
	: m_fSpeed(0.f)
{
}

CLargeLayer::~CLargeLayer()
{
}

CLargeLayer* CLargeLayer::Create
(
	const std::wstring&	wstrObjectKey, 
	const std::wstring&	wstrObjectStatus,
	const D3DXVECTOR3&	vecPos, 
	const D3DXVECTOR3&	vecSize
)
{
	CLargeLayer* pInstance = new CLargeLayer;

	pInstance->SetMatrix(vecPos, vecSize);

	pInstance->SetObjectKey(wstrObjectKey);
	pInstance->SetObjectStatus(wstrObjectStatus);

	::SetRect(&pInstance->m_tMainRect, 0, 0, 400, 142);

	return pInstance;
}

void CLargeLayer::UpdateRect()
{
}

int CLargeLayer::Update()
{
	return 0;
}

void CLargeLayer::LateUpdate()
{
	m_tMainRect.left = static_cast<int>(CSINGLETON::pCameraMgr->GetPos().x / 320.f);
	m_tMainRect.right = m_tMainRect.left + 400;

	m_tInfo.vPos.x += m_fSpeed * CSINGLETON::pTimeMgr->GetDelta();

	m_tInfo.matWorld._41 = m_tInfo.vPos.x;
}

void CLargeLayer::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus);
	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CSINGLETON::pDirectMgr->GetSprite()->Draw
	(
		pTexInfo->pTexture,
		nullptr,
		nullptr,
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CLargeLayer::SetMatrix(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 & vecSize)
{
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	m_tInfo.SetPos(vecPos);
	m_tInfo.SetSize(vecSize);

	m_tInfo.matWorld._11 = m_tInfo.vSize.x;
	m_tInfo.matWorld._22 = m_tInfo.vSize.y;

	m_tInfo.matWorld._42 = m_tInfo.vPos.y;
}
