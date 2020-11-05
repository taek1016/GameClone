#ifndef SoundMgr_h__
#define SoundMgr_h__

#include "Engine_Defines.h"
#include "Base.h"
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")

#include <io.h>

class CSoundMgr : public CBase
{
	DECLARE_SINGLETON(CSoundMgr)
private:
	explicit	CSoundMgr(void);
	virtual		~CSoundMgr(void);

public:
	enum CHANNEL_ID { BGM, PLAYER, MONSTER, EFFECT, MAX_CHANNEL };
	
	void		Initialize();
	void		UpdateSound();
	void		PlaySound(const wstring& wstrSoundKey, CHANNEL_ID eID);
	void		PlayBGM(const wstring& wstrSoundKey);
	void		StopSound(CHANNEL_ID eID);
	void		StopAll();
	void		SetVolume(CHANNEL_ID eID, float fVol); // ������ ������ �ּ� 0.f ~ �ִ� 1.f����.

private:
	void		Release();
	void		LoadSoundFile();

	unordered_map<wstring, FMOD_SOUND*>	m_MapSound;

	FMOD_CHANNEL*	m_pChannelArr[MAX_CHANNEL];
	FMOD_SYSTEM*	m_pSystem;


	// CBase��(��) ���� ��ӵ�
	virtual void freeMem(void) override;

};

#endif // SoundMgr_h__
