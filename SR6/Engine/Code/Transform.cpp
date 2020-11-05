#include "Transform.h"

USING(Engine)

CTransform::CTransform(void)
	: CComponent()
	, m_vScale(1.f, 1.f, 1.f)
	, m_vAngle(0.f, 0.f, 0.f)
{
	ZeroMemory(m_vInfo, sizeof(_vec3) * INFO::INFO_END);
	CComponent::Set_ComType(COMPONENT_TYPE::TRANSFORM);
}

CTransform::CTransform(const CTransform& rhs)
	: CComponent(rhs),
	m_vAngle(rhs.m_vAngle),
	m_vScale(rhs.m_vScale)
{
	memcpy(m_vInfo, rhs.m_vInfo, sizeof(_vec3) * INFO_END);
}

CTransform::~CTransform(void)
{
}

const _vec3 * CTransform::Get_Info(INFO eType)
{
	return &m_vInfo[eType];
}

void CTransform::Get_Info(INFO eType, _vec3* pInfo)
{
	*pInfo = m_vInfo[eType];
}

void CTransform::Move_Pos(const _vec3* const pDir)
{
	m_vInfo[INFO_POS] += *pDir;
}

void CTransform::Rotation(ROTATION eType, const _float& fAngle)
{
	*(reinterpret_cast<_float*>(&m_vAngle) + eType) += fAngle;
}

const _matrix * CTransform::Compute_LookAtTarget(const _vec3* pTargetPos)
{
	_vec3		vDir = *pTargetPos - m_vInfo[INFO_POS];

	_vec3		vAxis, vUp;
	_matrix		matRot;

	return D3DXMatrixRotationAxis
				(
					&matRot,
					D3DXVec3Cross(&vAxis, &m_vInfo[INFO_UP], &vDir),
					acosf	(
								D3DXVec3Dot(D3DXVec3Normalize(&vDir, &vDir),
								D3DXVec3Normalize(&vUp, &m_vInfo[INFO_UP]))
							)
				);
}

void CTransform::Chase_Target(const _vec3* pTargetPos, const _float& fSpeed)
{
	_vec3		vDir = *pTargetPos - m_vInfo[INFO_POS];

	m_vInfo[INFO_POS] += *D3DXVec3Normalize(&vDir, &vDir) * fSpeed;

	_matrix		matRot = *Compute_LookAtTarget(pTargetPos);
	_matrix		matScale, matTrans;

	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixTranslation(&matTrans, m_vInfo[INFO_POS].x, m_vInfo[INFO_POS].y, m_vInfo[INFO_POS].z);

	m_matWorld = matScale * matRot * matTrans;
}

void CTransform::Set_Scale(const _float& fX, const _float& fY, const _float& fZ)
{
	m_vScale.x = fX;
	m_vScale.y = fY;
	m_vScale.z = fZ;
}

void CTransform::Set_Scale(const _vec3* pScale)
{
	m_vScale = *pScale;
}

void CTransform::Set_Pos(const _float& fX, const _float& fY, const _float& fZ)
{
	m_vInfo[INFO_POS].x = fX;
	m_vInfo[INFO_POS].y = fY;
	m_vInfo[INFO_POS].z = fZ;
}

void CTransform::Set_Pos(const _vec3 * pPos)
{
	m_vInfo[INFO_POS] = *pPos;
}

void CTransform::Set_Look(const _vec3 * pLook)
{
	m_vInfo[INFO::INFO_LOOK] = *pLook;
}

void CTransform::Set_Angle(const _vec3 * pAngle)
{
	m_vAngle = *pAngle;
}

void CTransform::Set_Angle(ROTATION eType, const _float & fAngle)
{
	m_vAngle[eType] = fAngle;
}

void CTransform::SetParent(CTransform * parent)
{
	m_pParentTransform = parent;
}


HRESULT CTransform::Initialize_Component(void)
{
	D3DXMatrixIdentity(&m_matWorld);

	for (_uint i = 0; i < INFO_END; ++i)
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));

	return S_OK;
}

_int CTransform::Update_Component(const _float & fTimeDelta)
{
	if (wcscmp(m_pGameObject->Get_Name(), L"LArm") == 0)
	{
		if(m_vAngle.x != 0)
			int aasv = 100;
	}
	D3DXMatrixIdentity(&m_matWorld);

	for (_uint i = 0; i < INFO_POS; ++i)
		memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));

	// 스케일
	for (_uint i = 0; i < INFO_POS; ++i)
	{
		D3DXVec3Normalize(&m_vInfo[i], &m_vInfo[i]);
		m_vInfo[i] *= *(reinterpret_cast<_float*>(&m_vScale) + i);
	}

	// 자전
	_matrix	matRot[ROT_END];
	D3DXMatrixRotationX(&matRot[ROT_X], m_vAngle.x);
	D3DXMatrixRotationY(&matRot[ROT_Y], m_vAngle.y);
	D3DXMatrixRotationZ(&matRot[ROT_Z], m_vAngle.z);

	// 이동
	for (_uint i = 0; i < INFO_POS; ++i)
	{
		for (_uint j = 0; j < ROT_END; ++j)
		{
			D3DXVec3TransformNormal(&m_vInfo[i], &m_vInfo[i], &matRot[j]);
		}
	}

	for (_uint i = 0; i < INFO_END; ++i)
		memcpy(&m_matWorld.m[i][0], &m_vInfo[i], sizeof(_vec3));

	if (m_pParentTransform != nullptr)
	{
		m_matWorld *= *m_pParentTransform->Get_World();
	}

	return 0;
}

HRESULT CTransform::Attach(CGameObject * pObj, COMPONENTID com_ID)
{
	m_pGameObject = pObj;
	m_pGameObject->Add_Component(COMPONENT_TYPE::TRANSFORM, this, com_ID);

	return S_OK;
}

void CTransform::LoadData(HANDLE hFile)
{
	DWORD dwBytes = 0;
	DWORD total = 0;
	int size = 0;
	_tchar strName[255];
	ZeroMemory(strName, 255);
	ReadFile(hFile, &size, sizeof(size), &dwBytes, nullptr);

	if (size != 0)
	{
		ReadFile(hFile, strName, size, &dwBytes, nullptr);
	}

	ReadFile(hFile, &m_vInfo[INFO_POS], sizeof(m_vInfo[INFO_POS]), &dwBytes, nullptr);

	ReadFile(hFile, &m_vScale, sizeof(m_vScale), &dwBytes, nullptr);

	ReadFile(hFile, &m_vAngle, sizeof(m_vAngle), &dwBytes, nullptr);

}

CTransform * CTransform::Create(void)
{
	CTransform*		pInstance = new CTransform;

	if (FAILED(pInstance->Initialize_Component()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CTransform::Clone()
{
	return new CTransform(*this);
}