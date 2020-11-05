#include "Transform.h"

USING(Engine)

CTransform::CTransform(void)
	: CComponent()
	, m_vScale(1.f, 1.f, 1.f)
	, m_vAngle(0.f, 0.f, 0.f)
{
	::ZeroMemory(m_vInfo, sizeof(_vec3) * INFO_END);
	m_vInfo[INFO_LOOK] = { 0.f, 0.f, 1.f };
	m_vInfo[INFO_UP] = { 0.f, 1.f, 0.f };
}

CTransform::CTransform(const CTransform& rhs)
	: CComponent(rhs)
	, m_vAngle(rhs.m_vAngle)
	, m_vScale(rhs.m_vScale)
{
	memcpy(m_vInfo, rhs.m_vInfo, sizeof(_vec3) * INFO::INFO_END);
	memcpy(&m_matWorld, &rhs.m_matWorld, sizeof(_matrix));
}

CTransform::~CTransform(void)
{
}

HRESULT CTransform::Late_Initialize(void)
{
	return S_OK;
}

HRESULT CTransform::Initialize_Component(void)
{
	D3DXMatrixIdentity(&m_matWorld);

	for (_uint i = 0; i < INFO_END; ++i)
	{
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));
	}

	return S_OK;
}

_int CTransform::Update_Component(const _float& fTimeDelta)
{
	D3DXMatrixIdentity(&m_matWorld);

	for (_uint i = 0; i < INFO_POS; ++i)
	{
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));
	}

	// 크기 변환 적용
	for (_uint i = 0; i < INFO_POS; ++i)
	{
		D3DXVec3Normalize(&m_vInfo[i], &m_vInfo[i]);
		m_vInfo[i] *= *(reinterpret_cast<_float*>(&m_vScale) + i);
	}

	// 회전 적용
	_matrix			matRot[ROT_END];

	D3DXMatrixRotationX(&matRot[ROT_X], m_vAngle.x);
	D3DXMatrixRotationY(&matRot[ROT_Y], m_vAngle.y);
	D3DXMatrixRotationZ(&matRot[ROT_Z], m_vAngle.z);

	for (_uint i = 0; i < INFO_POS; ++i)
	{
		for (_uint j = 0; j < ROT_END; ++j)
		{
			D3DXVec3TransformNormal(&m_vInfo[i], &m_vInfo[i], &matRot[j]);
		}
	}

	for (_uint i = 0; i < INFO_END; ++i)
	{
		memcpy(&m_matWorld.m[i][0], &m_vInfo[i], sizeof(_vec3));
	}
	return 0;
}

void CTransform::Move_Pos(const _vec3* const pDir)
{
	m_vInfo[INFO::INFO_POS] += *pDir;
}

void CTransform::Rotation(ROTATION eType, const _float & fAngle)
{
	*(reinterpret_cast<_float*>(&m_vAngle) + eType) += fAngle;

	if (m_vAngle[eType] >= D3DXToRadian(360.f))
	{
		m_vAngle[eType] -= D3DXToRadian(360.f);
	}
}

void CTransform::Compute_LookAtTarget(const _vec3* pTargetPos)
{
	_vec3 vDir = *pTargetPos - m_vInfo[INFO_POS];
	vDir.y = 0.f;

	_float		fAngle = acosf(D3DXVec3Dot(D3DXVec3Normalize(&vDir, &vDir), &_vec3(0.f, 0.f, 1.f)));

	if (vDir.x > 0)
	{
		m_vAngle.y = (fAngle);
	}
	else
	{
		m_vAngle.y = -(fAngle);
	}
}

//void CTransform::Chase_Target(const _vec3* pTargetPos, const _float& fSpeed)
//{
//	_vec3		vDir = *pTargetPos - m_vInfo[INFO::INFO_POS];
//
//	m_vInfo[INFO::INFO_POS] += *D3DXVec3Normalize(&vDir, &vDir) * fSpeed;
//
//	_matrix matRot = *Compute_LookAtTarget(pTargetPos);
//	_matrix	matScale, matTrans;
//
//	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
//	D3DXMatrixTranslation(&matTrans, m_vInfo[INFO_POS].x, m_vInfo[INFO_POS].y, m_vInfo[INFO_POS].z);
//
//	m_matWorld = matScale * matRot * matTrans;
//}

const _vec3* CTransform::Get_Info(const INFO & eInfoType) const
{
	return &m_vInfo[eInfoType];
}

const _vec3* CTransform::Get_Scale(void) const
{
	return &m_vScale;
}

const _vec3* CTransform::Get_Angle(void) const
{
	return &m_vAngle;
}

const _matrix* CTransform::Get_World(void) const
{
	return &m_matWorld;
}

void CTransform::Set_Info(const INFO& eInfoType, const _vec3* pVec)
{
	m_vInfo[eInfoType] = *pVec;
}

void CTransform::Set_Scale(const _vec3* pScale)
{
	m_vScale = *pScale;
}

void CTransform::Set_Angle(const ROTATION& eRotID, const _float& fAngle)
{
	m_vAngle[eRotID] = fAngle;
}

void CTransform::Set_Angle(const _vec3* pAngle)
{
	m_vAngle = *pAngle;
}

void CTransform::Set_WorldMatrix(const _matrix * matWorld)
{
	memcpy(&m_matWorld, matWorld, sizeof(_matrix));
}

CTransform* CTransform::Create(void)
{
	CTransform*		pInstance = new CTransform;

	if (FAILED(pInstance->Initialize_Component()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent* CTransform::Clone(void)
{
	return new CTransform(*this);
}