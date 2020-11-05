#include "stdafx.h"
#include "BlockObject.h"

#include "../Block/SealClose.h"

CBlockObject::CBlockObject()
	: m_fAngle(0.f)
	, m_bDelete(false)
{
	SetObjectKey(L"SealStone");
	SetObjectStatus(L"Idle");

	m_tFrame.SetMaxFrame(8.f);
}

void CBlockObject::CollideWithObj(const OBJECT_LIST& pTo)
{
	RECT rc{};

	for (auto iter : pTo)
	{
		if (IntersectRect(&rc, &iter->GetRect(), &m_tMainRect))
		{
			const D3DXVECTOR3& vPos = iter->GetPos();
			float fDiff = static_cast<float>(rc.right) - rc.left;
			// 오른쪽에서 올 경우 오른쪽으로 밀어냄
			if (m_tInfo.vPos.x <= vPos.x)
			{
				iter->SetPosition(D3DXVECTOR3(vPos.x + fDiff, vPos.y, vPos.z));
			}
			else
			{
				iter->SetPosition(D3DXVECTOR3(vPos.x - fDiff, vPos.y, vPos.z));
			}
		}
	}
}

CBlockObject::~CBlockObject()
{
}

CBlockObject* CBlockObject::Create(const D3DXVECTOR3& vecPos, const D3DXVECTOR3& vecSize, float fAngle)
{
	CBlockObject* pInstance = new CBlockObject;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->SetAngle(fAngle);
	pInstance->m_tInfo.SetSize(vecSize);

	return pInstance;
}

int CBlockObject::Update()
{
	if (CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_MONSTER)->empty())
	{
		CSINGLETON::pObjectMgr->AddObject
		(
			OBJECT_OBJECT, 
			CSealClose::Create
			(
				m_tInfo.vPos, 
				m_tInfo.vSize, 
				m_fAngle
			)
		);
		return DEAD_OBJ;
	}

	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta() * 2;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		m_tFrame.fCurFrame = 0.f;
	}

	return NO_EVENT;
}

void CBlockObject::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, m_fAngle);
	UpdateRect();

	CollideWithObj(*CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER));
	CollideWithObj(*CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_MONSTER));
}

void CBlockObject::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, static_cast<WORD>(m_tFrame.fCurFrame));

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(m_tMainRect, D3DCOLOR_ARGB(255, 0, 255, 0));
#endif // _DEBUG

}

void CBlockObject::UpdateRect()
{
	float fHalfX = 20.f;
	float fHalfY = 100.f;

	m_tMainRect.left	= static_cast<LONG>(m_tInfo.vPos.x - fHalfX);
	m_tMainRect.right	= static_cast<LONG>(m_tInfo.vPos.x + fHalfX);
	m_tMainRect.top		= static_cast<LONG>(m_tInfo.vPos.y - fHalfY);
	m_tMainRect.bottom	= static_cast<LONG>(m_tInfo.vPos.y + fHalfY);
}