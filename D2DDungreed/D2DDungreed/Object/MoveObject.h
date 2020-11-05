#ifndef __MOVE_OBJECT_H__

#include "GameObject.h"
#include "Effect\Effect.h"
#include "../CoolTime/CoolTime.h"
#include "Effect/HitEffect.h"

class CMoveObject : public CGameObject
{
protected:
	bool		m_bHit;
	int			m_iHP;
	int			m_iMaxHP;

	CCoolTime	m_NextHitCool;

protected:
	CMoveObject					();

public:
	virtual ~CMoveObject		();

	virtual int	Update			() override	PURE;
	virtual void LateUpdate		() override	PURE;
	virtual void Render			() override;

	void SetCollideGround		();

	virtual void GetDamage		(float fDamage)
	{
		if (!m_bHit)
		{
			m_bHit = true;
			m_iHP -= static_cast<int>(fDamage);

			if (m_wStrObjectKey == L"Player")
			{
				CSINGLETON::pSoundMgr->PlaySound(L"HitPlayer.wav", CSoundMgr::CHANNEL_ID::PLAYER);
				CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_EFFECT, CHitEffect::Create(m_tInfo.vPos, this));
				CSINGLETON::pHitScreen->SetHit();
				CSINGLETON::pCameraMgr->SetHit();
			}
			else
			{
				if (m_iHP <= 0)
				{
					return;
				}
				CSINGLETON::pSoundMgr->PlaySound(L"HitMonster.wav", CSoundMgr::CHANNEL_ID::MONSTER);
				CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_EFFECT, CHitEffect::Create(m_tInfo.vPos, this));
			}
		}
	}

	const int GetMaxHP			() const
	{
		return m_iMaxHP;
	}
	const int GetHP				() const
	{
		return m_iHP;
	}

protected:
	virtual void ChangeStatus	();	// 행동 결정.
				 
	virtual void UpdateRect		() override;

	void FreeDownObject			();
	void CheckMapOutside		();
	void Jump					();
	void Move					(float fX);
	void HitCheck				()
	{
		if (m_bHit)
		{
			m_NextHitCool.Update();
			if (m_NextHitCool.GetNextCool())
			{
				m_bHit = false;
			}
		}
	}

	void InitializeMove			()
	{
		m_tMove = D3DXVECTOR3(0.f, 0.f, 0.f);
	}
	void SetFrame				() 
	{ 
		m_tFrame.SetMaxFrame(static_cast<float>(m_iObjectStatus[m_eCurStatus])); 
	}
	void SetSpeed				(float fSpeed) 
	{ 
		m_fSpeed = fSpeed;	
	}
	
	void InitializeAnimation	()
	{
		for (int i = 0; i < static_cast<int>(OBJECT_STATUS::STATUS_END); ++i)
		{
			SetAnimation(static_cast<OBJECT_STATUS>(i), 0);
		}
	}
	void SetAnimation			(OBJECT_STATUS eStatus, int iAnimation)
	{
		m_iObjectStatus[eStatus] = iAnimation;
	}
	void SetCurStatus			(const OBJECT_STATUS eStatus)
	{
		m_eCurStatus = eStatus;
	}
	
	void SetPreStatus			()
	{
		m_ePreStatus = m_eCurStatus;
	}

	const int GetAnimation		(OBJECT_STATUS eStatus) const
	{
		return m_iObjectStatus[eStatus];
	}
	
	void InitializeHP			(int iHP)
	{
		m_iMaxHP	= iHP;
		m_iHP		= iHP;
	}
	void Hit					()
	{
		m_bHit = true;
	}

private:
	void			AssertMember();
	void			SetStatus();

protected:
	bool			m_bGround;

	float			m_fAngle;
	float			m_fSpeed;

	OBJECT_STATUS	m_eCurStatus;
	OBJECT_STATUS	m_ePreStatus;

	GRAVITY_INFO	m_tGravityInfo;

	COUNT			m_tJumpCount;
	
	D3DXVECTOR3		m_tMove;

private:
	int				m_iObjectStatus[OBJECT_STATUS::STATUS_END];
	int				m_iWidth;
	int				m_iHeight;
};

#define __MOVE_OBJECT_H__
#endif // !__MOVE_OBJECT_H__