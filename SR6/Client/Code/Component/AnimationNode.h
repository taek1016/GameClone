#ifndef AnimationNode_h__
#define AnimationNode_h__


class Engine::CTransform;
typedef  Engine::ANIM_TRANSFORM_INFO ANI_TRANSFORM;
class CAnimationNode : public CBase
{
	Engine::CTransform*				m_pTransform = nullptr;

	// 애니메이션 시작 지점
	ANI_TRANSFORM					m_StartInfo;

	// 애니메이션 끝 지점
	ANI_TRANSFORM					m_EndInfo;

	// 애니메이션 재생 속도
	float							m_fTime = 0;
	float							m_fCurTime = 0;

	int								m_iCurIndex = 0;
	int								m_iAnimInterval = 0;
	// 현재 동작 종료 여부
	bool							m_bEnd = false;

	bool							m_bTransform[Engine::TRANS_END];

	vector<ANI_TRANSFORM>			m_vecAnimTransformInfo;
public:
	CAnimationNode(Engine::CGameObject* obj);
	CAnimationNode();
	~CAnimationNode();
	CAnimationNode(const CAnimationNode& rhs);

	void							SetAnimTransform(Engine::ANIMTRANSFORM animTrans);

	void							SetStartInfo(ANI_TRANSFORM info) { m_StartInfo = info; }
	void							SetEndInfo(ANI_TRANSFORM info) { m_EndInfo = info; }

	void							SetInterval(int interval) { m_iAnimInterval = interval; }
	void							SetTimeSpeed(float spd) { m_fTime = spd; }

	void							SetAnimInfo(ANI_TRANSFORM start, ANI_TRANSFORM end, float fTime, int interval);

	void							Play();

	void							Stop();

	void							Action(const float& fDeltaTime);

	bool							IsEnd() { return m_bEnd; }

	const ANI_TRANSFORM&			GetEndInfo() { return m_EndInfo; }
	const ANI_TRANSFORM&			GetStartInfo() { return m_StartInfo; }

	int								GetInterval() { return m_iAnimInterval; }
	float							GetSpeedTime() { return m_fTime; }

	void							SetTransform(Engine::CTransform* transform) { m_pTransform = transform; }

	void							Initialize();

	void							SaveData(HANDLE hFile);
	void							LoadData(HANDLE hFile);

	// CBase을(를) 통해 상속됨
	virtual void freeMem(void) override;
};

#endif