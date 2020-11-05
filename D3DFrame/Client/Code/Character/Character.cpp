#include "stdafx.h"
#include "Character.h"

USING(Engine)

CCharacterBase::CCharacterBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)

	, m_iCurAnimationIdx(0)
	, m_iPreAnimationIdx(999)
	, m_eSphereCol(COLLTYPE::COL_FALSE)

	, m_pMainSphereCollider(nullptr)
	, m_pMesh(nullptr)
	, m_pStatCom(nullptr)
	, m_pActionCol(nullptr)
	, m_pShaderCom(nullptr)
	, m_fMainColSize(0.f)
	, m_fHeight(0.f)
{
}

CCharacterBase::CCharacterBase(const CCharacterBase & rhs)
	: CGameObject(rhs)
	, m_iCurAnimationIdx(0)
	, m_iPreAnimationIdx(999)
	, m_fHeight(rhs.m_fHeight)
	, m_fMainColSize(rhs.m_fMainColSize)
	, m_eSphereCol(COLLTYPE::COL_FALSE)

	, m_pMainSphereCollider(nullptr)
	, m_pMesh(nullptr)
	, m_pStatCom(nullptr)
	, m_pActionCol(nullptr)
	, m_pShaderCom(nullptr)
{
	for (auto iter : rhs.m_mapAnimationIndexMap)
	{
		m_mapAnimationIndexMap.emplace(iter.first, iter.second);
	}

	for (auto iter : rhs.m_mapBone)
	{
		m_mapBone.emplace(iter.first, iter.second);
	}

	if (nullptr != rhs.m_pMesh)
	{
		m_pMesh = dynamic_cast<CDynamicMesh*>(rhs.m_pMesh->Clone());
		m_pMesh->Attach(L"Mesh", this, ID_STATIC);
	}

	if (nullptr != rhs.m_pMainSphereCollider)
	{
		m_pMainSphereCollider = dynamic_cast<CSphereCollider*>(rhs.m_pMainSphereCollider->Clone());
		m_pMainSphereCollider->Attach(L"MainSphereCol", this, ID_DYNAMIC);
	}

	if (nullptr != rhs.m_pActionCol)
	{
		m_pActionCol = dynamic_cast<CSphereCollider*>(rhs.m_pMainSphereCollider->Clone());
		m_pActionCol->Attach(L"ActionSphereCol", this, ID_DYNAMIC);
	}

	if (nullptr != rhs.m_pStatCom)
	{
		m_pStatCom = dynamic_cast<CStatCom*>(rhs.m_pStatCom->Clone());
		m_pStatCom->Attach(L"Stat", this, ID_STATIC);
	}

// 	for (auto iter : rhs.m_mapAction)
// 	{
// 		m_mapAction.emplace(iter.first, iter.second->Clone());
// 	}
}

CCharacterBase::~CCharacterBase(void)
{
}

HRESULT CCharacterBase::Late_Initialize()
{
	for (auto iter : m_listComponent[ID_STATIC])
	{
		iter.second->Late_Initialize();
	}

	for (auto iter : m_listComponent[ID_DYNAMIC])
	{
		iter.second->Late_Initialize();
	}

	return S_OK;
}

void CCharacterBase::Render_GameObject(void)
{
	LPD3DXEFFECT	pEffect = m_pShaderCom->Get_EffectHandle();
	NULL_CHECK(pEffect);
	pEffect->AddRef();

	_uint	iPassMax = 0;

	FAILED_CHECK_RETURN(setUp_ConstantTable(pEffect), );

	pEffect->Begin(&iPassMax, 0);

	pEffect->BeginPass(0);

	m_pMesh->Render_Meshes(pEffect);

	pEffect->EndPass();

	pEffect->End();

	Safe_Release(pEffect);

	if (g_bCollider || g_bActCol)
	{
		const _matrix* pWorldMat = m_pTransform->Get_World();
		if (g_bCollider && m_pMainSphereCollider)
		{
			m_pMainSphereCollider->Render_Collider(m_eSphereCol, pWorldMat);
		}
	
		if (g_bActCol)
		{
			for (auto iter : m_mapAction)
			{
				iter.second->Render_Collider(m_mapActColType[iter.first], pWorldMat);
			}
		}
	}
}

void CCharacterBase::Add_AnimationKey(const Engine::_tchar * pKey, const Engine::_int & iIdx)
{
	auto iter = m_mapAnimationIndexMap.find(pKey);

	if (m_mapAnimationIndexMap.end() != iter)
	{
		return;
	}

	m_mapAnimationIndexMap.emplace(pKey, iIdx);
}

void CCharacterBase::Set_AnimationSet(const Engine::_tchar * pKey)
{
	auto iter = m_mapAnimationIndexMap.find(pKey);

	if (m_mapAnimationIndexMap.end() == iter)
	{
		MessageBox(g_hWnd, L"존재하지 않는 애니메이션 키", L"Warning", MB_OK);
		assert(false);
		return;
	}
	
	m_iCurAnimationIdx = iter->second;
}

void CCharacterBase::Set_SphereColName(const Engine::_tchar * pName)
{
	const int iMaxStr = 256;
	char szNameCopy[iMaxStr]{};

	WideCharToMultiByte(CP_ACP, 0, pName, lstrlenW(pName), szNameCopy, iMaxStr, NULL, NULL);

	m_strColName = szNameCopy;
}

void CCharacterBase::Add_Action(const Engine::_tchar * pName, const Engine::_float & fCoolTime, const Engine::_float & fRadius)
{
	auto iter = m_mapAction.find(pName);

	if (m_mapAction.end() != iter)
	{
		Safe_Release(m_mapAction[pName]);
		m_mapAction.erase(iter);
	}

	CActionCom* pCom = CActionCom::Create(m_pGraphicDev, pName, fCoolTime, fRadius, 10, 10, m_pTransform->Get_World());
	pCom->Attach(pCom->Get_Name(), this, ID_DYNAMIC);
	m_mapAction.emplace(pCom->Get_Name(), pCom);

	m_mapActColType.emplace(pCom->Get_Name(), COLLTYPE::COL_FALSE);
}

void CCharacterBase::Set_Position(const Engine::_vec3 * pPos)
{
	m_dwNaviIdx = DLL::pPickMgr->Get_Index(pPos);

	_vec3 vPos = DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, pPos, &_vec3(0.f, 0.f, 0.f));
	
	m_pTransform->Set_Info(INFO::INFO_POS, &vPos);
}

void CCharacterBase::Add_MainCollider(const Engine::_float & fRadius)
{
	m_pMainSphereCollider = CSphereCollider::Create(m_pGraphicDev, fRadius, 10, 10, m_pTransform->Get_World());
	m_pMainSphereCollider->Attach(L"MainSphereCol", this, ID_STATIC);
}

void CCharacterBase::Hit(const Engine::_int & iDamage)
{
	::ZeroMemory(m_szHitDamage, sizeof(_tchar) * 64);
	wsprintf(m_szHitDamage, L"%d", abs(iDamage));

	m_pStatCom->Hit(iDamage);
	Set_AnimationSet(L"Hit");
	m_pMesh->Set_AnimationSet(m_iCurAnimationIdx);
}

Engine::_bool CCharacterBase::Is_Dead(void) const
{
	return m_pStatCom->Get_Dead();
}

void CCharacterBase::make_PosToView(Engine::_vec4 * pPos, const Engine::_float& fMoveX, const Engine::_float& fMoveY)
{
	_matrix matView, matProj;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXVec4Transform(pPos, pPos, &matView);
	D3DXVec4Transform(pPos, pPos, &matProj);

	_float rhw = 1.f / pPos->w;
	pPos->x *= rhw;
	pPos->y *= rhw;
	pPos->z *= rhw;

	pPos->x *= WINCX;
	pPos->x -= fMoveX;

	pPos->y *= WINCY;
	pPos->y += fMoveY;
	pPos->z = 0.f;
}

void CCharacterBase::read_Data(void)
{
	enum INT_DATA { HP_DATA, MP_DATA, ATT_DATA, ARMOR_DATA, INT_DATA_END };
	// 체력 : int, MP : int, 공격, 방어 int, 이동 float, 
	_tchar* szIntKey[] = { L"HP", L"MP", L"Att", L"Armor" };
	_int* iValues = new _int[INT_DATA_END]{};

	for (_int i = 0; i < INT_DATA_END; ++i)
	{
		iValues[i] = GetPrivateProfileInt(m_wStrName.c_str(), szIntKey[i], 0, L"../../Data/PrefabData/UnitPrefab.ini");
	}

	_vec3 vScale;
	vScale.x = get_ReadData(L"ScaleX");
	vScale.y = get_ReadData(L"ScaleY");
	vScale.z = get_ReadData(L"ScaleZ");

	HP_INFO tHP(iValues[HP_DATA], iValues[HP_DATA]);
	MP_INFO tMP(iValues[MP_DATA], iValues[MP_DATA]);
	ATT_ARMOR_INFO tAttArmor(iValues[ATT_DATA], iValues[ARMOR_DATA]);

	Safe_Delete_Array(iValues);

	_float fRun = get_ReadData(L"Run");
	_float fWalk = get_ReadData(L"Walk");

	MOVE_INFO tMove(fWalk, fRun);

	_float fDodge = get_ReadData(L"Dodge");
	_float fSpellCast = get_ReadData(L"Spell");

	PERCENT_INFO tPercent(fDodge, fSpellCast);

	_float fFireResist = get_ReadData(L"Fire");
	_float fIceResist = get_ReadData(L"Ice");
	_float fVisionResist = get_ReadData(L"Vision");

	RESIST_INFO tResist(fFireResist, fIceResist, fVisionResist);

	m_pStatCom->Set_TotalStat(UNIT_INFO(tHP, tMP, tAttArmor, tMove, tPercent, tResist));

	m_fMainColSize = get_ReadData(L"MainCol");
	m_fHeight = get_ReadData(L"Height");
}

Engine::_float CCharacterBase::get_ReadData(const Engine::_tchar * pKey)
{
	const _int iMaxStr = 256;
	_tchar szValue[iMaxStr]{};
	GetPrivateProfileString(m_wStrName.c_str(), pKey, L"0.f", szValue, iMaxStr, L"../../Data/PrefabData/UnitPrefab.ini");

	return static_cast<_float>(_wtof(szValue));
}

void CCharacterBase::play_Animation(void)
{
	if (m_iCurAnimationIdx == m_iPreAnimationIdx)
	{
		return;
	}
	m_pMesh->Set_AnimationSet(m_iCurAnimationIdx);
}

HRESULT CCharacterBase::setUp_ConstantTable(LPD3DXEFFECT & pEffect)
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

void CCharacterBase::initialize_Animation(void)
{
	if (!m_mapAnimationIndexMap.empty())
	{
		m_mapAnimationIndexMap.clear();
	}

	LPD3DXANIMATIONCONTROLLER pAniController = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC)->Get_AniController()->Get_AnimationCtrl();
	_int iAnimationSet = pAniController->GetNumAnimationSets();
	LPD3DXANIMATIONSET pAniSet = nullptr;

	string strAnimationName;
	const _int iMaxStr = 256;
	TCHAR szBoneNames[iMaxStr]{};

	for (_int i = 0; i < iAnimationSet; ++i)
	{
		::ZeroMemory(szBoneNames, sizeof(TCHAR) * iMaxStr);

		pAniController->GetAnimationSet(i, &pAniSet);
		strAnimationName = pAniSet->GetName();
		MultiByteToWideChar(CP_ACP, 0, strAnimationName.c_str(), static_cast<int>(strAnimationName.size()), szBoneNames, iMaxStr);

		m_mapAnimationIndexMap.emplace(szBoneNames, i);
	}
}

void CCharacterBase::reset_ActCol(void)
{
	for (auto iter : m_mapActColType)
	{
		m_mapActColType[iter.first] = COL_FALSE;
	}
}

void CCharacterBase::set_MoveAnimation(void)
{
	if (true == m_pStatCom->Get_Run())
	{
		Set_AnimationSet(L"Run");
	}
	else
	{
		Set_AnimationSet(L"Walk");
	}
}

void CCharacterBase::set_DeadAnimation(void)
{
	Set_AnimationSet(L"Death");
}

void CCharacterBase::set_AttackAnimation(void)
{
	Set_AnimationSet(L"Attack");
}

void CCharacterBase::add_BoneNames(const Engine::_tchar * pName, const Engine::_tchar * pBoneName)
{
	auto iter = m_mapBone.find(pName);

	if (m_mapBone.end() != iter)
	{
		iter->second = pBoneName;
	}
	else
	{
		m_mapBone.emplace(pName, pBoneName);
	}
}

void CCharacterBase::set_PreAnimationKey(void)
{
	m_iPreAnimationIdx = m_iCurAnimationIdx;
}

inline void CCharacterBase::Free(void)
{
	Engine::CGameObject::Free();

	m_mapAnimationIndexMap.clear();

	Safe_Release(m_pActionCol);

	m_mapAction.clear();
}