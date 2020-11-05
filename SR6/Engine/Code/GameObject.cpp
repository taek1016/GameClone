#include "GameObject.h"

#include "WeaponBase.h"
#include "ArmorBase.h"
USING(Engine)

CGameObject::CGameObject()
	: CBase()
	, m_iCloneNum(0)
{
	for (_int i = 0; i < COMPONENTID::ID_END; ++i)
	{
		m_vecComponent[i].resize(COMPONENT_TYPE::COMP_TYPE_END);
	}
}

CGameObject::CGameObject(const CGameObject & rhs)
	: CBase()
	, m_bClone(true)
	, m_iCloneNum(rhs.m_iCloneNum)
	, m_bIsChild(rhs.m_bIsChild)
	, m_eType(rhs.m_eType)
{
	for (_int i = 0; i < COMPONENTID::ID_END; ++i)
	{
		m_vecComponent[i].resize(COMPONENT_TYPE::COMP_TYPE_END);
	}

	_tchar szName[256]{};
	if (!m_bIsChild)
	{
			swprintf_s(szName, L"%s%i", rhs.Get_Name(), m_iCloneNum++);
			SetName(szName);
	}
	else
	{
		SetName(rhs.Get_Name());
	}

	for (_int i = 0; i < ID_END; ++i)
	{
		for (_int j = 0; j < COMPONENT_TYPE::COMP_TYPE_END; ++j)
		{
			if (nullptr == rhs.m_vecComponent[i][j])
			{
				continue;
			}
			m_vecComponent[i][j] = rhs.m_vecComponent[i][j]->Clone();
			m_vecComponent[i][j]->SetGameObject(this);
		}
	}
}

CGameObject::~CGameObject()
{
}

CComponent* CGameObject::Find_Component(const _int iComponentTag, COMPONENTID eID)
{
	auto	iter = m_vecComponent[eID][iComponentTag];

	if (iter == nullptr)
		return nullptr;

	return iter;
}

void CGameObject::SetName(const _tchar * pKey)
{
	m_wStrObjName = pKey;
}

HRESULT CGameObject::Add_Component(const _int iComponentTag, CComponent* pComponent, COMPONENTID com_id)
{
	if (iComponentTag >= COMPONENT_TYPE::COMP_TYPE_END)
	{
		return E_FAIL;
	}

	if (m_vecComponent[com_id][iComponentTag] != nullptr)
	{
		Safe_Release(m_vecComponent[com_id][iComponentTag]);
	}

	m_vecComponent[com_id][iComponentTag] = pComponent;

	return S_OK;
}

void CGameObject::Set_Weapon(CWeaponBase * pWeapon)
{
	m_pWeapon = pWeapon;
	if (m_pWeapon)
	{
		m_pWeapon->Set_Obj(this);
	}
}

void CGameObject::AddChildObject(CGameObject * obj)
{
	obj->m_bIsChild = true;
	m_vecChildObject.push_back(obj);
}

CGameObject * CGameObject::GetChildObject(const _tchar * strName)
{
	for (auto ele : m_vecChildObject)
	{
		if (wcscmp(ele->Get_Name(), strName) == 0)
		{
			return ele;
		}
		CGameObject* obj = ele->GetChildObject(strName);
		if (obj != nullptr)
			return obj;
	}
	return nullptr;
}

vector<CGameObject*> CGameObject::GetChildObjects()
{
	return m_vecChildObject;
}

HRESULT CGameObject::Initialize_GameObject(void)
{
	return S_OK;
}

_int CGameObject::Update_GameObject(const _float& fTimeDelta)
{
	for (auto& iter : m_vecComponent[ID_DYNAMIC])
	{
		// 컴포넌트가 없을 경우도 있어서 continue 걸음.
		if (nullptr == iter)
		{
			continue;
		}

		iter->Update_Component(fTimeDelta);
	}

	if (m_pWeapon)
	{
		m_pWeapon->Update_GameObject(fTimeDelta);
	}
	if (m_pArmorBase)
	{
		m_pArmorBase->Update_GameObject(fTimeDelta);
	}

	return 0;
}

void CGameObject::Render_GameObject(void)
{
}

const _tchar * CGameObject::Get_Name(void) const
{
	return m_wStrObjName.c_str();
}

CGameObject * CGameObject::Clone(const _vec3 * pPos)
{
	return nullptr;
}

void CGameObject::freeMem(void)
{
	// 컴포넌트 돌면서 삭제 돌림.
	DWORD dwRefCnt = 0;
	for (_int i = 0; i < COMPONENTID::ID_END; ++i)
	{
		for (auto iter : m_vecComponent[i])
		{
			Safe_Release(iter);
		}
		m_vecComponent[i].clear();
	}
	m_vecComponent->clear();

	Safe_Release(m_pWeapon);
	Safe_Release(m_pArmorBase);
}

void CGameObject::Attack(const _float& fTimeDelta)
{
	if (m_pWeapon)
	{
		m_pWeapon->Attack(fTimeDelta);
	}
}