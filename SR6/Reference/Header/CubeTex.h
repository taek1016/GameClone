#ifndef Cube_h__
#define Cube_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CCubeTex : public Engine::CVIBuffer
{
	//VTXCUBE*				m_pVertices = nullptr;
	//INDEX32*				m_pIndices = nullptr;

	_vec3					m_vVertices[8];
protected:
	explicit				CCubeTex();
	explicit				CCubeTex(const CCubeTex& rhs);
	virtual					~CCubeTex(void);

public:
	virtual HRESULT			Initialize_Buffer(void) override;

	virtual HRESULT			Attach(CGameObject* pObj, COMPONENTID com_ID);

	// CVIBuffer을(를) 통해 상속됨
	virtual CResources*		Clone(void) override;

	void					LoadData(HANDLE hFile)override;

	static CCubeTex*		Create();
};

END

#endif // Cube_h__
