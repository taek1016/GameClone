struct HP_INFO
{
	Engine::_int	iHP;
	Engine::_int	iMaxHP;

	HP_INFO(void)
		: iHP(0)
		, iMaxHP(0)
	{ }

	HP_INFO(const Engine::_int& _iHP, const Engine::_int& _iMaxHP)
		: iHP(_iHP)
		, iMaxHP(_iMaxHP)
	{ }

	HP_INFO(const HP_INFO& rhs)
		: iHP(rhs.iHP)
		, iMaxHP(rhs.iMaxHP)
	{ }

	HP_INFO operator* (const Engine::_int& iLevel)
	{
		return HP_INFO(iHP * iLevel, iMaxHP * iLevel);
	}

	HP_INFO operator+(const HP_INFO& rhs)
	{
		return HP_INFO(iHP + rhs.iHP, iMaxHP + rhs.iMaxHP);
	}

	HP_INFO operator-(const HP_INFO& rhs)
	{
		return HP_INFO(iHP - rhs.iHP, iMaxHP - rhs.iMaxHP);
	}
};

struct MP_INFO
{
	Engine::_int	iMP;
	Engine::_int	iMaxMP;

	MP_INFO(void)
		: iMP(0)
		, iMaxMP(0)
	{ }

	MP_INFO(const Engine::_int& _iMP, const Engine::_int& _iMaxMP)
		: iMP(_iMP)
		, iMaxMP(_iMaxMP)
	{ }

	MP_INFO(const MP_INFO& rhs)
		: iMP(rhs.iMP)
		, iMaxMP(rhs.iMaxMP)
	{ }

	MP_INFO operator* (const Engine::_int& iLevel)
	{
		return MP_INFO(iMP * iLevel, iMaxMP * iLevel);
	}

	MP_INFO operator+(const MP_INFO& rhs)
	{
		return MP_INFO(iMP + rhs.iMP, iMaxMP + rhs.iMaxMP);
	}

	MP_INFO operator-(const MP_INFO& rhs)
	{
		return MP_INFO(iMP - rhs.iMP, iMaxMP - rhs.iMaxMP);
	}

};

struct ATT_ARMOR_INFO
{
	Engine::_int	iAtt;
	Engine::_int	iArmor;

	ATT_ARMOR_INFO(void)
		: iAtt(0)
		, iArmor(0)
	{ }

	ATT_ARMOR_INFO(const Engine::_int& _iAtt, const Engine::_int& _iArmor)
		: iAtt(_iAtt)
		, iArmor(_iArmor)
	{ }

	ATT_ARMOR_INFO(const ATT_ARMOR_INFO& rhs)
		: iAtt(rhs.iAtt)
		, iArmor(rhs.iArmor)
	{ }

	ATT_ARMOR_INFO operator* (const Engine::_int& iLevel)
	{
		return ATT_ARMOR_INFO(iAtt * iLevel, iArmor * iLevel);
	}

	ATT_ARMOR_INFO operator+(const ATT_ARMOR_INFO& rhs)
	{
		return ATT_ARMOR_INFO(iAtt + rhs.iAtt, iArmor + rhs.iArmor);
	}

	ATT_ARMOR_INFO operator-(const ATT_ARMOR_INFO& rhs)
	{
		return ATT_ARMOR_INFO(iAtt - rhs.iAtt, iArmor - rhs.iArmor);
	}
};

struct MOVE_INFO
{
	Engine::_float	fWalkSpeed;
	Engine::_float	fRunSpeed;

	MOVE_INFO(void)
		: fWalkSpeed(0.f)
		, fRunSpeed(0.f)
	{ }

	MOVE_INFO(const Engine::_float& _fWalkSpeed, const Engine::_float& _fRunSpeed)
		: fWalkSpeed(_fWalkSpeed)
		, fRunSpeed(_fRunSpeed)
	{ }

	MOVE_INFO(const MOVE_INFO& rhs)
		: fWalkSpeed(rhs.fWalkSpeed)
		, fRunSpeed(rhs.fRunSpeed)
	{ }

	MOVE_INFO operator*(const Engine::_int iLevel)
	{
		return *this;
	}

	MOVE_INFO operator+(const MOVE_INFO& rhs)
	{
		return MOVE_INFO(fWalkSpeed + rhs.fWalkSpeed, fRunSpeed + rhs.fRunSpeed);
	}

	MOVE_INFO operator-(const MOVE_INFO& rhs)
	{
		return MOVE_INFO(fWalkSpeed - rhs.fWalkSpeed, fRunSpeed - rhs.fRunSpeed);
	}
};

struct PERCENT_INFO
{
	Engine::_float	fDefaultDodgePercent;
	Engine::_float	fDefaultSpellCastPercent;

	PERCENT_INFO(void)
		: fDefaultDodgePercent(0.f)
		, fDefaultSpellCastPercent(0.f)
	{ }

	PERCENT_INFO(const Engine::_float& _fDodge, const Engine::_float& _fSpell)
		: fDefaultDodgePercent(_fDodge)
		, fDefaultSpellCastPercent(_fSpell)
	{ }

	PERCENT_INFO(const PERCENT_INFO& rhs)
		: fDefaultDodgePercent(rhs.fDefaultDodgePercent)
		, fDefaultSpellCastPercent(rhs.fDefaultSpellCastPercent)
	{ }

	PERCENT_INFO operator*(const Engine::_int iLevel)
	{
		return *this;
	}

};

struct RESIST_INFO
{
	Engine::_float	fFireResist;
	Engine::_float	fIceResist;
	Engine::_float	fVisionResist;

	RESIST_INFO(void)
		: fFireResist(0.f)
		, fIceResist(0.f)
		, fVisionResist(0.f)
	{ }

	RESIST_INFO(const Engine::_float& _fFire, const Engine::_float& _fIce, const Engine::_float& _fVision)
		: fFireResist(_fFire)
		, fIceResist(_fIce)
		, fVisionResist(_fVision)
	{ }

	RESIST_INFO(const RESIST_INFO& rhs)
		: fFireResist(rhs.fFireResist)
		, fIceResist(rhs.fIceResist)
		, fVisionResist(rhs.fVisionResist)
	{ }

	RESIST_INFO operator*(const Engine::_int iLevel)
	{
		return *this;
	}

};

struct UNIT_INFO
{
	HP_INFO			tHP;
	MP_INFO			tMP;

	ATT_ARMOR_INFO	tAttArmor;

	MOVE_INFO		tMove;

	PERCENT_INFO	tPercent;

	RESIST_INFO		tResist;

	UNIT_INFO(void)
		: tHP()
		, tMP()
		, tAttArmor()
		, tMove()
		, tPercent()
		, tResist()
	{ }

	UNIT_INFO(const HP_INFO& _tHp, const MP_INFO& _tMP, const ATT_ARMOR_INFO& _tAttArmor,
		const MOVE_INFO& _tMove, const PERCENT_INFO& _tPercent, const RESIST_INFO& _tResist)
		: tHP(_tHp)
		, tMP(_tMP)
		, tAttArmor(_tAttArmor)
		, tMove(_tMove)
		, tPercent(_tPercent)
		, tResist(_tResist)
	{ }

	UNIT_INFO(const UNIT_INFO& rhs)
		: tHP(rhs.tHP)
		, tMP(rhs.tMP)
		, tAttArmor(rhs.tAttArmor)
		, tMove(rhs.tMove)
		, tPercent(rhs.tPercent)
		, tResist(rhs.tResist)
	{ }

	UNIT_INFO operator *(const Engine::_int& iLevel)
	{
		return UNIT_INFO(tHP * iLevel, tMP * iLevel, tAttArmor * iLevel, tMove * iLevel, tPercent * iLevel, tResist * iLevel);
	}

	UNIT_INFO operator+(const UNIT_INFO& rhs)
	{
		return UNIT_INFO(tHP + rhs.tHP, tMP + rhs.tMP, tAttArmor + rhs.tAttArmor, tMove + rhs.tMove, tPercent, tResist);
	}

	UNIT_INFO operator-(const UNIT_INFO& rhs)
	{
		return UNIT_INFO(tHP - rhs.tHP, tMP - rhs.tMP, tAttArmor - rhs.tAttArmor, tMove - rhs.tMove, tPercent, tResist);
	}
};
