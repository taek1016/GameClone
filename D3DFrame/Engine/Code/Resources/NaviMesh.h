#ifndef NaviMesh_h__
#define NaviMesh_h__

#include "Mesh.h"
#include "Cell.h"

BEGIN(Engine)

class ENGINE_DLL CNaviMesh : public CMesh
{
protected:
	explicit				CNaviMesh(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CNaviMesh(const CNaviMesh& rhs);
	virtual					~CNaviMesh(void);

public:
	void					Set_Index(const _ulong& dwIndex) { m_dwIndex = dwIndex; }
	CCell*					Add_Cell(const _vec3* pStart, const _vec3* pCenter, const _vec3* pEnd);
	
	virtual void			Render_NaviMesh(void);
	_vec3					Move_OnNaviMesh(const _vec3* pTargetPos, const _vec3* pTargetDir);
	HRESULT					Link_Cell(void);
	const vector<CCell*>*	Get_Vec(void) const;

	_ulong					Get_Index(void) const { return m_dwIndex; }

protected:
	HRESULT					initialize_NaviMesh(void);

protected:
	vector<CCell*>			m_vecCell;
	_ulong					m_dwIndex;

public:
	static	CNaviMesh*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CResources*		Clone(void);
	virtual void			Free(void);
};

END
#endif // NaviMesh_h__
