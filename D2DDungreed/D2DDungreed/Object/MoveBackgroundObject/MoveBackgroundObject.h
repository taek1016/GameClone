#ifndef __MOVE_BACKGROUND_OBJECT_H__

#include "..\MoveObject.h"
class CMoveBackgroundObject : public CMoveObject
{
protected:
	CMoveBackgroundObject();

public:
	virtual ~CMoveBackgroundObject();

	static CMoveBackgroundObject*	Create(
		const std::wstring&	wstrObjectKey,
		const std::wstring&	wstrObjectStatus,
		const WORD&			wIndex,
		const D3DXVECTOR3&	vecPos,
		const D3DXVECTOR3&	vecSize,
		const float			fSpeed
		);
	static CMoveBackgroundObject*	Create(
		const std::wstring&	wstrObjectKey,
		const std::wstring&	wstrObjectStatus,
		const WORD&			wIndex,
		const float			fSpeed
	);

public:
	virtual int Update() override;
	virtual void LateUpdate() override;
};

#define __MOVE_BACKGROUND_OBJECT_H__
#endif // !__MOVE_BACKGROUND_OBJECT_H__