#ifndef ToolContainerMgr_h__
#define ToolContainerMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

#include "Tool/TerrainTool.h"

class CToolContainer : public CBase
{
	DECLARE_SINGLETON(CToolContainer)

private:
	explicit	CToolContainer(void);
	virtual		~CToolContainer(void);

public:
	void		Add_Tool(const Engine::_tchar* pKey, CDialogEx* pTool);

	template <typename T>
	T*			Get_Tool(const Engine::_tchar* pKey)
	{
		return dynamic_cast<T*>(m_mapContainer[pKey]);
	}
private:
	map<const Engine::_tchar*, CDialogEx*> m_mapContainer;

private:
	inline virtual void	Free(void);
};

#endif // ToolContainerMgr_h__