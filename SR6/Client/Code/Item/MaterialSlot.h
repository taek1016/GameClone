#ifndef MaterialSlot_h__
#define MaterialSlot_h__

#include "GameObject.h"
#include "ItemBase.h"

class Engine::CItemBase;

class CMaterialSlot : public Engine::CGameObject
{
private:
	explicit						CMaterialSlot(void);
	explicit						CMaterialSlot(const CMaterialSlot& rhs);
	virtual							~CMaterialSlot(void);

public:
	virtual HRESULT					Late_Initialize() override;
	virtual HRESULT					Initialize_GameObject() override;
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	void							Add_MaterialNum(void);
	Engine::_bool					Delete_MaterialNum(const Engine::_int& iCnt);

	const Engine::_int				Get_MaterialNum(void) { return m_iCurMaterialNum; }

private:
	void							Set_NumData();
	void							Set_Type(const MATERIAL_TYPE& eType);
	void							Set_Pos(const Engine::_vec3* pPos);

	wstring							m_wStrRenderKey;
	Engine::_int					m_iRenderIdx = 0;
	Engine::_int					m_iCurMaterialNum = 0;
	RECT							m_tRect;
	MATERIAL_TYPE					m_eType;

	_matrix							m_matNumWorld;

	Engine::CTransform*				m_pTransform = nullptr;
	Engine::CTexture*				m_pTexture = nullptr;
	Engine::CTexture*				m_pNumTexture = nullptr;

public:
	static CMaterialSlot*			Create(const Engine::_vec3* pPos, const MATERIAL_TYPE& eType);
	virtual Engine::CGameObject*	Clone(const Engine::_vec3* pPos = nullptr) override;

private:
	virtual void					LoadData(HANDLE hFile) override { ; }
	inline virtual void				freeMem() override;
};

#endif // MaterialSlot_h__