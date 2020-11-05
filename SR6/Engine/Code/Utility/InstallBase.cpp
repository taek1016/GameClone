#include "InstallBase.h"

USING(Engine)

CInstallBase::CInstallBase(void)
	: CItemBase()
{
}

CInstallBase::CInstallBase(const CInstallBase & rhs)
	: CItemBase(rhs)
{
}

CInstallBase::~CInstallBase(void)
{
}

_int CInstallBase::Update_Component(const _float & fTimeDelta)
{
	return 0;
}

void CInstallBase::Install()
{
}
