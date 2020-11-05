#ifndef NPC_Thrall_h__
#define NPC_Thrall_h__

#include "../NPCBase.h"

class CQuestUI;

class CNPC_Thrall : public CNPCBase
{
private:
	explicit										CNPC_Thrall(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit										CNPC_Thrall(const CNPC_Thrall& rhs);
	virtual											~CNPC_Thrall(void) = default;

private:
	void											initialize_QuestContent(void);
	void											make_Content(const Engine::_tchar* pKey);
	virtual void									act(void) override;
	virtual void									initialize_NPCUI(void) override;
	
	map<const Engine::_tchar*, list<FONT_INFO>*>	m_QuestContent;
	const Engine::_tchar*							m_pCurrentQuest;

public:
	static CNPC_Thrall*								Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*					Clone(void) override;

private:
	inline virtual void								Free(void) override;
};
#endif // NPC_Thrall_h__
