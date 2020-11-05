#ifndef __COOL_TIME_H__

class CCoolTime
{
private:
	float m_fCoolTime;
	float m_fCurTime;

public:
	CCoolTime();
	~CCoolTime();

	void Update		();
	void SetCool	(float fCoolTime)
	{
		m_fCoolTime = fCoolTime;
	}

	bool GetNextCool()
	{
		if (m_fCurTime >= m_fCoolTime)
		{
			m_fCurTime = 0.f;
			return true;
		}
		return false;
	}
};

#define __COOL_TIME_H__
#endif