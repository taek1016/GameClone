#ifndef NaviObject_h__
#define NaviObject_h__

#include "Engine_Defines.h"
#include "NaviMesh.h"

class CToolLine;
class CToolTerrainTex;
class CToolNaviCtrl;

class CToolNavi : public Engine::CNaviMesh
{
private:
	explicit				CToolNavi(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CToolNavi(void);

public:
	void					KeyInput(void);
	void					Set_Objects(Engine::CStaticMesh* pTex, CToolNaviCtrl* pNavi);
	HRESULT					Delete_Cell(const Engine::_ulong& dwIdx);

	const Engine::CCell*	Get_Cell(const Engine::_ulong& dwIdx);
	Engine::_ulong			Find_Index(const Engine::_vec3* pPos);
	Engine::CCell*			Get_MadeCell(void) const;
	Engine::_bool			Find_NearPos(Engine::_vec3* pOut, const Engine::_vec3* pIn);

	vector<Engine::CCell*>*	Get_Vec(void) { return &m_vecCell; }

	void					Move_Pos(const Engine::_vec3* pPos, const Engine::_vec3* pDir);
	void					Set_Pos(const Engine::_vec3* pPos, const Engine::_vec3* pDir);
private:
	Engine::_bool			collide_PointToMouse(const Engine::_vec3* pMouseViewspace, const Engine::_vec3* pTargetPos);
	void					pickUp_OnMesh(Engine::_vec3* pPos);
	Engine::_ulong			find_Index(const Engine::_vec3 * pStart, const Engine::_vec3 * pCenter, const Engine::_vec3 * pEnd);

	Engine::_vec3			m_vPos[3];
	Engine::_int			m_iCurCnt;

	Engine::CCell*			m_pCurMadeCell;

	CToolTerrainTex*		m_pTerrainTex;
	Engine::CStaticMesh*	m_pMesh;
	CToolNaviCtrl*			m_pNavi;
public:
	HRESULT					SaveNaviMesh(HANDLE hFile);
	HRESULT					LoadNaviMesh(HANDLE hFile);

	static CToolNavi*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
};

#endif // NaviObject_h__
