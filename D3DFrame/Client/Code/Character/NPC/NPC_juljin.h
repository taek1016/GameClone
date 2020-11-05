#ifndef NPC_juljin_h__
#define NPC_juljin_h__

#include "../NPCBase.h"

class CNPC_Zuljin : public CNPCBase
{
private:
	explicit						CNPC_Zuljin(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CNPC_Zuljin(const CNPC_Zuljin& rhs);
	virtual							~CNPC_Zuljin(void) = default;

public:


private:
	virtual void					initialize_NPCUI(void) override;

public:
	static CNPC_Zuljin*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // NPC_juljin_h__
