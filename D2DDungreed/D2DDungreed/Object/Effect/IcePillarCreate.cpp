#include "stdafx.h"
#include "IcePillarCreate.h"

#include "../Monster/Boss.h"
#include "../Monster/IcePillar.h"

CIcePillarCreate::CIcePillarCreate()
	: m_fAngle(0.f)
	, m_fRevolve(0.f)
	, m_pTarget(nullptr)
{
	SetObjectKey(L"FX");
	SetObjectStatus(L"IcePillarCreate");

	m_tFrame.SetMaxFrame(20.f);

	m_tInfo.SetSize(D3DXVECTOR3(120.f / 62.f, 50.f / 33.f, 0.f));
	m_tInfo.SetLook(D3DXVECTOR3(0.f, -1.f, 0.f));
}


CIcePillarCreate::~CIcePillarCreate()
{
}

CIcePillarCreate * CIcePillarCreate::Create(int iIndex, float fSelfRotAngle, float fRevolveAngle, CBoss* pObj)
{
	CIcePillarCreate* pInstance = new CIcePillarCreate;

	pInstance->SetIndex(iIndex);
	pInstance->SetSelfRot(fSelfRotAngle);
	pInstance->SetRevolve(fRevolveAngle);
	pInstance->SetTarget(pObj);

	return pInstance;
}

int CIcePillarCreate::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta() * 0.5f;

	if (m_tFrame.fCurFrame >= m_tFrame.fMaxFrame)
	{
		CSINGLETON::pObjectMgr->AddObject(OBJECT_MONSTER, CIcePillar::Create(m_iIndex, m_fAngle, m_fRevolve, m_pTarget));
		m_pTarget = nullptr;
		return DEAD_OBJ;
	}

	return NO_EVENT;
}

void CIcePillarCreate::LateUpdate()
{
	m_fAngle += D3DXToRadian(5.f);
	m_tInfo.SetPos(m_pTarget->GetPos());
	m_tInfo.SetDir(D3DXVECTOR3(cosf(m_fAngle), sinf(m_fAngle), 0.f));

	m_fRevolve += D3DXToRadian(5.f);
	if (m_fRevolve >= D3DXToRadian(180.f))
	{
		m_fRevolve *= -1.f;
	}

	m_tInfo.vDir *= 80.f;
	m_tInfo.vPos += m_tInfo.vDir;
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fRevolve);
}

void CIcePillarCreate::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CIcePillarCreate::UpdateRect()
{
}
