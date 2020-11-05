#include "GameObject.h"
#include "Transform.h"

USING(Engine)

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBase()
	, m_pGraphicDev(pGraphicDev)
	, m_pTransform(nullptr)
{
	m_pGraphicDev->AddRef();
}

CGameObject::CGameObject(const CGameObject& rhs)
	: CBase()
	, m_pGraphicDev(rhs.m_pGraphicDev)
	, m_wStrName(rhs.m_wStrName)
{
	m_pGraphicDev->AddRef();

	for (_int i = 0; i < ID_END; ++i)
	{
		for (auto iter : rhs.m_listComponent[i])
		{
			if (nullptr != iter.second)
			{
				Add_Component(iter.first, iter.second->Clone(), static_cast<COMPONENTID>(i));
			}
		}
	}
}

CGameObject::~CGameObject(void)
{
}

void CGameObject::set_Name(const Engine::_tchar* pName)
{
	if (nullptr != pName)
	{
		m_wStrName = pName;
	}
}

CComponent * CGameObject::find_Component(const _tchar* pComponentTag, COMPONENTID eID)
{
	auto	iter = find_if(m_listComponent[eID].begin(), m_listComponent[eID].end(), CTag_Finder(pComponentTag));

	if (iter == m_listComponent[eID].end())
		return nullptr;

	return iter->second;
}

_float CGameObject::Get_ViewZ(void) const
{
	return m_fViewZ;
}

CComponent* CGameObject::Add_Component(const _tchar * pComponentTag, CComponent* pComponent, COMPONENTID eID)
{
	auto iter = find_Component(pComponentTag, eID);

	if (nullptr != iter)
	{
		auto changeIter = find_if(m_listComponent[eID].begin(), m_listComponent[eID].end(), CTag_Finder(pComponentTag));
		Safe_Release(changeIter->second);
		changeIter->second = pComponent;

		return pComponent;
	}

	m_listComponent[eID].push_back(make_pair(pComponentTag, pComponent));

	return pComponent;
}

_int CGameObject::Update_GameObject(const _float & fTimeDelta)
{
	for (auto& iter : m_listComponent[ID_DYNAMIC])
	{
		iter.second->Update_Component(fTimeDelta);
	}

	return 0;
}

void CGameObject::Render_GameObject(void)
{
}

void CGameObject::Set_Pos(const _vec3* pPos)
{
	m_pTransform->Set_Info(INFO::INFO_POS, pPos);
}

void CGameObject::Set_Look(const _vec3* pLook)
{
	m_pTransform->Set_Info(INFO::INFO_LOOK, pLook);
}

void CGameObject::Set_Scale(const _vec3 * pScale)
{
	m_pTransform->Set_Scale(pScale);
}

void CGameObject::Set_Rotation(ROTATION eRot, const _float & fAngle)
{
	m_pTransform->Rotation(eRot, fAngle);
}

void CGameObject::Compute_ViewZ(void)
{
	_matrix		matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);

	_vec3	vCamPos;
	memcpy(&vCamPos, &matView.m[3][0], sizeof(_vec3));

	m_fViewZ = D3DXVec3Length(&(vCamPos - *m_pTransform->Get_Info(INFO_POS)));
}

const _tchar* CGameObject::Get_Name(void) const
{
	return m_wStrName.c_str();
}

const _vec3* CGameObject::Get_Pos(void)
{
	return m_pTransform->Get_Info(INFO_POS);
}

const _vec3 * CGameObject::Get_CenterPos(void)
{
	return m_pTransform->Get_Info(INFO::INFO_POS);
}

inline void CGameObject::Free(void)
{
	for (_uint i = 0; i < ID_END; ++i)
	{
		for (auto iter : m_listComponent[i])
		{
			Safe_Release(iter.second);
		}
		m_listComponent[i].clear();
	}

	Safe_Release(m_pGraphicDev);
}