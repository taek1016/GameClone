#ifndef FrameMgr_h__
#define FrameMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CFrame;
class ENGINE_DLL CFrameMgr : public CBase
{
	DECLARE_SINGLETON(CFrameMgr)

private:
	explicit CFrameMgr(void);
	virtual ~CFrameMgr(void);

public:
	_bool		IsPermit_Call(const _int iFrameTag, const _float fTimeDelta);
	HRESULT		Ready_Frame(const _int iFrameTag, const _float fCallLimit);
	void		Initialize_Frame(const _int iFrameSize);
private:
	CFrame*		Find_Frame(const _int iFrameTag);

private:
	bool				m_bInitialized;
	vector<CFrame*>		m_vecFrame;

public:
	virtual void	freeMem(void);
};

END
#endif // FrameMgr_h__
