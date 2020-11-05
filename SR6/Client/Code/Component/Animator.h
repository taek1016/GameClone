#ifndef Animator_h__
#define Animator_h__

class CAnimation;
class Engine::CGameObject;
class CAnimator : public Engine::CComponent
{
private:
	map<wstring, CAnimation*>	m_mapAnimation;

	CAnimation*					m_pCurAnimation = nullptr;

	explicit	CAnimator();
	explicit	CAnimator(const CAnimator& rhs);
public:
	void						AddAnimation(Engine::_tchar* animKey, CAnimation* anim);
	void						Play();
	void						ChangeAnim(const Engine::_tchar* animKey);
	void						Stop();

	int							Update_Component(const float& fDeltaTime)override;

	static CAnimator*			Create();

	void						LoadData(HANDLE hFile)override;

	void						SetAnimTransform();

	HRESULT						Attach(Engine::CGameObject* pObj, Engine::COMPONENTID com_ID)override;

	CComponent*					Clone()override;

	// CComponent을(를) 통해 상속됨
	virtual void freeMem(void) override;
};

#endif