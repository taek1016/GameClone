#ifndef QuestBase_h__
#define QuestBase_h__

#include "Base.h"

class CQuestBase : public CBase
{
protected:
	explicit				CQuestBase(void);
	virtual					~CQuestBase(void) = default;

public:
	virtual void			Update_Quest(void) PURE;

	void					Set_QuestCount(const Engine::_int& iCount);
	void					Activate_Quest(void);

	Engine::_bool			Get_Activated(void) const;
	Engine::_bool			Get_Finished(void) const;
	
	Engine::_int			Get_QuestNum(void) const;

	const Engine::_tchar*	Get_TargetName(void) const;

protected:
	Engine::_bool			m_bActivated;
	Engine::_bool			m_bFinished;
	
	Engine::_tchar			m_szContentStr[128];
	Engine::_tchar			m_szQuestCount[32];
	Engine::_tchar			m_szTargetName[32];

	Engine::_int			m_iQuestCount;
	Engine::_int			m_iLineCount;

	Engine::_vec3			m_vPos;
	Engine::_vec3			m_vScale;

protected:
	inline virtual void		Free(void) override;
};
#endif // QuestBase_h__
