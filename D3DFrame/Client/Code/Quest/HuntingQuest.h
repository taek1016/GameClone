#ifndef HuntingQuest_h__
#define HuntingQuest_h__

#include "QuestBase.h"

class CHuntingQuest : public CQuestBase
{
private:
	explicit				CHuntingQuest(void);
	virtual					~CHuntingQuest(void) = default;

public:
	virtual void			Update_Quest(void) override;
	void					Add_KillNum(void);


private:
	void					set_TargetName(const Engine::_tchar* pTargetName);
	void					set_KillNum(const Engine::_int& iGoalNum);
	void					set_Exp(const Engine::_int& iExp);

	Engine::_int			m_iCurKillNum;
	Engine::_int			m_iKillGoal;
	Engine::_int			m_iExp;

public:
	static CHuntingQuest*	Create(const Engine::_tchar* pTargetName, const Engine::_int& iCount, const Engine::_int& iExp);

private:
	inline virtual void		Free(void) override;
};

#endif // HuntingQuest_h__
