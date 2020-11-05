#include "stdafx.h"
#include "Player.h"

#include "Skill/Player/FrostBolt.h"
#include "Skill/Player/FrostNova.h"

#include "Effect/Particle/RedBloodParticle.h"

#include "Character/VehicleBase.h"
#include "Effect/LevelUpEffect.h"

USING(Engine)

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCharacterBase(pGraphicDev)
	, m_bHit(false)
	, m_bSkillUsing(false)
	, m_bRide(false)
	, m_bUnBeatable(false)
	, m_pVehicle(nullptr)
	, m_fLevelUpTime(0.f)
	, m_fCurDeadTime(0.f)
	, m_fDeadLifeTime(0.f)
	, m_fUnBeatableActivateTime(0.f)
	, m_tItemInfo()
	, m_bLevelUp(false)
	, m_bStun(false)
	, m_bFirstUpdate(false)
{
	set_Name(L"BloodElf");
}

CPlayer::CPlayer(const CPlayer& rhs)
	: CCharacterBase(rhs)
	, m_bHit(false)
	, m_bSkillUsing(false)
	, m_bRide(false)
	, m_bStun(false)
	, m_bUnBeatable(false)
	, m_fUnBeatableActivateTime(0.f)
	, m_pVehicle(nullptr)
	, m_fLevelUpTime(0.f)
	, m_fCurDeadTime(0.f)
	, m_fDeadLifeTime(rhs.m_fDeadLifeTime)
	, m_tItemInfo()
	, m_bLevelUp(false)
	, m_bFirstUpdate(false)
{
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::read_Data(void)
{
	CCharacterBase::read_Data();

	m_fDeadLifeTime = get_ReadData(L"DeadTime");
}

void CPlayer::print_Unbeatable(const Engine::_float & fTimeDelta)
{
	m_fUnBeatableActivateTime += fTimeDelta;
	if (m_fUnBeatableActivateTime >= 5.f)
	{
		return;
	}

	const _tchar* pText = L"무적상태";
	_vec3 vPos, vScale(15.f, 20.f, 1.f);

	_int iLen = lstrlen(pText);
	vPos = *m_pTransform->Get_Info(INFO_POS);

	_matrix matView, matProj;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	D3DXVec3TransformCoord(&vPos, &vPos, &matView);
	D3DXVec3TransformCoord(&vPos, &vPos, &matProj);

	D3DVIEWPORT9 tView;
	m_pGraphicDev->GetViewport(&tView);

	vPos.x = vPos.x * tView.Width * 0.5f;
	vPos.y = -vPos.y * tView.Height * 0.5f;

	vPos.x -= vScale.x * iLen * 0.5f;
	vPos.y += 80.f + fTimeDelta * 200.f;
	vPos.z = 0.f;

	DLL::pFontMgr->Print_Font(&vPos, &vScale, iLen, pText, D3DXCOLOR(1.f, 1.f, 0.f, 1.f));
}

void CPlayer::print_LevelUp(const _float& fTimeDelta)
{
	if (m_bLevelUp)
	{
		m_fLevelUpTime += fTimeDelta;
		if (m_fLevelUpTime >= m_fLevelUpDeadTime)
		{
			m_bLevelUp = false;
			return;
		}

		const _tchar* pText = L"레벨업";
		_vec3 vPos, vScale(15.f, 20.f, 1.f);

		_int iLen = lstrlen(pText);
		vPos = *m_pTransform->Get_Info(INFO_POS);

		_matrix matView, matProj;
		m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
		m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

		D3DXVec3TransformCoord(&vPos, &vPos, &matView);
		D3DXVec3TransformCoord(&vPos, &vPos, &matProj);

		D3DVIEWPORT9 tView;
		m_pGraphicDev->GetViewport(&tView);

		vPos.x = vPos.x * tView.Width * 0.5f;
		vPos.y = -vPos.y * tView.Height * 0.5f;

		vPos.x -= vScale.x * iLen * 0.5f;
		vPos.y += 80.f;
		vPos.z = 0.f;

		DLL::pFontMgr->Print_Font(&vPos, &vScale, iLen, pText, D3DXCOLOR(1.f, 1.f, 0.f, 1.f));
	}
}

void CPlayer::print_Name(void)
{
	_vec4 vPos(*m_pTransform->Get_Info(INFO_POS), 1.f);

	_vec3 vScale(30.f, 20.f, 1.f);
	make_PosToView(&vPos, vScale.x * 2.f, m_fHeight);

	DLL::pFontMgr->Print_Font(&_vec3(vPos), &vScale, 20, L"플레이어", D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
}

HRESULT CPlayer::Initialize_GameObject()
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);

	CStatCom::Create()->Attach(L"Stat", this, ID_STATIC);

	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"MeshShader", this, ID_STATIC);

	initialize_Animation();

	return S_OK;
}

HRESULT CPlayer::Late_Initialize()
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	const _float fSize = 5.f;
	m_pTransform->Set_Scale(&_vec3(fSize, fSize, fSize));
	m_pMesh = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);

	m_pStatCom = Get_Component<CStatCom>(L"Stat", ID_STATIC);

	m_pShaderCom = Get_Component<CShader>(L"MeshShader", ID_STATIC);

	CCharacterBase::Late_Initialize();

	return S_OK;
}

Engine::_int CPlayer::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (m_bUnBeatable)
	{
		print_Unbeatable(fTimeDelta);
	}

	if (m_pStatCom->Get_Dead())
	{
		m_fCurDeadTime += fTimeDelta;

		Set_AnimationSet(L"Death");
		play_Animation();

		if (false == m_pMesh->Is_AnimationSetEnd())
		{
			m_pMesh->Play_Animation(fTimeDelta);
		}
		else if (m_fCurDeadTime >= m_fDeadLifeTime + 3.f)
		{
			m_pStatCom->Revive();
			m_fCurDeadTime = 0.f;
			m_dwNaviIdx = DLL::pPickMgr->Get_Index(&(m_vFirstPlacePos + _vec3(0.f, 1.f, 0.f)));
			m_pTransform->Set_Info(INFO_POS, &m_vFirstPlacePos);
		}
		
		DLL::pRenderer->Add_RenderGroup(RENDER_NONALPHA, this);
		return 0;
	}
	set_PreAnimationKey();

	if (false == m_bFirstUpdate)
	{
		m_bFirstUpdate = true;
		m_vFirstPlacePos = *m_pTransform->Get_Info(INFO_POS);
	}

	print_LevelUp(fTimeDelta);

	key_Input(fTimeDelta);
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	play_Animation();
	m_pMesh->Play_Animation(fTimeDelta);

	for (auto iter : m_vecItemEquip)
	{
		if (nullptr != iter->pItem)
		{
			iter->pItem->Update_GameObject(fTimeDelta);
		}
	}

	if (m_bRide)
	{
		m_pVehicle->Update_GameObject(fTimeDelta);
	}

	DLL::pCameraMgr->Update_Camera(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_NONALPHA, this);

	return iExit;
}

void CPlayer::Render_GameObject(void)
{
	CCharacterBase::Render_GameObject();
}

const _vec3 CPlayer::Get_SkillHandPosition(const Engine::_bool bHandMatrixUse)
{
	_matrix matFrameWorld;
	if (true == bHandMatrixUse)
	{
		matFrameWorld = m_pMesh->Get_FrameByName("bloodelfmale_Bone59_LFingerIndex")->CombinedTransformationMatrix * *m_pTransform->Get_World();
	}
	else
	{
		matFrameWorld = *m_pTransform->Get_World();
	}

	_vec3 vPos;
	memcpy(&vPos, matFrameWorld.m[3], sizeof(_vec3));

	return vPos;
}

Engine::_float CPlayer::Get_HPPercent(void) const
{
	return m_pStatCom->Get_HPPercent();
}

void CPlayer::Change_Items(const EQUIP_ENUM eEquip, const Engine::_tchar * pKey)
{
	UNIT_INFO tDefaultStaffInfo(HP_INFO(), MP_INFO(50, 50), ATT_ARMOR_INFO(10, 0),
		MOVE_INFO(), PERCENT_INFO(), RESIST_INFO());
	UNIT_INFO tFinalStaffInfo(HP_INFO(), MP_INFO(100, 100), ATT_ARMOR_INFO(20, 0),
		MOVE_INFO(), PERCENT_INFO(), RESIST_INFO());

	if (nullptr != m_vecItemEquip[eEquip]->pItem)
	{
		auto pItemName = m_vecItemEquip[eEquip]->pItem->Get_Name();
		if (0 == wcscmp(pItemName, L"DefaultStaff"))
		{
			m_tItemInfo = m_tItemInfo - tDefaultStaffInfo;
		}
		else if (0 == wcscmp(pItemName, L"FinalStaff"))
		{
			m_tItemInfo = m_tItemInfo - tFinalStaffInfo;
		}
		m_pStatCom->Set_Item(m_tItemInfo);
		Safe_Release(m_vecItemEquip[eEquip]->pItem);
		m_vecItemEquip[eEquip]->pItem = nullptr;
	}

	CItemBase* pItem = DLL::pItemMgr->Clone_Item(pKey);

	if (nullptr == pItem)
	{
		TakeOff_Item(eEquip);
		return;
	}

	auto pItemName = pItem->Get_Name();
	if (0 == wcscmp(pItemName, L"DefaultStaff"))
	{
		m_tItemInfo = m_tItemInfo + tDefaultStaffInfo;
	}
	else if (0 == wcscmp(pItemName, L"FinalStaff"))
	{
		m_tItemInfo = m_tItemInfo + tFinalStaffInfo;
	}

	pItem->Set_ColliderMat(m_vecItemEquip[eEquip]->pMatWorld, m_vecItemEquip[eEquip]->pMatBone);
	m_vecItemEquip[eEquip]->pItem = pItem;

	m_pStatCom->Set_Item(m_tItemInfo);
}

void CPlayer::Change_Body(const Engine::_tchar * pKey)
{
	const _int iMaxStr = 256;
	_tchar szMeshName[iMaxStr]{};

	lstrcpy(szMeshName, m_wStrName.c_str());
	lstrcat(szMeshName, pKey);

	UNIT_INFO tBlueClothInfo(HP_INFO(50, 50), MP_INFO(), ATT_ARMOR_INFO(0, 3),
		MOVE_INFO(), PERCENT_INFO(), RESIST_INFO());
	UNIT_INFO tMetalPlateInfo(HP_INFO(100, 100), MP_INFO(), ATT_ARMOR_INFO(0, 6),
		MOVE_INFO(), PERCENT_INFO(), RESIST_INFO());

	if (L"BlueCloth" == m_wStrBodyName)
	{
		m_tItemInfo = m_tItemInfo - tBlueClothInfo;
	}
	else if (L"MetalPlate" == m_wStrBodyName)
	{
		m_tItemInfo = m_tItemInfo - tMetalPlateInfo;
	}

	m_pStatCom->Set_Item(m_tItemInfo);

	CDynamicMesh* pMesh = DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, szMeshName);

	if (nullptr == pMesh)
	{
		m_wStrBodyName.clear();
		return;
	}

	m_wStrBodyName = pKey;

	if (L"BlueCloth" == m_wStrBodyName)
	{
		m_tItemInfo = m_tItemInfo + tBlueClothInfo;
	}
	else if (L"MetalPlate" == m_wStrBodyName)
	{
		m_tItemInfo = m_tItemInfo + tMetalPlateInfo;
	}

	m_pStatCom->Set_Item(m_tItemInfo);

	auto iter = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);
	Safe_Release(iter);
	m_pMesh = pMesh;

	m_pMesh->Attach(L"Mesh", this, ID_STATIC);

	initialize_Animation();
	m_iPreAnimationIdx = 999;

	Set_AnimationSet(L"Stand");
	play_Animation();
}

void CPlayer::TakeOff_Item(const EQUIP_ENUM eEquip)
{
	if (nullptr != m_vecItemEquip[eEquip]->pItem)
	{
		Safe_Release(m_vecItemEquip[eEquip]->pItem);
		m_vecItemEquip[eEquip]->pItem = nullptr;
	}
}

void CPlayer::Stun(void)
{
	if (m_bUnBeatable)
	{
		return;
	}

	m_bStun = true;
	m_fStunTime = 0.f;

	DLL::pEffectMgr->Get_Effect(L"Stun", m_pTransform->Get_Info(INFO_POS));
}

void CPlayer::Hit(const Engine::_int & iDamage)
{
	if (m_bUnBeatable || m_pStatCom->Get_Dead())
	{
		return;
	}

	::ZeroMemory(m_szHitDamage, sizeof(_tchar) * 64);
	_int iDamageResult = iDamage - static_cast<_int>(m_pStatCom->Get_Armor() * 0.5f) < 0 ? 1 : iDamage - static_cast<_int>(m_pStatCom->Get_Armor() * 0.5f);

	m_pStatCom->Hit(iDamageResult);

	wsprintf(m_szHitDamage, L"%d", iDamageResult);
	Set_AnimationSet(L"Hit");

	m_pMesh->Set_AnimationSet(m_iCurAnimationIdx);
	m_bHit = true;

	for (_int i = 0; i < 5; ++i)
	{
		CRedBloodParticle* pParticle = CRedBloodParticle::Create(m_pGraphicDev);
		_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
		vPos.y += 5.f;
		pParticle->Set_Pos(&vPos);
		_vec3 vRight = *m_pTransform->Get_Info(INFO_RIGHT) * -1.f;
		vRight.z -= 1.f * i;
		pParticle->Set_Dir(&vRight);
		DLL::pObjMgr->Add_GameObject(L"Effect", pParticle);
	}
}

Engine::_bool CPlayer::Is_AnimationEnd(void) const
{
	return m_bSkillUsing;
}

void CPlayer::Play_AnimationForce(const Engine::_tchar * pKey)
{
	Set_AnimationSet(pKey);
	m_pMesh->Set_AnimationSet(m_iCurAnimationIdx);
}

void CPlayer::Ride_Target(CVehicleBase* pVehicle)
{
	m_bRide = true;
	m_pVehicle = pVehicle;
	m_pVehicle->Ride_Vehicle(this);
}

void CPlayer::DisEmbark(void)
{
	m_bRide = false;
	if (nullptr != m_pVehicle)
	{
		m_pVehicle->DisEmbark();
		m_pVehicle = nullptr;
	}

	m_dwNaviIdx = DLL::pPickMgr->Get_Index(m_pTransform->Get_Info(INFO_POS));
	m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), m_pTransform->Get_Info(INFO_LOOK)));
	//m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, &(*m_pTransform->Get_Info(INFO_POS) + _vec3(0.f, 1.f, 0.f)), &_vec3(0.f, 0.f, 0.f)));
}

void CPlayer::Get_Exp(const Engine::_int & iExp)
{
	if (m_pStatCom->Get_Exp(iExp))
	{
		DLL::pSoundMgr->PlaySound(L"LevelUp.wav", CSoundMgr::EFFECT);
		DLL::pSoundMgr->SetVolume(CSoundMgr::EFFECT, 0.3f);

		// 레벨 업 이펙트
		m_bLevelUp = true;
		m_fLevelUpTime = 0.f;
		CLevelUpEffect* pEffect = dynamic_cast<CLevelUpEffect*>(DLL::pEffectMgr->Get_Effect(L"LevelUp", m_pTransform->Get_Info(INFO_POS)));
	}
}

Engine::_bool CPlayer::Has_EnoughMana(const Engine::_float & fMana)
{
	if (m_pStatCom->Get_MP().iMP >= fMana)
	{
		m_pStatCom->Use_Mana(fMana);
		return true;
	}

	return false;
}

const Engine::_int& CPlayer::Get_Damage(void) const
{
	return m_pStatCom->Get_Att();
}


Engine::_bool CPlayer::attack_Act(void)
{
	return false;
}

void CPlayer::get_CameraRight(Engine::_vec3 * pRight)
{
	_matrix matViewToWorld;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matViewToWorld);
	D3DXMatrixInverse(&matViewToWorld, nullptr, &matViewToWorld);
	memcpy(pRight, matViewToWorld.m[0], sizeof(_vec3));
	D3DXVec3Normalize(pRight, pRight);
}

void CPlayer::make_VectorReady(void)
{
	const _matrix* pBone = nullptr;
	const _matrix* pWorld = m_pTransform->Get_World();

	m_vecItemEquip.resize(ITEM_END);

	// 머리, 어깨, 가슴, 무기, 신발
	const char* pBoneName[ITEM_END] = { "", "", "", "bloodelfmale_Bone66_RFingerIndex", "" };
	for (_int i = 0; i < ITEM_END; ++i)
	{
		m_vecItemEquip[i] = new ITEM_INFO;
		if (0 != strlen(pBoneName[i]))
		{
			m_vecItemEquip[i]->pMatBone = &m_pMesh->Get_FrameByName(pBoneName[i])->CombinedTransformationMatrix;
		}
		m_vecItemEquip[i]->pMatWorld = pWorld;
	}
}

void CPlayer::key_Input(const Engine::_float & fTimeDelta)
{
	if (DLL::pInputMgr->KeyDown(DIK_P))
	{
		DisEmbark();
	}

	if (DLL::pInputMgr->KeyDown(DIK_I))
	{
		_vec3 vPos = *m_pTransform->Get_Info(INFO_POS) + *m_pTransform->Get_Info(INFO_LOOK);
		m_dwNaviIdx = DLL::pPickMgr->Get_Index(&(vPos + _vec3(0.f, 1.f, 0.f)));
		m_pTransform->Set_Info(INFO_POS, &vPos);
	}

	if (DLL::pInputMgr->KeyDown(DIK_T))
	{
		m_bUnBeatable = true;
	}

	if (m_bStun)
	{
		m_fStunTime += fTimeDelta;
		Set_AnimationSet(L"Stun");

		if (m_fStunTime >= 3.f)
		{
			m_bStun = false;
		}
		else
		{
			return;
		}
	}
	else if (m_bHit)
	{
		_vec3 vPos(20.f, 40.f, 0.f);

		_vec3 vScale;
		D3DXCOLOR tColor;

		if (_wtoi(m_szHitDamage) > 20)
		{
			vScale = { 30.f, 30.f, 1.f };
			tColor = D3DXCOLOR(1.f, 1.f, 0.f, 1.f);
		}
		else
		{
			vScale = { 20.f, 20.f, 1.f };
			tColor = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
		}

		DLL::pFontMgr->Print_Font(&vPos, &vScale, 15, m_szHitDamage, tColor);

		if (m_pMesh->Is_AnimationSetEnd())
		{
			m_bHit = false;
		}
		return;
	}
	else if (m_bRide)
	{
		Set_AnimationSet(L"Mount");
		return;
	}
	else if (DLL::pSkillMgr->Is_ShotSkill() && m_bSkillUsing)
	{
		if (m_pMesh->Is_AnimationSetEnd())
		{
			m_bSkillUsing = false;
		}
		return;
	}
	else if (DLL::pSkillMgr->Is_SkillUsing())
	{
		m_bSkillUsing = true;
		auto pSkill = DLL::pSkillMgr->Get_CurrentSkillInfo();
		Set_AnimationSet(pSkill->wStrReadyAnimationKey.c_str());
		return;
	}

	Set_AnimationSet(L"Stand");

	if (DLL::pInputMgr->KeyDown(DIK_R))
	{
		m_pStatCom->Set_Run(!m_pStatCom->Get_Run());
	}

	if (DLL::pInputMgr->KeyPressing(DIK_A))
	{
		const _float fDeltaRot = -D3DXToRadian(180.f) * fTimeDelta;
		m_pTransform->Rotation(ROT_Y, fDeltaRot);
		Set_AnimationSet(L"ShuffleLeft");
	}
	else if (DLL::pInputMgr->KeyPressing(DIK_D))
	{
		const _float fDeltaRot = D3DXToRadian(180.f) * fTimeDelta;
		m_pTransform->Rotation(ROT_Y, fDeltaRot);
		Set_AnimationSet(L"ShuffleRight");
	}

	if (DLL::pInputMgr->KeyPressing(DIK_W))
	{
		_vec3 vDir = *m_pTransform->Get_Info(INFO::INFO_LOOK);
		D3DXVec3Normalize(&vDir, &vDir);

		vDir = (vDir * m_pStatCom->Get_Move()) * fTimeDelta;

		m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &vDir));
		set_MoveAnimation();
	}
	else if (DLL::pInputMgr->KeyPressing(DIK_S))
	{
		const _float fReverse = -1.f;
		_vec3 vDir = *m_pTransform->Get_Info(INFO::INFO_LOOK) * fReverse;
		D3DXVec3Normalize(&vDir, &vDir);

		m_pStatCom->Set_Run(false);
		vDir = (vDir * m_pStatCom->Get_Move()) * fTimeDelta;

		m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &vDir));

		Set_AnimationSet(L"WalkBack");
	}

	if (DLL::pInputMgr->KeyPressing(DIK_Q))
	{
		const _float fReverse = -1.f;
		_vec3 vLeft;
		get_CameraRight(&vLeft);
		vLeft *= fReverse * m_pStatCom->Get_Move() * fTimeDelta;
		m_pTransform->Compute_LookAtTarget(&(*m_pTransform->Get_Info(INFO_POS) + vLeft));

		m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &vLeft));
		set_MoveAnimation();
	}
	else if (DLL::pInputMgr->KeyPressing(DIK_E))
	{
		_vec3 vRight;
		get_CameraRight(&vRight);
		vRight *= m_pStatCom->Get_Move() * fTimeDelta;
		m_pTransform->Compute_LookAtTarget(&(*m_pTransform->Get_Info(INFO_POS) + vRight));

		m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &vRight));
		set_MoveAnimation();
	}

	if (DLL::pInputMgr->KeyDown(DIK_F11))
	{
		_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
		_vec3 vDir = *m_pTransform->Get_Info(INFO_LOOK);
		D3DXVec3Normalize(&vDir, &vDir);

		vPos += vDir * 10.f;
		vPos.y += 1.f;
		DLL::pDataMgr->Clone_CharacterObj(L"Supporter", L"WaterElemental", &vPos);
	}
}

CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer* pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->make_VectorReady();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CPlayer::Clone(void)
{
	CPlayer* pInstance = new CPlayer(*this);

	pInstance->Late_Initialize();
	pInstance->make_VectorReady();
	pInstance->Add_MainCollider(pInstance->m_fMainColSize);

	return pInstance;
}

inline void CPlayer::Free(void)
{
	CCharacterBase::Free();

	for (auto iter : m_vecItemEquip)
	{
		Safe_Release(iter->pItem);
		Safe_Delete(iter);
	}
	m_vecItemEquip.clear();
}
