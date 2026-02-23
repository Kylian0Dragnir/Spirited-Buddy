#pragma once
#include "DataAsset.h"
#include "IniFile.h"
#include <iostream>

class Param : public DataAsset
{
	float m_levelUnlockedCount;
	float m_isMusicMute;
	float m_isSFXMute;

	IniFile* m_iniFile;

	Param();

public:
	static Param& Get();

	void SetLevelUnlockedCount(float value);
	float GetLevelUnlockedCount() { return m_levelUnlockedCount; }

	void SetMusicMute(float value);
	float IsMusicMute() { return m_isMusicMute; }

	void SetSFXMute(float value);
	float IsSFXMute() { return m_isSFXMute; }

	void Reload() override;
};

