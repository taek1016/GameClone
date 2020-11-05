#include "stdafx.h"
#include "BossController.h"
#include "Effect/Fragment.h"
#include "SceneObject/MonsterBase.h"
#include "Effect/Vomit.h"
#include "SceneObject/Player.h"
USING(Engine)

CBossController::CBossController(void)
	: CController()
	, m_fSpeed(5.f)
	, m_fDetectLength(100.f)
	, m_fAttackLength(3.f)
{
}

CBossController::~CBossController(void)
{
}

HRESULT CBossController::Late_Initialize()
{
	m_pTransform = m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	m_pPlayer = DLL::pSearchMgr->Get_Object(L"Player");

	return S_OK;
}

HRESULT CBossController::Initialize_Component()
{
	return S_OK;
}

float offset = 0;
float ShakePower = 20;

_int CBossController::Update_Component(const _float & fTimeDelta)
{
	if (m_bJump)
	{
		m_pTransform->Move_Pos(&(_vec3(0, 7 - m_fJumpOffset, 0) * fTimeDelta));
		m_fJumpOffset += (5 + (offset += 0.2)) * fTimeDelta;
	}

	if (m_bLanded)
	{
		m_fCurCool += fTimeDelta;
		if (m_fCurCool > m_fAttackCool)
		{
			CVomit* vomit = DLL::pPoolMgr->Get_Pool<CVomit>(POOL_VOMIT);
			DLL::pObjMgr->Add_GameObject(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_PARTICLE, vomit);
			CTransform* transform = m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
			_vec3 vPos = *transform->Get_Info(INFO_POS);
			vomit->SetEmitPoint(_vec3(vPos.x, vPos.y, (transform->Get_Info(INFO_POS)->z)));
			vomit->Reset_AllParticles();
			m_bNowAttacking = true;
			m_fCurCool = 0;
		}
	}
	if (m_bNowAttacking)
	{
		CBody* body = m_pGameObject->Get_Component<CBody>(BODY, ID_DYNAMIC);
		body->PlayArmAnimation(L"Voming");
		body->PlayLegAnimation(L"Idle");
		m_fNowAttackingTime += fTimeDelta;
		if (m_fNowAttackingTime > 4)
		{
			m_bNowAttacking = false;
			m_fNowAttackingTime = 0;
		}
	}
	else if (m_bJump)
	{
		CBody* body = m_pGameObject->Get_Component<CBody>(BODY, ID_DYNAMIC);
		body->PlayArmAnimation(L"Jumping");
		body->PlayLegAnimation(L"Jumping");

	}
	else
	{
		CBody* body = m_pGameObject->Get_Component<CBody>(BODY, ID_DYNAMIC);
		body->PlayAnimation(L"Move");
	}

	Set_OnTerrain();
	if (!m_bNowAttacking)
		Key_Input(fTimeDelta);



	if (m_bShaking)
	{
		m_fShakeTime += fTimeDelta;
		if (m_fShakeTime > 2)
		{
			m_bShaking = false;
			m_fShakeOffset = 0;
			ShakePower = 10;
			m_fShakeTime = 0;
		}
		DLL::pCameraMgr->Shake_Camera(ShakePower);
		ShakePower -= (m_fShakeOffset += 0.1f);
	}

	return 0;
}

void CBossController::Jump()
{
	m_bJump = true;
	m_bLanded = false;
	offset = 0;
}

void CBossController::LandAttack()
{
	CGameObject* terrain = DLL::pSearchMgr->Get_Object(L"Terrain");
	CTerrainTex* terrainTex = terrain->Get_Component<CTerrainTex>(BODY, ID_STATIC);
	terrainTex->StartQuake(*m_pTransform->Get_Info(INFO_POS), 8.f);

	CFragment* particle = dynamic_cast<CFragment*>(DLL::pPoolMgr->Get_Pool<CFragment>(POOL_FRAGMENT));
	DLL::pObjMgr->Add_GameObject(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_PARTICLE, particle);

	particle->SetEmitPoint(*m_pTransform->Get_Info(INFO_POS));
	particle->Reset_AllParticles();
	m_bLanded = true;
	m_bShaking = true;

	_vec3 vPlayerPos = *m_pPlayer->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS);
	_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);

	if (D3DXVec3Length(&(vPlayerPos - vPos)) < 7)
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->AirBorne();
		m_pPlayer->Take_Damage(m_pGameObject->Get_Damage());
	}
}

void CBossController::Check_Map(void)
{
	Engine::CTerrainTex*   pTerrainTex = DLL::pSearchMgr->Get_Object(L"Terrain")
		->Get_Component<CTerrainTex>(BODY, ID_STATIC);

}

void CBossController::Key_Input(const _float& fTimeDelta)
{
	CMonster* pGameObject = dynamic_cast<CMonster*>(m_pGameObject);

	pGameObject->SetPreStatus();
	pGameObject->SetCurStatus(OBJECT_STATUS::IDLE);

	_float   fMovePerFrame = m_fSpeed * fTimeDelta;
	m_fCurCool += fTimeDelta;
	// 이동
	const _vec3 vPlayerPos = *DLL::pSearchMgr->Get_Pos(L"Player");
	const _vec3 vMyPos = *m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS);

	_vec3 vLength = vPlayerPos - vMyPos;
	const _float fLength = D3DXVec3Length(&vLength);

	if (fLength < m_fAttackLength)
	{
		if (m_fCurCool >= m_fAttackCool)
		{
			pGameObject->SetCurStatus(OBJECT_STATUS::ATTACK);
			m_fCurCool = 0.f;
			m_pPlayer->Take_Damage(m_pGameObject->Get_Damage());
		}
	}
	else if (fLength < m_fDetectLength)
	{
		pGameObject->SetCurStatus(OBJECT_STATUS::MOVE);
		m_pTransform->Compute_LookAtTarget(&vPlayerPos);
		D3DXVec3Normalize(&vLength, &vLength);
		m_pTransform->Move_Pos(&(vLength * fMovePerFrame));

		_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
		_vec3 vDir = *m_pPlayer->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS);
		_vec3 vLook = *m_pTransform->Get_Info(INFO_LOOK);
		D3DXVec3Normalize(&vDir, &(vDir - vPos));
		_float angle = D3DXVec3Dot(&vLook, &vDir);

		angle = acos(angle);
		if (vDir.x < 0)
			angle = -angle;
		if (abs(D3DXToDegree(angle)) >= 5)
			m_pTransform->Set_Angle(ROT_Y, angle);
	}
}

void CBossController::Set_OnTerrain(void)
{
	_vec3      vPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vPos);

	Engine::CTerrainTex*   pTerrainTex = DLL::pSearchMgr->Get_Object(L"Terrain")
		->Get_Component<CTerrainTex>(BODY, ID_STATIC);

	_float   fHeight = Compute_HeightOnTerrain(&vPos, pTerrainTex->Get_Vtx(), pTerrainTex->Get_TotalVtxCnt());

	if (m_bJump)
	{
		if (vPos.y <= fHeight)
		{
			m_bJump = false;
			m_fJumpOffset = 0;
			m_pTransform->Set_Pos(vPos.x, fHeight + 1.f, vPos.z);
			LandAttack();
		}
	}
	else
	{
		m_pTransform->Set_Pos(vPos.x, fHeight + 1.f, vPos.z);
	}

}

Engine::_float CBossController::Compute_HeightOnTerrain(const Engine::_vec3* pPos, const Engine::BasicVertex* pVtx, const _ulong& dwTotalCnt)
{
	_ulong   dwCntX = static_cast<_ulong>(sqrt(dwTotalCnt));
	// 타일 ITV = 1.f
	_ulong   dwIndex = _ulong(pPos->z / 1.f) * dwCntX + _ulong(pPos->x / 1.f);

	_float   fRatioX = (pPos->x - pVtx[dwIndex + dwCntX].vPos.x) / 1.f;
	_float   fRatioZ = (pVtx[dwIndex + dwCntX].vPos.z - pPos->z) / 1.f;

	_float   fHeight[4] = {
		pVtx[dwIndex + dwCntX].vPos.y,
		pVtx[dwIndex + dwCntX + 1].vPos.y,
		pVtx[dwIndex + 1].vPos.y,
		pVtx[dwIndex].vPos.y
	};

	// 오른쪽 위 평면
	if (fRatioX > fRatioZ)
	{
		return fHeight[0] + (fHeight[1] - fHeight[0]) * fRatioX + (fHeight[2] - fHeight[1]) * fRatioZ;
	}
	// 왼쪽 아래 평면
	else
	{
		return fHeight[0] + (fHeight[2] - fHeight[3]) * fRatioX + (fHeight[3] - fHeight[0]) * fRatioZ;
	}
}

CBossController * CBossController::Create(void)
{
	CBossController* pInstance = new CBossController();

	return pInstance;
}

CBossController * CBossController::Clone(void)
{
	return new CBossController(*this);
}

inline void CBossController::freeMem()
{
	CController::freeMem();
	m_pTransform = nullptr;
}