#include "stdafx.h"
#include "Sound.h"

void SoundManager::Init()
{
    SetUseASyncLoadFlag(FALSE);

    LoadSound("BGM_Title", "data/sound/BGM_Title.mp3");
    LoadSound("BGM_Game", "data/sound/BGM_Game.mp3");
}

void SoundManager::LoadSound(const std::string& name, const std::string& path)
{
    if (soundHandles.find(name) == soundHandles.end()) {
        int handle = LoadSoundMem(path.c_str());
        soundHandles[name] = handle;
    }
}

void SoundManager::Play_Sound(const std::string& name, bool isLoop)
{
    // ‰¹‚ðÄ¶‚·‚éB
    auto it = soundHandles.find(name);
    if (it == soundHandles.end()) return;

    int playType = isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_NORMAL;

    PlaySoundMem(it->second,playType);
}

void SoundManager::StopSound(const std::string& name)
{
    // ‰¹‚ð’âŽ~‚·‚éB
    auto it = soundHandles.find(name);
    if (it == soundHandles.end()) return;

    StopSoundMem(it->second);
}