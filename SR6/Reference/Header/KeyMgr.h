#ifndef KeyMgr_h__
#define KeyMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CKeyMgr : public CBase
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	explicit				CKeyMgr(void);
	virtual					~CKeyMgr(void);

public:
	HRESULT					Register_Key(const _int iKey);
	void					Update();

	bool					KeyDown(const _int iKey);
	bool					KeyUp(const _int iKey);
	bool					KeyPressing(const _int iKey);

private:
	_uint					m_iCurKeyCount = 0;

	_ulong					m_dwKeyDown = 0;
	_ulong					m_dwKeyUp = 0;
	_ulong					m_dwCurKey = 0;

	map<const _int, _int>	m_mapKey;

private:
	inline virtual void		freeMem();
};
END
#endif // KeyMgr_h__
