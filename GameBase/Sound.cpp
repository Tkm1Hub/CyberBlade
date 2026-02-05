#include "stdafx.h"
#include "Sound.h"

void SoundManager::Init()
{
    LoadSound("BGM_Title", "data/sound/BGM_Title.mp3",40,true);
    LoadSound("BGM_Game", "data/sound/BGM_Game.mp3",50,true);
    LoadSound("BGM_Result", "data/sound/BGM_Result.mp3", 45, true);
    LoadSound("SE_Title", "data/sound/SE_Title.wav",60,false);
    LoadSound("SE_LockOn", "data/sound/SE_LockOn.wav", 70, false);
    LoadSound("SE_Slash1", "data/sound/SE_Slash1.mp3",75, false);
    LoadSound("SE_Slash2", "data/sound/SE_Slash2.mp3", 75, false);
    LoadSound("SE_Slash3", "data/sound/SE_Slash3.mp3", 75, false);
    LoadSound("SE_Hit1", "data/sound/SE_Hit1.mp3", 75, false);
    LoadSound("SE_Hit2", "data/sound/SE_Hit2.mp3", 75, false);
    LoadSound("SE_Hit3", "data/sound/SE_Hit3.mp3", 75, false);
    LoadSound("SE_HitDash", "data/sound/SE_HitDash.mp3", 75, false);
    LoadSound("SE_SlashDash", "data/sound/SE_SlashDash.mp3", 75, false);
    LoadSound("SE_Jump", "data/sound/SE_Jump.mp3", 60, false);
    LoadSound("SE_Landing", "data/sound/SE_Landing.mp3", 60, false);
    LoadSound("SE_Dodge", "data/sound/SE_Dodge.mp3", 70, false);
    LoadSound("SE_DodgeJust1", "data/sound/SE_DodgeJust1.mp3", 90, false);
    LoadSound("SE_DodgeJust2", "data/sound/SE_DodgeJust2.mp3", 90, false);
    LoadSound("カーソル移動", "data/sound/カーソル移動.mp3", 50, false);
    LoadSound("SE_Player_Damage", "data/sound/SE_Player_Damage.mp3", 80, false);
    LoadSound("SE_Enemy_JumpAttack", "data/sound/SE_Enemy_JumpAttack.mp3", 100, false);
    LoadSound("SE_Enemy_Jump", "data/sound/SE_Enemy_Jump.mp3", 75, false);
    LoadSound("SE_Enemy_Walk", "data/sound/SE_Enemy_Walk.mp3", 80, true);
    LoadSound("SE_Enemy_Alert1", "data/sound/SE_Enemy_Alert1.mp3", 75, false);
    LoadSound("SE_Enemy_Alert2", "data/sound/SE_Enemy_Alert2.mp3", 80, false);
    LoadSound("SE_Enemy_Alert3", "data/sound/SE_Enemy_Alert3.mp3", 65, false);
    LoadSound("SE_Enemy_Move", "data/sound/SE_Enemy_Move.mp3", 90, false);
    LoadSound("SE_Enemy_Warning", "data/sound/SE_Enemy_Warning.mp3", 90, false);
    LoadSound("カーソル移動", "data/sound/カーソル移動.mp3", 50, false);
    LoadSound("SE_Player_Walk", "data/sound/SE_Player_Walk.mp3", 100, true);
    LoadSound("SE_Player_SlowRun", "data/sound/SE_Player_SlowRun.mp3", 100, true);
    LoadSound("SE_Player_Run", "data/sound/SE_Player_Run.mp3", 100, true);



}

/// <summary>
/// ロード処理
/// </summary>
/// <param name="name">名前</param>
/// <param name="path">パス</param>
/// <param name="volume">音量</param>
/// <param name="isLoop">ループ再生</param>
void SoundManager::LoadSound(const std::string& name, const std::string& path, int volume, bool isLoop)
{
    // 早期リターン
    if (soundHandles.find(name) != soundHandles.end()) return;

    SoundData data;
    data.handle = LoadSoundMem(path.c_str());
    data.volume = volume;
    data.isLoop = isLoop;

    // Dxlib用の音量に変換
    int dxVolume = volume * 255 / 100;
    ChangeVolumeSoundMem(dxVolume, data.handle);

    soundHandles[name] = data;

}

void SoundManager::Play_Sound(const std::string& name)
{
    // 音を再生する。
    auto it = soundHandles.find(name);
    if (it == soundHandles.end()) return;

    SoundData& data = it->second;

    int playType = data.isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK;

    if (name != "SE_Dodge" && name != "カーソル移動" && name != "SE_Enemy_Move" && name != "SE_Enemy_Warning")
    {
        if (!CheckSoundMem(data.handle)) PlaySoundMem(data.handle, playType);
    }
    else
    {
        PlaySoundMem(data.handle, playType);
    }
}

void SoundManager::StopSound(const std::string& name)
{
    // 音を停止する。
    auto it = soundHandles.find(name);
    if (it == soundHandles.end()) return;

    SoundData& data = it->second;

    StopSoundMem(data.handle);
}