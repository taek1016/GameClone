#ifndef Animation_h__
#define Animation_h__

#include "Base.h"

class Engine::CTransform;
class CAnimationNode;
class CAnimation : public CBase
{
private:
	Engine::_tchar					m_strAnimName[100];
	CAnimation();
	CAnimation(const CAnimation& rhs);
	~CAnimation();

protected:
	list<CAnimationNode*>			m_ltAnimations;
	list<CAnimationNode*>::iterator m_iter;

	bool							m_bPlay = false;
	bool							m_bStart = true;
public:
	list<CAnimationNode*>::iterator GetAnimListIter();
	list<CAnimationNode*>::iterator GetAnimListEndIter();

	void							Start() { m_bStart = false; }

	void							SetTransform(Engine::CTransform* transform);

	int								GetAnimListSize() { return m_ltAnimations.size(); }

	void							SetAnimName(Engine::_tchar* strName, int size);
	Engine::_tchar*							GetAnimName() { return m_strAnimName; }

	void							DeleteAnimation(int index);

	void							Initialize();

	void							Play();
	void							Stop();

	void							freeMem() override;

	void							Update(const float& fDeltaTime);

	void							AddAnimation(CAnimationNode* animNode);

	static CAnimation*				Create();

	void							SaveData(HANDLE hFile);
	void							LoadData(HANDLE hFile);

	CAnimation*						Clone();
};

#endif