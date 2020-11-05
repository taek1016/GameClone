#ifndef __TIME_MGR_H__
#define __TIME_MGR_H__

class CTimeMgr
{
private:
	float			m_fDeltaTime;	// 1초당 걸리는 시간
	float			m_fTimeScale;

	LARGE_INTEGER	m_liOldTimeOne;
	LARGE_INTEGER	m_liOldTimeTwo;
	LARGE_INTEGER	m_liCurTime;
	LARGE_INTEGER	m_liCpuTick;

public:
	const	float	GetDelta() const;
	void	Update();
	void	SetTimeScale(float fScale);

	DECLARE_SINGLETON(CTimeMgr)

private:
	CTimeMgr();
	virtual ~CTimeMgr();

	void	AssertMember();

};

#endif // !__TIME_MGR_H__
