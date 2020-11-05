typedef struct tagObjectBaseInfo
{
	Engine::_vec3	vPos;
	Engine::_vec3	vScale;
	Engine::_vec3	vAngle;

	tagObjectBaseInfo(void)
		: vPos(0.f, 0.f, 0.f)
		, vScale(0.f, 0.f, 0.f)
		, vAngle(0.f, 0.f, 0.f)
	{ }

	tagObjectBaseInfo(const Engine::_vec3& _vPos,
		const Engine::_vec3& _vScale,
		const Engine::_vec3& _vLook)
		: vPos(_vPos)
		, vScale(_vScale)
		, vAngle(_vLook)
	{ }

	tagObjectBaseInfo(const tagObjectBaseInfo& rhs)
		: vPos(rhs.vPos)
		, vScale(rhs.vScale)
		, vAngle(rhs.vAngle)
	{ }

} OBJECTBASE_INFO;

typedef struct tagObjectInfo
{
	OBJECTBASE_INFO	tInfo;
	std::wstring	wStrRenderKey;

	tagObjectInfo(void)
		: tInfo()
		, wStrRenderKey(L"")
	{ }

	tagObjectInfo(const OBJECTBASE_INFO& _tInfo, const wstring& _wStrRenderKey)
		: tInfo(_tInfo)
		, wStrRenderKey(_wStrRenderKey)
	{ }

	tagObjectInfo(const Engine::_vec3& _vPos,
		const Engine::_vec3& _vScale,
		const Engine::_vec3& _vLook,
		const wstring& _wStrRenderKey)
		: tInfo(_vPos, _vScale, _vLook)
		, wStrRenderKey(_wStrRenderKey)
	{ }

} OBJECT_INFO;
