#include "stdafx.h"
#include "Monster.h"

#include "Item/WeaponBase.h"

#include "Effect/Particle/GreenBloodParticle.h"

#include "Player.h"

USING(Engine)

CMonsterBase::CMonsterBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCharacterBase(pGraphicDev)
	, m_pWeapon(nullptr)
	, m_pWeaponMatrix(nullptr)

	, m_bAfterAct(false)
	, m_bMeleeAtt(false)
	, m_bHit(false)
	, m_bDead(false)
	, m_bLooted(false)
	, m_fCurPatternTime(0.f)
	, m_iCurPattern(0)
	, m_iExp(0)
	, m_iMoney(0)
	, m_fCurDeadTime(0.f)
	, m_fDeadLifeTime(0.f)
	, m_tColor(1.f, 1.f, 1.f, 1.f)

	, m_fAfterAct(0.f)
	, m_fBeginActTime(0.f)
{
}

CMonsterBase::CMonsterBase(const CMonsterBase & rhs)
	: CCharacterBase(rhs)
	, m_pWeapon(nullptr)
	, m_pWeaponMatrix(nullptr)

	, m_bAfterAct(false)
	, m_bMeleeAtt(false)
	, m_bHit(false)
	, m_bDead(false)
	, m_bLooted(false)
	, m_tColor(rhs.m_tColor)

	, m_fCurDeadTime(0.f)
	, m_fDeadLifeTime(rhs.m_fDeadLifeTime)

	, m_fCurPatternTime(0.f)
	, m_iCurPattern(0)
	, m_iExp(rhs.m_iExp)
	, m_iMoney(rhs.m_iMoney)

	, m_fAfterAct(0.f)
	, m_fBeginActTime(0.f)
{
	if (nullptr != rhs.m_pWeapon)
	{
		m_pWeapon = dynamic_cast<CWeaponBase*>(rhs.m_pWeapon->Clone());
	}
}

CMonsterBase::~CMonsterBase(void)
{
}

HRESULT CMonsterBase::Initialize_GameObject()
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);

	CStatCom::Create()->Attach(L"Stat", this, ID_STATIC);

	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"MeshShader", this, ID_STATIC);

	initialize_Animation();

	return S_OK;
}

HRESULT CMonsterBase::Late_Initialize()
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);

	m_pMesh = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);

	m_pStatCom = Get_Component<CStatCom>(L"Stat", ID_STATIC);

	m_pShaderCom = Get_Component<CShader>(L"MeshShader", ID_STATIC);

	CCharacterBase::Late_Initialize();

	return S_OK;
}

void CMonsterBase::Render_GameObject(void)
{
	m_pMesh->Play_Animation(m_fTimeDelta);

	CCharacterBase::Render_GameObject();

	if (nullptr != m_pWeapon)
	{
		m_pWeapon->Update_GameObject(m_fTimeDelta);
		m_pWeapon->Render_GameObject();
	}
}

Engine::_int CMonsterBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	set_PreAnimationKey();
	if (m_pStatCom->Get_Dead())
	{
		Set_AnimationSet(L"Death");
		//if (m_bDead)
		//{
		//	m_fCurDeadTime += fTimeDelta;
		//	if (m_fCurDeadTime >= 3.f)
		//	{
		//	}
		//	print_DeadInfo(fTimeDelta);
		//	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);
		//	return 0;
		//}

		play_Animation();

		if (false == m_pMesh->Is_AnimationSetEnd())
		{
			m_pMesh->Play_Animation(fTimeDelta);
		}
		else
		{
			_tchar szDeathSound[32]{};
			wsprintf(szDeathSound, L"%s%s", Get_Name(), L"Death.wav");

			DLL::pSoundMgr->PlaySound(szDeathSound, CSoundMgr::MONSTER);
			DLL::pSoundMgr->SetVolume(CSoundMgr::MONSTER, 0.3f);

			DLL::pInventory->Add_Money(m_iMoney);
			DLL::pQuestMgr->Kill_Monster(m_wStrName.c_str());
			DLL::pMouseMgr->Clear_PickTarget();
			dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front())->Get_Exp(m_iExp);

			return DEAD_OBJ;
		}

		print_DeadInfo(fTimeDelta);

		DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

		return 0;
	}

	m_fTimeDelta = fTimeDelta;

	set_PreAnimationKey();

	for (auto iter : m_mapAction)
	{
		iter.second->Update_Component(fTimeDelta);
	}

	reset_ActCol();

	if (m_pMesh->Is_AnimationSetEnd())
	{
		if (m_bMeleeAtt && m_pWeapon)
		{
			m_pWeapon->Cancel_Attack();
			m_bMeleeAtt = false;
		}
	}

	act_Determine(fTimeDelta);

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	play_Animation();

	mouse_Pick();

	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

	if (m_bHit)
	{
		print_Hit(fTimeDelta);
	}

	return iExit;
}

void CMonsterBase::Hit(const Engine::_int & iDamage)
{
	if (m_pStatCom->Get_Dead())
	{
		return;
	}

	CCharacterBase::Hit(iDamage);
	m_bHit = true;
	m_fHitHeight = 0.f;

	_tchar szHitSound[32]{};
	wsprintf(szHitSound, L"%s%s", Get_Name(), L"Hit.wav");

	DLL::pSoundMgr->PlaySound(szHitSound, CSoundMgr::MONSTER);
	DLL::pSoundMgr->SetVolume(CSoundMgr::MONSTER, 0.3f);

	for (_int i = 0; i < 5; ++i)
	{
		CGreenBloodParticle* pParticle = CGreenBloodParticle::Create(m_pGraphicDev);
		_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
		vPos.y += 5.f;
		pParticle->Set_Pos(&vPos);
		_vec3 vRight = *m_pTransform->Get_Info(INFO_RIGHT) * -1.f;
		vRight.z -= 1.f * i;
		pParticle->Set_Dir(&vRight);
		DLL::pObjMgr->Add_GameObject(L"Effect", pParticle);
	}
}

void CMonsterBase::print_DeadInfo(const Engine::_float& fTimeDelta)
{
	::ZeroMemory(m_szDieMessage, sizeof(_tchar) * 256);

	const _int iGoldConverter = 10000;
	const _int iSilverConverter = 100;

	_int iMoneyCopy = m_iMoney;
	const _int iGold = iMoneyCopy / iGoldConverter;
	iMoneyCopy %= iGoldConverter;

	const _int iSilver = iMoneyCopy / iSilverConverter;
	iMoneyCopy %= iSilverConverter;

	wsprintf(m_szDieMessage, L"%d골드 %d실버 %d쿠퍼, 경험치 %d를 얻었습니다.", iGold, iSilver, iMoneyCopy, m_iExp);

	_vec3 vSize(15.f, 20.f, 1.f);
	const _float fHalf = 0.5f;
	_vec3 vPos(-WINCX * fHalf * 0.9f, -WINCY * fHalf  * 0.7f, 0.f);
	DLL::pFontMgr->Print_Font(&vPos, &vSize, 50, m_szDieMessage, m_tColor);

	m_tColor.a -= 1.f * fTimeDelta;
	if (m_tColor.a <= 0.f)
	{
		m_tColor.a = 0.f;
	}

}

void CMonsterBase::print_Hit(const Engine::_float& fTimeDelta)
{
	_vec4 vPos(*m_pTransform->Get_Info(INFO_POS), 1.f);

	make_PosToView(&vPos, 0.f, m_fHitHeight);

	m_fHitHeight += fTimeDelta * 10.f;

	_vec3 vScale(20.f, 20.f, 1.f);
	D3DXCOLOR tColor(1.f, 0.f, 1.f, 1.f);

	if (_wtoi(m_szHitDamage) > 20)
	{
		vScale = { 30.f, 30.f, 1.f };
		tColor = { 0.f, 1.f, 1.f, 1.f };
	}

	DLL::pFontMgr->Print_Font(&_vec3(vPos), &vScale, 15, m_szHitDamage, tColor);
}

void CMonsterBase::read_Data(void)
{
	_int iHP = static_cast<_int>(get_ReadData(L"HP"));

	HP_INFO tHP(iHP, iHP);
	MP_INFO tMP;

	_int iAtt = static_cast<_int>(get_ReadData(L"Att"));
	_int iArmor = static_cast<_int>(get_ReadData(L"Armor"));

	ATT_ARMOR_INFO tAttArmor(iAtt, iArmor);

	_float fRun = get_ReadData(L"Run");

	MOVE_INFO tMove(fRun, fRun);

	PERCENT_INFO tPercent;
	RESIST_INFO tResist;

	m_pStatCom->Set_TotalStat(UNIT_INFO(tHP, tMP, tAttArmor, tMove, tPercent, tResist));

	m_fMainColSize = get_ReadData(L"MainCol");

	_vec3 vScale;
	vScale.x = get_ReadData(L"ScaleX");
	vScale.y = get_ReadData(L"ScaleY");
	vScale.z = get_ReadData(L"ScaleZ");

	m_pTransform->Set_Scale(&vScale);

	m_iExp = static_cast<_int>(get_ReadData(L"Exp"));

	m_iMoney = static_cast<_int>(get_ReadData(L"Gold"));

	m_fDeadLifeTime = get_ReadData(L"DeadTime");
}

Engine::_float CMonsterBase::get_ReadData(const Engine::_tchar * pKey)
{
	const _int iMaxStr = 256;
	_tchar szValue[iMaxStr]{};
	GetPrivateProfileString(m_wStrName.c_str(), pKey, L"0.f", szValue, iMaxStr, L"../../Data/PrefabData/MonsterPrefab.ini");

	return static_cast<_float>(_wtof(szValue));
}

void CMonsterBase::mouse_Pick(void)
{
	if (m_pMainSphereCollider)
	{
		if (CollideFunc::SphereToMouse(m_pGraphicDev, DLL::pMouseMgr->Get_ViewspaceMouse(), m_pTransform->Get_Info(INFO_POS), m_pMainSphereCollider->Get_Radius()))
		{
			DLL::pMouseMgr->Set_MouseMode(MOUSE_ATTACK);
			if (DLL::pInputMgr->MouseDown(DIM_LB))
			{
				DLL::pMouseMgr->Set_PickTarget(this);
			}
		}
	}
}

Engine::_bool CMonsterBase::can_Act(const Engine::_tchar* pKey, Engine::CGameObject* pObj)
{
	_bool bCanAct = m_mapAction[pKey]->Can_Act() && CollideFunc::ActionColToPlayer(m_mapAction[pKey], pObj);

	if (bCanAct)
	{
		m_mapAction[pKey]->Reset_Act();
		m_mapActColType[pKey] = COL_TRUE;
	}

	return bCanAct;
}

void CMonsterBase::can_NextAct(const Engine::_float & fTimeDelta)
{
	m_fAfterAct += fTimeDelta;
	if (m_fAfterAct >= m_fBeginActTime)
	{
		m_fAfterAct = 0.f;
		m_bAfterAct = false;
	}
}

void CMonsterBase::set_ActTime(const Engine::_float & fAfterTime)
{
	m_bAfterAct = true;
	m_fBeginActTime = fAfterTime;
	m_fAfterAct = 0.f;
}

void CMonsterBase::move_ToPlayer(const _float& fTimeDelta)
{
	CTransform* pPlayerTransform = DLL::pObjMgr->Get_ObjList(L"Player")->front()->Get_Component<CTransform>(L"Transform", ID_DYNAMIC);

	_vec3 vDir = *pPlayerTransform->Get_Info(INFO_POS) - *m_pTransform->Get_Info(INFO_POS);
	D3DXVec3Normalize(&vDir, &vDir);

	vDir = vDir * m_pStatCom->Get_Move() *  fTimeDelta;

	m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &vDir));
}

void CMonsterBase::look_Target(Engine::CGameObject * pObj)
{
	m_pTransform->Compute_LookAtTarget(pObj->Get_Pos());
}
