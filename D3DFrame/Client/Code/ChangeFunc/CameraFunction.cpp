#include "stdafx.h"
#include "CameraFunction.h"

USING(Engine)

Engine::_matrix CameraFunc::Make_BillBoard(LPDIRECT3DDEVICE9 & pGraphicDev, Engine::CTransform * pTransform)
{
	_matrix matView;
	pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	memset(matView.m[3], 0, sizeof(_vec3));
	D3DXMatrixInverse(&matView, NULL, &matView);

	_vec3 vPos = *pTransform->Get_Info(INFO_POS);
	_vec3 vScale = *pTransform->Get_Scale();

	memcpy(matView.m[3], &vPos, sizeof(_vec3));

	for (_int i = 0; i < 3; ++i)
	{
		for (_int j = 0; j < 4; ++j)
		{
			matView.m[i][j] *= vScale[i];
		}
	}

	return matView;
}
