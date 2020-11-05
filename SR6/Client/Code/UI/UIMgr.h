#ifndef UIMgr_h__
#define UIMgr_h__

#include "Engine_Defines.h"
#include "Base.h"
#include "UIBase.h"
class CHitBox;
class CUIMgr : public CBase
{
	DECLARE_SINGLETON(CUIMgr)

private:
	explicit								CUIMgr(void);
	virtual									~CUIMgr(void);

public:
	void									Initialize_UI(void);
	void									Register_UI(const Engine::_tchar* pKey, CUIBase* pUi);
	void									Set_Data(const Engine::_tchar* pKey, const Engine::_float& fData);
	void									Update_Ui(const Engine::_float& fTimeDelta);

	void									Activate_HitBox(void);
private:
	map<const Engine::_tchar*, CUIBase*>	m_mapUI;
	CHitBox*								m_pHitBox = nullptr;

	Engine::_bool							m_bActivateHit = false;
	Engine::_float							m_fCurTime;
	Engine::_float							m_fHitTime;

private:
	inline virtual void						freeMem() override;
};

#endif // UIMgr_h__
