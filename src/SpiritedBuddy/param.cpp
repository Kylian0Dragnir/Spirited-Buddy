#include "param.h"
#include "DataManager.h"
#include "FileDataSource.h"

Param::Param()
{
	m_iniFile = new IniFile();
	m_iniFile->InitPath("../../Assets/param.ini");
	m_iniFile->Load();
	Reload();

	FileDataSource* filedata = new FileDataSource("../../Assets/param.ini");
	DataManager::Get().Register(this, filedata);
}

Param& Param::Get()
{
	static Param Instance;
	return Instance;
}
void Param::SetLevelUnlockedCount(float value)
{
	m_iniFile->SetFloat("GeneralParams", "LevelUnlockedCount", value);
	m_iniFile->Save();
}

void Param::SetMusicMute(float value)
{
	m_iniFile->SetFloat("GeneralParams", "MusicMute", value);
	m_iniFile->Save();
}

void Param::SetSFXMute(float value)
{
	m_iniFile->SetFloat("GeneralParams", "SFX_Mute", value);
	m_iniFile->Save();
}

void Param::Reload()
{
	m_iniFile->Load();
	m_levelUnlockedCount = m_iniFile->GetFloat("GeneralParams", "LevelUnlockedCount", m_levelUnlockedCount);
	m_isMusicMute = m_iniFile->GetFloat("GeneralParams", "MusicMute", m_isMusicMute);
	m_isSFXMute = m_iniFile->GetFloat("GeneralParams", "SFX_Mute", m_isSFXMute);
}
