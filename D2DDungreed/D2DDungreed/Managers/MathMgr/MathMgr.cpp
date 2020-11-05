#include "stdafx.h"
#include "MathMgr.h"

IMPLEMENT_SINGLETON(CMathMgr)

CMathMgr::CMathMgr()
	: m_matScale()
	, m_matRotate()
	, m_matMove()
	, m_fGravity(9.8f)
{
	CMathMgr::InitializeMat();
	CMathMgr::AssertMember();
}

CMathMgr::~CMathMgr()
{
	CMathMgr::InitializeMat();
	CMathMgr::AssertMember();
}

HRESULT CMathMgr::CalculateMove
(
	D3DXMATRIX&			matWorld,
	const D3DXVECTOR3&	vecPos,
	const D3DXVECTOR3&	vecSize,
	const	float		fAngle,
	const	bool		bScroll
)
{
	::D3DXMatrixIdentity(&matWorld);
	CMathMgr::MakeIdentity();

	::D3DXMatrixScaling(&m_matScale, vecSize.x, vecSize.y, vecSize.z);
	::D3DXMatrixRotationZ(&m_matRotate, fAngle);

	if (bScroll)
	{
		const D3DXVECTOR3& vecCameraPos = CSINGLETON::pCameraMgr->GetPos();
		::D3DXMatrixTranslation
		(
			&m_matMove,
			vecPos.x - vecCameraPos.x,
			vecPos.y - vecCameraPos.y,
			vecPos.z
		);
	}
	else
	{
		::D3DXMatrixTranslation
		(
			&m_matMove,
			vecPos.x,
			vecPos.y,
			vecPos.z
		);
	}
	matWorld = (m_matScale * m_matRotate * m_matMove);

	return S_OK;
}

HRESULT CMathMgr::CalculateMove
(
	D3DXMATRIX & matWorld,
	const D3DXVECTOR3 & vecPos, 
	const D3DXVECTOR3 & vecSize, 
	const float fSelfRotAngle, 
	const float fRevAngle, 
	const D3DXMATRIX & matParent
)
{
	::D3DXMatrixIdentity(&matWorld);
	CMathMgr::MakeIdentity();

	::D3DXMatrixScaling(&m_matScale, vecSize.x, vecSize.y, vecSize.z);
	::D3DXMatrixRotationZ(&m_matRotate, fSelfRotAngle);

	::D3DXMatrixTranslation
	(
		&m_matMove,
		vecPos.x,
		vecPos.y,
		vecPos.z
	);

	::D3DXMatrixRotationZ(&m_matRevolve, fRevAngle);
	matWorld = (m_matScale * m_matRotate * m_matMove * m_matRevolve * matParent);

	return S_OK;
}

float CMathMgr::ConvertGravity(const GRAVITY_INFO* pInfo)
{
	if (nullptr == pInfo)
	{
		return 0.f;
	}

	static const float fGravity = 9.8f;

	return pInfo->fPower + fGravity * powf(pInfo->fAcc, 2.f) TO_HALF;
}

void CMathMgr::MakeIdentity()
{
	::D3DXMatrixIdentity(&m_matMove);
	::D3DXMatrixIdentity(&m_matRotate);
	::D3DXMatrixIdentity(&m_matScale);
	::D3DXMatrixIdentity(&m_matRevolve);
}

void CMathMgr::AssertMember() const
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			assert(0 == m_matMove.m[i][j]);
			assert(0 == m_matRotate.m[i][j]);
			assert(0 == m_matScale.m[i][j]);
		}
	}
}

void CMathMgr::InitializeMat()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_matMove.m[i][j] = 0;
			m_matRotate.m[i][j] = 0;
			m_matScale.m[i][j] = 0;
		}
	}
}
