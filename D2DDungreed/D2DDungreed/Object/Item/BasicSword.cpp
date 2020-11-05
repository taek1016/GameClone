#include "stdafx.h"
#include "BasicSword.h"

#include "../Effect/NormalAttackEffect.h"

CBasicSword::CBasicSword()
	: CSword()
{
	SetObjectKey(L"BasicShortSword");
	SetObjectStatus(L"Weapon");
	SetDamage(5.f);
}


CBasicSword::~CBasicSword()
{
}

CBasicSword* CBasicSword::Create
(
	const float				fAttackCool,
	const D3DXVECTOR3&		vecPos, 
	const D3DXVECTOR3&		vecSize
)
{
	CBasicSword* pInstance = new CBasicSword;

	pInstance->SetAttackCool(fAttackCool);
	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->m_tInfo.SetSize(vecSize);

	return pInstance;
}

CBasicSword * CBasicSword::Create(const float fAttackCool, const D3DXVECTOR3 & vecSize)
{
	CBasicSword* pInstance = new CBasicSword;

	pInstance->SetAttackCool(fAttackCool);

	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(pInstance->m_wStrObjectKey, pInstance->m_wStrObjectStatus);
	pInstance->m_tInfo.SetSize(D3DXVECTOR3(vecSize.x / pTexInfo->tImgInfo.Width, vecSize.y / pTexInfo->tImgInfo.Height, vecSize.z));

	return pInstance;
}

void CBasicSword::CreateEffect()
{
	const D3DXVECTOR3& mousePos = CSINGLETON::pCameraMgr->GetPos() + CSINGLETON::pMouseMgr->GetMousePos();
	const D3DXVECTOR3& playerPos = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front()->GetPos();

	D3DXVECTOR3 vecPos = mousePos - playerPos;

	D3DXVec3Normalize(&vecPos, &vecPos);

	float fAngle = acosf(D3DXVec3Dot(&vecPos, &m_tInfo.vLook));

	if (vecPos.x < 0.f)
	{
		fAngle *= REVERSE;
	}

	vecPos *= SWORD_LENGTH;

	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_EFFECT,
		CNormalAttackEffect::Create
		(
			ATTACK_FROM::ATTACK_FROM_PLAYER,
			m_fDamage,
			fAngle,
			vecPos + m_tInfo.vPos,
			SWORD_SIZE,
			L"FX",
			L"BasicSwordSwing",
			3
		)
	);
}
