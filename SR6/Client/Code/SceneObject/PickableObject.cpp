#include "stdafx.h"
#include "PickableObject.h"

USING(Engine)

CPickableObject::CPickableObject()
	:CInGameObject()
{
}

CPickableObject::CPickableObject(const CPickableObject & rhs)
	:CInGameObject(rhs)
{
}

void CPickableObject::PickUp(CGameObject* picker)
{
	m_bIsPicked = true;
	CTransform* transform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	transform->SetParent(picker->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC));
	transform->Set_Pos(&_vec3(0, 0, 2));
	transform->Set_Scale(&_vec3(1, 1, 1));
}

void CPickableObject::Drop()
{
	m_bIsPicked = false;
	CTransform* transform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	_matrix matWorld = *transform->Get_World();
	transform->SetParent(nullptr);
	transform->Set_Scale(&_vec3(6, 6, 1));
	transform->Set_Pos(&_vec3(matWorld._41, matWorld._42, matWorld._43));
}

Engine::_int CPickableObject::Update_GameObject(const Engine::_float & fTimeDelta)
{
	CInGameObject::Update_GameObject(fTimeDelta);
	
	return Engine::_int();
}

HRESULT CPickableObject::Initialize_GameObject()
{
	CInGameObject::Initialize_GameObject();
	m_vecVertices.push_back(_vec3(-0.5f, 0.5f, 0.f));
	m_vecVertices.push_back(_vec3(0.5f, 0.5f, 0.f));
	m_vecVertices.push_back(_vec3(0.5f, -0.5f, 0.f));
	m_vecVertices.push_back(_vec3(-0.5f, -0.5f, 0.f));
	return S_OK;
}

Engine::_bool CPickableObject::IsPicked(Engine::_vec3 vOrigin, Engine::_vec3 vDir, Engine::_float fMaxDistance, Engine::_float *distance)
{
	D3DXVec3Normalize(&vDir, &(vDir - vOrigin));
	m_vecWorldvtx.clear();
	for (auto ele : m_vecVertices)
	{
		_vec3 v = ele;
		D3DXVec3TransformCoord(&v, &v, &m_matBill);
		m_vecWorldvtx.push_back(v);
	}

	float u, v, dist = 0;
	bool retVal = D3DXIntersectTri(&m_vecWorldvtx[0], &m_vecWorldvtx[1], &m_vecWorldvtx[2], &vOrigin, &vDir, &u, &v, &dist);

	if (!retVal)
	{
		retVal = D3DXIntersectTri(&m_vecWorldvtx[0], &m_vecWorldvtx[2], &m_vecWorldvtx[3], &vOrigin, &vDir, &u, &v, &dist);
	}
	*distance = dist;
	if (dist > fMaxDistance)
		return false;
	
	return retVal;
}

void CPickableObject::freeMem()
{
	CInGameObject::freeMem();
}
