#ifndef __OBJECT_FACTORY_H__

class CGameObject;

template <typename T>
class CObjectFactory
{
public:
	static CGameObject*	Create(const D3DXVECTOR3* pVec);
};

#define __OBJECT_FACTORY_H__
#endif // !__OBJECT_FACTORY_H__

template<typename T>
inline CGameObject * CObjectFactory<T>::Create(const D3DXVECTOR3 * pVec)
{
	CGameObject*	pInstance = new T;

	return NULL;
}
