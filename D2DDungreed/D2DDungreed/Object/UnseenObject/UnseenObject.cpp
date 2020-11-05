#include "stdafx.h"
#include "UnseenObject.h"


CUnseenObject::CUnseenObject()
{
}


CUnseenObject::~CUnseenObject()
{
}

CUnseenObject* CUnseenObject::Create()
{
	CUnseenObject*	pInstance = new CUnseenObject;

	assert(nullptr != pInstance);

	pInstance->m_tInfo.SetSize(D3DXVECTOR3(1.f, 1.f, 0.f));

	return pInstance;
}

int CUnseenObject::Update()
{
	return 0;
}

void CUnseenObject::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(
		m_tInfo.matWorld,
		m_tInfo.vPos,
		m_tInfo.vSize,
		m_fAngle);
}

void CUnseenObject::Render()
{
}
