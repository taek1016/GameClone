#ifndef MouseMgr_h__
#define MouseMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CMouse;
class CGameObject;

class ENGINE_DLL CMouseManager : public CBase
{
	DECLARE_SINGLETON(CMouseManager)

private:
	explicit	CMouseManager(void);
	virtual		~CMouseManager(void);

public:
	void		Late_Initialize();
	HRESULT		Initialize_MouseMgr(const _int& iMaxIdx, const HWND& hWnd);
	HRESULT		Set_CurMouse(const _int& iCurMouse);
	_int		Update_Mouse(const _float& fTimeDelta);

	const _vec3*	GetMousePos();

	template <typename T>
	T*			Add_Mouse(const _int& iMouseIdx)
	{
		T* pInstance = T::Create();

		if (FAILED(pInstance->Initialize_GameObject()))
		{
			Safe_Release(pInstance);
		}

		m_vecMouse[iMouseIdx] = pInstance;

		return pInstance;
	}

private:
	_vec3				m_vMouse;

	_int				m_iCurMouse = 0;
	_int				m_iMaxMouse = 0;
	vector<CMouse*>		m_vecMouse;

	HWND				m_hWnd = nullptr;
private:
	inline virtual void	freeMem();
};

END

#endif // MouseMgr_h__
