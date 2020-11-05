#ifndef __FRAME_MGR_H__
#define __FRAME_MGR_H__

class CFrameMgr
{
	DECLARE_SINGLETON(CFrameMgr)

private:
	CFrameMgr();
	virtual ~CFrameMgr();

public:
	bool	LimitFrame();
	void	RenderFPS();
	void	SetFps(float fFps);

private:
	void	AssertMember() const;
	
private:
	float			m_fFps;
	float			m_fTimeCount;
	float			m_fDeltaTime;

	int				m_iFpsCount;

	LARGE_INTEGER	m_liOldTimeOne;
	LARGE_INTEGER	m_liOldTimeTwo;
	LARGE_INTEGER	m_liCurTime;
	LARGE_INTEGER	m_liCpuTick;

	TCHAR			m_szFPS[MIN_STR];
};

#endif // !__FRAME_MGR_H__
