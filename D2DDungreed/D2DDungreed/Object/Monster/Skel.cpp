#include "stdafx.h"
#include "Skel.h"

#include "../Item/Weapon.h"

CSkel::CSkel()
	: CMeleeMonster()
{
}


CSkel::~CSkel()
{
	SafeDelete(m_pWeapon);
}

CSkel* CSkel::Create(const D3DXVECTOR3& vecPos, const D3DXVECTOR3& vecSize, CWeapon* pWeapon)
{
	CSkel* pInstance = new CSkel;

	pInstance->SetObjectKey(L"Skel");

	for (int i = 0; i < static_cast<int>(OBJECT_STATUS::STATUS_END); ++i)
	{
		pInstance->SetAnimation(static_cast<OBJECT_STATUS>(i), 0);
	}

	pInstance->SetAnimation(DIE, 1);
	pInstance->SetAnimation(IDLE, 1);
	pInstance->SetAnimation(MOVE, 6);

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->m_tInfo.SetSize(vecSize);

	pInstance->SetDefaultXWay(vecSize.x);

	pInstance->SetWeapon(pWeapon);

	pInstance->SetAttackCool(3.f);
	
	pInstance->SetSpeed(50.f);

	pInstance->SetObjType(OBJECT_TYPE::OBJECT_MONSTER);

	return pInstance;
}

void CSkel::Act()
{
	if (m_pWeapon)
	{
		m_pWeapon->Update();
	}

	CMoveObject::SetPreStatus();
	CMoveObject::SetCurStatus(OBJECT_STATUS::IDLE);

	if (!m_pPlayer)
	{
		return;
	}

	D3DXVECTOR3 vecDistance = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front()->GetPos() - m_tInfo.vPos;
	float fDistance = D3DXVec3Length(&vecDistance);

	if (fDistance <= m_fCheckDistance)
	{
		D3DXVec3Normalize(&m_tInfo.vDir, &vecDistance);

		m_tInfo.vDir *= m_fSpeed;

		// 공격범위 안 쪽이면 공격
		if (m_pAttackRect->GetCanAct() && m_fAttackCool.GetNextCool())
		{
			Attack();
		}

		// 움직임
		else
		{
			CMoveObject::Move(m_tInfo.vDir.x);
		}
	}

	CMoveObject::FreeDownObject();
}

void CSkel::Attack()
{
}

void CSkel::Render()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey,
		m_wStrObjectStatus,
		static_cast<WORD>(m_tFrame.fCurFrame)
	);
	assert(nullptr != pTexInfo);
	NULL_CHECK(pTexInfo);

	D3DXVECTOR3	vecCenter{ pTexInfo->tImgInfo.Width TO_HALF, pTexInfo->tImgInfo.Height * 0.75f, 0.f };
	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CSINGLETON::pDirectMgr->GetSprite()->Draw
	(
		pTexInfo->pTexture,
		nullptr,
		&vecCenter,
		nullptr,
		m_tInfo.iColorValue
	);
	UpdateRect();

#ifdef _DEBUG
	CSINGLETON::pDirectMgr->RenderRect(
		m_tMainRect,
		D3DCOLOR_ARGB(255, 255, 125, 255));

	const D3DXVECTOR3& cameraPos = CSINGLETON::pCameraMgr->GetPos();

	D3DXVECTOR2 temp[2] = {
		D3DXVECTOR2(m_tInfo.vPos.x - cameraPos.x, m_tInfo.vPos.y - cameraPos.y),
		D3DXVECTOR2(m_tInfo.vPos.x + 10.f - cameraPos.x, m_tInfo.vPos.y - cameraPos.y)
	};
	CSINGLETON::pDirectMgr->GetLine()->Draw(
		temp,
		2,
		D3DCOLOR_ARGB(255, 255, 0, 0)
	);
#endif // _DEBUG
	if (m_pAttackRect)
	{
		m_pAttackRect->Render();
	}

	if (m_pWeapon)
	{
		m_pWeapon->Render();
	}
}