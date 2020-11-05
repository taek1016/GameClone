#include "stdafx.h"
#include "PickingMgr.h"
#include "SceneObject/PickableObject.h"

USING(Engine)

IMPLEMENT_SINGLETON(CPickingMgr)

CPickingMgr::CPickingMgr()
{
}

void CPickingMgr::freeMem()
{

}

CPickableObject* CPickingMgr::GetPickedObject(const Engine::_float & fTimeDelta, _float dist, _float* fOutDist)
{
	CPickableObject* retVal = nullptr;
	_vec3 vEye, vLook;
	vEye = *DLL::pCameraMgr->Get_Eye();
	vLook = *DLL::pCameraMgr->Get_At();
	float fMin = 99999;
	float fDistance = 0;
	auto iter = m_ltObjects.begin();
	while (iter != m_ltObjects.end())
	{
		if ((*iter)->IsPicked(vEye, vLook, dist, &fDistance))
		{
			if (fMin > fDistance)
			{
				fMin = fDistance;
				retVal = *iter;
			}
		}
		iter++;
	}
	*fOutDist = fMin;
	if (retVal == nullptr)
		*fOutDist = -1;
	return retVal;
}

void CPickingMgr::Delete_Object(const _tchar * name)
{
	auto iter = m_ltObjects.begin();
	while (iter != m_ltObjects.end())
	{
		if (wcscmp((*iter)->Get_Name(), name) == 0)
		{
			m_ltObjects.erase(iter);
			return;
		}
		iter++;
	}
}
