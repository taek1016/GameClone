typedef struct tagFileInfo
{
	wstring wStrName;
	wstring wStrFilePath;
	wstring	wStrFileName;
	int		iResourceCount;

	tagFileInfo(void)
		: wStrName(L"")
		, wStrFilePath(L"")
		, wStrFileName(L"")
		, iResourceCount(0)
	{ }

	tagFileInfo(const wstring& _wStrName,
		const wstring& _wStrFilePath,
		const wstring& _wStrFileName,
		const int& _iResourceCount)
		: wStrName(_wStrName)
		, wStrFilePath(_wStrFilePath)
		, wStrFileName(_wStrFileName)
		, iResourceCount(_iResourceCount)
	{ }

	tagFileInfo(const tagFileInfo& rhs)
		: wStrName(rhs.wStrName)
		, wStrFilePath(rhs.wStrFilePath)
		, wStrFileName(rhs.wStrFileName)
		, iResourceCount(rhs.iResourceCount)
	{ }

} FILE_INFO;
