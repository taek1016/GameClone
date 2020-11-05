#ifndef Management_h__
#define Management_h__

#include "Scene.h"

BEGIN(Engine)

class ENGINE_DLL CManagement : public CBase
{
	DECLARE_SINGLETON(CManagement)

private:
	explicit		CManagement(void);
	virtual			~CManagement(void);

public:
	template<typename T>
	T* SetUp_Scene(LPDIRECT3DDEVICE9 pGraphicDev)
	{
		Safe_Release(m_pScene);

		m_pScene = T::Create(pGraphicDev);

		return dynamic_cast<T*>(m_pScene);
	}
	_int			Update_Scene(const _float& fTimeDelta);
	void			Render_Scene(void);

private:
	CScene*			m_pScene = nullptr;
private:
	virtual void	Free(void);
};

END
#endif // Management_h__