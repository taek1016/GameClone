#ifndef Body_h__
#define Body_h__

#include "Component.h"

USING(Engine)

class CAnimator;
class CBody : public CComponent
{
private:
	vector<CAnimator*>			m_vecAnimators;
	vector<wstring>				m_vecObjNames;

	ANIMSTATE					m_AnimState;

	CBody();
	CBody(const CBody& rhs);
public:
	void						PlayAnimation(_tchar* animKey);

	void						PlayArmAnimation(_tchar* animKey);
	void						PlayLegAnimation(_tchar* animKey);

	void						StopAnimation();

	void						AddAnimator(CAnimator* animator);
	void						RemoveAnimator(int index);

	void						SetPartAnimation(int index, CAnimator* animator);
	
	// CComponent을(를) 통해 상속됨
	virtual void				freeMem(void) override;
	void						LoadData(HANDLE hFile)override;

	_int						Update_Component(const float& fDeltaTime)override;

	CBody*						Clone()override;

	static CBody*				Create();
};

#endif