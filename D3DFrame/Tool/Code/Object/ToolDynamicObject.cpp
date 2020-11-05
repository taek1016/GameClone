#include "stdafx.h"
#include "ToolDynamicObject.h"

#include "Transform.h"
#include "Shader.h"

USING(Engine)

CToolDynamicObject::CToolDynamicObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: CToolGameObject(pGraphicDev)
	, m_pSphereCollider(nullptr)
{
}

CToolDynamicObject::CToolDynamicObject(const CToolDynamicObject & rhs)
	: CToolGameObject(rhs)
	, m_pSphereCollider(nullptr)
{
}

CToolDynamicObject::~CToolDynamicObject(void)
{
}

HRESULT CToolDynamicObject::Initialize_GameObject(void)
{
	DLL::pResourcesMgr->Clone<CDynamicMesh>(0, m_wStrRenderKey.c_str())->Attach(L"DynamicMesh", this, ID_DYNAMIC);
	
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"MeshShader", this, ID_STATIC);

	return S_OK;
}

HRESULT CToolDynamicObject::Late_Initialize(void)
{
	m_pMesh = Get_Component<CDynamicMesh>(L"DynamicMesh", ID_DYNAMIC);
	NULL_CHECK_RETURN(m_pMesh, E_FAIL);

	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);

	m_pShaderCom = Get_Component<CShader>(L"MeshShader", ID_STATIC);

	initialize_Bones();
	initialize_Animation();

	return S_OK;
}

Engine::_int CToolDynamicObject::Update_GameObject(const Engine::_float & fTimeDelta)
{
	Engine::_int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

	if (m_pMesh)
	{
		m_pMesh->Play_Animation(fTimeDelta);
	}

	return iExit;
}

HRESULT CToolDynamicObject::SetUp_ConstantTable(LPD3DXEFFECT & pEffect)
{
	_matrix			matWorld, matView, matProj;

	matWorld = *m_pTransform->Get_World();
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	const D3DLIGHT9*		pLight = DLL::pLightMgr->Get_LightInfo(0);
	NULL_CHECK_RETURN(pLight, S_OK);


	pEffect->SetVector("g_vLightDir", &_vec4(pLight->Direction, 0.f));
	pEffect->SetVector("g_vLightDiffuse", (_vec4*)&pLight->Diffuse);
	pEffect->SetVector("g_vLightSpecular", (_vec4*)&pLight->Specular);
	pEffect->SetVector("g_vLightAmbient", (_vec4*)&pLight->Ambient);


	D3DMATERIAL9		tMtrlInfo;
	ZeroMemory(&tMtrlInfo, sizeof(D3DMATERIAL9));

	tMtrlInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tMtrlInfo.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	tMtrlInfo.Power = 100.f;

	pEffect->SetVector("g_vMtrlDiffuse", (_vec4*)&tMtrlInfo.Diffuse);
	pEffect->SetVector("g_vMtrlSpecular", (_vec4*)&tMtrlInfo.Specular);
	pEffect->SetVector("g_vMtrlAmbient", (_vec4*)&tMtrlInfo.Ambient);

	_vec4		vCamPos;
	D3DXMatrixInverse(&matView, NULL, &matView);
	memcpy(&vCamPos, &matView.m[3][0], sizeof(_vec4));

	pEffect->SetVector("g_vCamPos", &vCamPos);
	pEffect->SetFloat("g_fPower", tMtrlInfo.Power);

	return S_OK;
}
void CToolDynamicObject::Render_GameObject(void)
{
	if (nullptr == m_pMesh)
	{
		return;
	}
	const _matrix* pWorld = m_pTransform->Get_World();
	LPD3DXEFFECT	pEffect = m_pShaderCom->Get_EffectHandle();
	NULL_CHECK(pEffect);
	pEffect->AddRef();

	_uint	iPassMax = 0;

	FAILED_CHECK_RETURN(SetUp_ConstantTable(pEffect), );

	pEffect->Begin(&iPassMax, 0);

	pEffect->BeginPass(0);

	m_pMesh->Render_Meshes(pEffect);

	pEffect->EndPass();

	pEffect->End();

	Safe_Release(pEffect);
	_matrix matWorld;
	D3DXMatrixIdentity(&matWorld);
	memcpy(&matWorld.m[3], pWorld->m[3], sizeof(_vec3));

	if (m_pSphereCollider)
	{
		m_pSphereCollider->Render_Collider(COL_FALSE);
	}

	for (auto iter : m_mapActionCol)
	{
		iter.second->Render_Collider(COL_FALSE);
	}
}

Engine::CDynamicMesh * CToolDynamicObject::Get_DynamicMesh(void)
{
	return m_pMesh;
}

void CToolDynamicObject::Play_Animation(const Engine::_tchar* pKey)
{
	m_pMesh->Set_AnimationSet(m_mapAnimationIndexMap[pKey]);
}

void CToolDynamicObject::Set_RenderKey(const Engine::_tchar* pKey)
{
	m_wStrRenderKey = pKey;
}

void CToolDynamicObject::Add_SphereCollider(const Engine::_float & fRadius)
{
	if (nullptr == this)
	{
		return;
	}

	if (m_pSphereCollider)
	{
		Safe_Release(m_pSphereCollider);
	}

	m_pSphereCollider = CSphereCollider::Create(m_pGraphicDev, fRadius, 10, 10, m_pTransform->Get_World());
	m_pSphereCollider->Attach(L"SphereCollider", this, ID_STATIC);
}

void CToolDynamicObject::Delete_ActionCol(const Engine::_tchar * pName)
{
	auto iter = m_mapActionCol.find(pName);

	if (m_mapActionCol.end() == iter)
	{
		return;
	}

	Safe_Release(m_mapActionCol[pName]);
	m_mapActionCol.erase(iter);

	auto finder = find_if(m_listComponent[ID_DYNAMIC].begin(), m_listComponent[ID_DYNAMIC].end(), CTag_Finder(pName));
	if (m_listComponent[ID_DYNAMIC].end() == finder)
	{
		return;
	}

	m_listComponent[ID_DYNAMIC].erase(finder);
}

const wstring & CToolDynamicObject::Get_RenderKey(void) const
{
	return m_wStrRenderKey;
}

const map<wstring, const Engine::_int>* CToolDynamicObject::Get_AnimationKey(void) const
{
	return &m_mapAnimationIndexMap;
}

const list<wstring>* CToolDynamicObject::Get_BoneList(void) const
{
	return &m_BoneList;
}

const wstring & CToolDynamicObject::Get_ColliderBoneName(void) const
{
	return m_wStrColliderBoneName;
}

void CToolDynamicObject::Set_ColliderBoneName(const Engine::_tchar * pKey)
{
	m_wStrColliderBoneName = pKey;
}

const map<wstring, CActionCom*>* CToolDynamicObject::Get_ActionMap(void) const
{
	return &m_mapActionCol;
}

void CToolDynamicObject::Add_ActionCol(const Engine::_tchar * pName, const Engine::_float & fCoolTime, const Engine::_float& fRadius)
{
	auto iter = m_mapActionCol.find(pName);

	if (m_mapActionCol.end() != iter)
	{
		CActionCom* pCom = CActionCom::Create(m_pGraphicDev, pName, fCoolTime, fRadius, 10, 10, m_pTransform->Get_World());
		Safe_Release(m_mapActionCol[pName]);
		m_mapActionCol[pName] = pCom;
		pCom->Attach(pName, this, ID_DYNAMIC);
	}
	else
	{
		CActionCom* pCom = CActionCom::Create(m_pGraphicDev, pName, fCoolTime, fRadius, 10, 10, m_pTransform->Get_World());
		pCom->Attach(pName, this, ID_DYNAMIC);
		m_mapActionCol.emplace(pName, pCom);
	}
}

void CToolDynamicObject::initialize_Bones(void)
{
	const list<Engine::D3DXMESHCONTAINER_DERIVED*>* pContainerList = m_pMesh->Get_ContainerList();

	string strBoneName;
	wstring wStrBoneNameConvert;

	_ulong iBoneNum = 0;

	for (auto iterList : *pContainerList)
	{
		iBoneNum = iterList->dwNumBones;

		for (_ulong i = 0; i < iBoneNum; ++i)
		{
			strBoneName = iterList->pSkinInfo->GetBoneName(i);
			wStrBoneNameConvert.assign(strBoneName.begin(), strBoneName.end());

			_bool bDuplicated = false;

			for (auto iter : m_BoneList)
			{
				if (iter == wStrBoneNameConvert)
				{
					bDuplicated = true;
					break;
				}
			}

			if (!bDuplicated)
			{
				m_BoneList.push_back(wStrBoneNameConvert);
			}
		}
	}
}

void CToolDynamicObject::initialize_Animation(void)
{
	LPD3DXANIMATIONCONTROLLER pAniController = m_pMesh->Get_AniController()->Get_AnimationCtrl();
	_int iAnimationSet = pAniController->GetNumAnimationSets();
	LPD3DXANIMATIONSET pAniSet = nullptr;

	CString strAnimationName;

	for (_int i = 0; i < iAnimationSet; ++i)
	{
		pAniController->GetAnimationSet(i, &pAniSet);
		strAnimationName = pAniSet->GetName();
		m_mapAnimationIndexMap.emplace(strAnimationName, i);
	}
}

CToolDynamicObject * CToolDynamicObject::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar* pKey)
{
	CToolDynamicObject* pInstance = new CToolDynamicObject(pGraphicDev);

	pInstance->Set_RenderKey(pKey);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Engine::Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CToolDynamicObject::Clone(void)
{
	CToolDynamicObject* pInstance = new CToolDynamicObject(*this);

	static int iCount = 0;

	const int iMaxStr = 256;
	TCHAR szName[iMaxStr]{};
	wsprintf(szName, L"%s%d", m_wStrRenderKey.c_str(), iCount++);

	pInstance->Set_RenderKey(m_wStrRenderKey.c_str());
	pInstance->set_Name(szName);

	return pInstance;
}

void CToolDynamicObject::SaveData(HANDLE hFile)
{
}

void CToolDynamicObject::LoadData(HANDLE hFile)
{
}

inline void CToolDynamicObject::Free(void)
{
	CToolGameObject::Free();
}
