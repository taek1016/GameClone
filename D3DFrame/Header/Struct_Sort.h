typedef	struct tagSortingNaviMesh
{
	D3DXVECTOR3 vMousePos;
	tagSortingNaviMesh(const D3DXVECTOR3& _vMousePos)
		: vMousePos(_vMousePos)
	{	}

	bool operator()(const D3DXVECTOR3& vPos1, const D3DXVECTOR3& vPos2)
	{
		float fDist1, fDist2;
		fDist1 = D3DXVec3Length(&(vMousePos - vPos1));
		fDist2 = D3DXVec3Length(&(vMousePos - vPos2));

		return fDist1 > fDist2;
	}

}NAVI_SORT;