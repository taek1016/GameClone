#ifndef ToolNaviCtrl_h__
#define ToolNaviCtrl_h__

#include "Engine_Defines.h"
#include "Base.h"

class CToolTerrainTex;
class CToolNavi;
class CToolGuideAxis;

class CToolNaviCtrl : public CBase
{
private:
	explicit				CToolNaviCtrl(void);
	virtual					~CToolNaviCtrl(void);

public:
	Engine::_int			Update(const Engine::_float& fTimeDelta);
	void					KeyInput(void);
	void					Render(void);

	void					Initialize_Ctrl(CToolNavi* pObj, Engine::CStaticMesh* pBuffer);
	void					Activate(vector<Engine::CCell*>* vecCell);
	void					Add_Guide(Engine::_vec3* pPos);

	Engine::_bool			PickOnNavi(Engine::_vec3* pOut);
	CToolGuideAxis*			Get_ActivatedAxis(void);

private:
	Engine::_bool			check_ActiveGuideLine();
	void					clear_List(void);
	CToolNavi*				m_pNaviObj;

	list<CToolGuideAxis*>	m_listGuideLine;
	CToolGuideAxis*			m_pActivateGuideLine;

	vector<Engine::CCell*>* m_pVecCell;
	Engine::CStaticMesh*	m_pBuffer;

	Engine::_bool			m_bActivated;
	
	Engine::_bool			m_bAxisSelected;
	Engine::_vec3			m_vSelectPos;
	Engine::_vec3			m_vMeshPos;
	Engine::_ulong			m_dwStartPos;
	Engine::_ulong			m_dwSelectAxisNum;

public:
	static CToolNaviCtrl*	Create(void);
private:
	inline virtual void		Free(void);
};

#endif // ToolNaviCtrl_h__
