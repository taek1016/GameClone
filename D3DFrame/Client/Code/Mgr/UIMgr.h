#ifndef UIMgr_h__
#define UIMgr_h__

#include "Base.h"

class CUIBase;

class CUIMgr : public CBase
{
	DECLARE_SINGLETON(CUIMgr)

private:
	explicit				CUIMgr(void);
	virtual					~CUIMgr(void);

public:
	void					Update_UI(const Engine::_float& fTimeDelta);
	void					Add_UI(const Engine::_tchar* pName, CUIBase* pUI);

	void					Set_Target(const Engine::_tchar* pName, Engine::CGameObject* pObj);

	void					Set_Act(void);

private:
	Engine::_bool			m_bUIAct;
	map<wstring, CUIBase*>	m_mapUI;

private:
	inline virtual void		Free(void) override;
};

#endif // UIMgr_h__
