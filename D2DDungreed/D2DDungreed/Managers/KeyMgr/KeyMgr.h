#ifndef __KEY_MGR_H__
#define __KEY_MGR_H__

const DWORD KEY_UP			= 0x00000001;	// ��
const DWORD KEY_DOWN		= 0x00000002;	// �Ʒ�
const DWORD KEY_LEFT		= 0x00000004;	// ����
const DWORD KEY_RIGHT		= 0x00000008;	// ������
const DWORD KEY_SPACE		= 0x00000010;	// �Ʒ� �����̽� -> �Ʒ�����
const DWORD KEY_RETURN		= 0x00000020;	// ����Ű
const DWORD KEY_LBUTTON		= 0x00000040;	// ���� Ű
const DWORD KEY_RBUTTON		= 0x00000080;	// �뽬 Ű
const DWORD KEY_V			= 0x00000100;	// �κ��丮
const DWORD KEY_F			= 0x00000200;	//
const DWORD KEY_TAB			= 0x00000400;	//
//const DWORD KEY_V			= 0x00000800;	//

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	CKeyMgr();
	~CKeyMgr();

public:
	void	Update		();

	bool	KeyDown		(DWORD dwKey);
	bool	KeyUp		(DWORD dwKey);
	bool	KeyPressing	(DWORD dwKey);

private:
	void	AssertMember() const;

private:
	DWORD	m_dwKeyDown;
	DWORD	m_dwKeyUp;
	DWORD	m_dwCurKey;
};

#endif // !__KEY_MGR_H__
