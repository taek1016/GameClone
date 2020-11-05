#ifndef QuestMgr_h__
#define QuestMgr_h__

#include "Base.h"

class CQuestBase;

class CQuestMgr : public CBase
{
	DECLARE_SINGLETON(CQuestMgr)

private:
	explicit									CQuestMgr(void);
	virtual										~CQuestMgr(void);

public:
	void										Update_Quest(void);

	void										Add_HuntingQuest(const Engine::_tchar* pHuntingType, const Engine::_int& iCount, const Engine::_int& iExp);
	void										Kill_Monster(const Engine::_tchar* pMonsterName);
	void										Activate_HuntingQuest(const Engine::_tchar* pHuntingQuest);

	const Engine::_tchar*						Get_ActivatedQuestName(void);
	const Engine::_tchar*						Get_NextQuestName(void);

	Engine::_bool								Is_Cleared(const Engine::_tchar* pKey);

private:
	map<const Engine::_tchar*, CQuestBase*>		m_HuntingQuestMap;

	Engine::_int								m_iQuestCount;

private:
	inline virtual void							Free(void) override;
};

#endif // QuestMgr_h__
