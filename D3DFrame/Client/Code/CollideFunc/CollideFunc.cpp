#include "stdafx.h"
#include "CollideFunc.h"

#include "Sphere.h"
#include "UI/Button.h"

USING(Engine)

Engine::_bool CollideFunc::MainSphereCol(Engine::CGameObject * pFrom, Engine::CGameObject * pTo)
{
	_bool bCollide = false;

	CSphereCollider* pFromSphere = pFrom->Get_Component<CSphereCollider>(L"MainSphereCol", ID_STATIC);
	CSphereCollider* pToSphere = pTo->Get_Component<CSphereCollider>(L"MainSphereCol", ID_STATIC);

	_float fRadiusDistance = fabsf(*pFromSphere->Get_Radius() + *pToSphere->Get_Radius());
	_float fPosDistance = D3DXVec3Length(&(*pTo->Get_CenterPos() - *pFrom->Get_CenterPos()));

	if (fPosDistance < fRadiusDistance)
	{
		bCollide = true;
		CTransform* pFromTransform = pFrom->Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
		CTransform* pToTransform = pTo->Get_Component<CTransform>(L"Transform", ID_DYNAMIC);

		const _float fReverse = -1.f;
		_vec3 vFromDir = (*pToTransform->Get_Info(INFO_POS) - *pFromTransform->Get_Info(INFO_POS));
		D3DXVec3Normalize(&vFromDir, &vFromDir);

		pToTransform->Move_Pos(&(vFromDir * (fRadiusDistance - fPosDistance)));
	}

	return bCollide;
}

Engine::_bool CollideFunc::ActionColToPlayer(Engine::CSphereCollider * pSphere, Engine::CGameObject * pPlayer)
{
	Engine::_bool bCollided = false;

	CSphereCollider* pPlayerMainSphere = pPlayer->Get_Component<CSphereCollider>(L"MainSphereCol", ID_STATIC);

	const _float fRadiusSum = *pSphere->Get_Radius() + *pPlayerMainSphere->Get_Radius();

	const _float fPosDist = D3DXVec3Length(&(*pSphere->Get_CenterPos() - *pPlayerMainSphere->Get_CenterPos()));

	if (fPosDist < fRadiusSum)
	{
		bCollided = true;
	}

	return bCollided;
}

Engine::_bool CollideFunc::SphereToSphere(Engine::CSphereCollider * pFrom, Engine::CSphereCollider * pTo)
{
	Engine::_bool bCollided = false;

	const _float fRadiusSum = *pFrom->Get_Radius() + *pTo->Get_Radius();

	const _float fPosDist = D3DXVec3Length(&(*pFrom->Get_CenterPos() - *pTo->Get_CenterPos()));

	if (fPosDist < fRadiusSum)
	{
		bCollided = true;
	}

	return bCollided;
}

Engine::_bool CollideFunc::SphereToMouse(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pMouseViewspace, const Engine::_vec3* pTargetPos, const Engine::_float* pRadius)
{
	_bool bCollide = false;

	_vec3 vRayPos, vRayDir;
	vRayPos = { 0.f, 0.f, 0.f };
	vRayDir = *pMouseViewspace - vRayPos;

	_matrix matView;
	pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, nullptr, &matView);
	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matView);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matView);

	D3DXVec3Normalize(&vRayDir, &vRayDir);

	_float fDistance = D3DXVec3Length(&(*pTargetPos - vRayPos));

	_vec3 vFinalPos = vRayPos + vRayDir * fDistance;

	_float fFinalToSphereLength = fabsf(D3DXVec3Length(&(vFinalPos - *pTargetPos)));

	if (fFinalToSphereLength < *pRadius)
	{
		bCollide = true;
	}

	return bCollide;
}

Engine::_bool CollideFunc::MouseToRect(MY_RECT* pRect, const Engine::_vec2* pPos)
{
	if ((pRect->fLeft <= pPos->x && pPos->x <= pRect->fRight) &&
		(pRect->fTop >= pPos->y && pPos->y >= pRect->fBottom))
	{
		return true;
	}

	return false;
}
