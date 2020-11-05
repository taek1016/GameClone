#include "stdafx.h"
#include "MonsterController.h"

#include "SceneObject/MonsterBase.h"

USING(Engine)

CMonsterController::CMonsterController(void)
	: CController()
	, m_fSpeed(5.f)
	, m_fDetectLength(10.f)
	, m_fAttackLength(3.f)
{
}

CMonsterController::~CMonsterController(void)
{
}

HRESULT CMonsterController::Late_Initialize()
{
	m_pTransform = m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	m_pPlayer = DLL::pSearchMgr->Get_Object(L"Player");

	return S_OK;
}

HRESULT CMonsterController::Initialize_Component()
{
	return S_OK;
}

_int CMonsterController::Update_Component(const _float & fTimeDelta)
{
	Set_OnTerrain();
	Key_Input(fTimeDelta);

	return 0;
}

void CMonsterController::Check_Map(void)
{
	Engine::CTerrainTex*	pTerrainTex = DLL::pSearchMgr->Get_Object(L"Terrain")
		->Get_Component<CTerrainTex>(BODY, ID_STATIC);

}

void CMonsterController::Key_Input(const _float& fTimeDelta)
{
	CMonster* pGameObject = dynamic_cast<CMonster*>(m_pGameObject);

	pGameObject->SetPreStatus();
	pGameObject->SetCurStatus(OBJECT_STATUS::IDLE);

	_float	fMovePerFrame = m_fSpeed * fTimeDelta;
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
			DLL::pSoundMgr->PlaySound(L"ZombieAttack.wav", CSoundMgr::EFFECT);
			pGameObject->SetCurStatus(OBJECT_STATUS::ATTACK);
			m_fCurCool = 0.f;
			m_pPlayer->Take_Damage(m_pGameObject->Get_Damage());
		}
	}
	else if (fLength < m_fDetectLength)
	{
		static _float fDelta = 0.f;
		fDelta += fTimeDelta;
		if (fDelta >= 3.f)
		{
			fDelta = 0.f;
			DLL::pSoundMgr->PlaySound(L"ZombieIdle.mp3", CSoundMgr::EFFECT);
		}

		pGameObject->SetCurStatus(OBJECT_STATUS::MOVE);
		m_pTransform->Compute_LookAtTarget(&vPlayerPos);
		D3DXVec3Normalize(&vLength, &vLength);
		m_pTransform->Move_Pos(&(vLength * fMovePerFrame));
	}
}

void CMonsterController::Set_OnTerrain(void)
{
	_vec3		vPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTex = DLL::pSearchMgr->Get_Object(L"Terrain")
		->Get_Component<CTerrainTex>(BODY, ID_STATIC);

	_float	fHeight = Compute_HeightOnTerrain(&vPos, pTerrainTex->Get_Vtx(), pTerrainTex->Get_TotalVtxCnt());

	m_pTransform->Set_Pos(vPos.x, fHeight + 1.f, vPos.z);
}

Engine::_float CMonsterController::Compute_HeightOnTerrain(const Engine::_vec3* pPos, const Engine::BasicVertex* pVtx, const _ulong& dwTotalCnt)
{
	_ulong	dwCntX = static_cast<_ulong>(sqrt(dwTotalCnt));
	// 타일 ITV = 1.f
	_ulong	dwIndex = _ulong(pPos->z / 1.f) * dwCntX + _ulong(pPos->x / 1.f);

	_float	fRatioX = (pPos->x - pVtx[dwIndex + dwCntX].vPos.x) / 1.f;
	_float	fRatioZ = (pVtx[dwIndex + dwCntX].vPos.z - pPos->z) / 1.f;

	_float	fHeight[4] = {
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

CMonsterController * CMonsterController::Create(void)
{
	CMonsterController* pInstance = new CMonsterController();

	return pInstance;
}

CMonsterController * CMonsterController::Clone(void)
{
	return new CMonsterController(*this);
}

inline void CMonsterController::freeMem()
{
	CController::freeMem();
	m_pTransform = nullptr;
}
