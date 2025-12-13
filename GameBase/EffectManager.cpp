#include "stdafx.h"
#include "EffectManager.h"

void EffectManager::Init()
{
    LoadEffect("Boss_Roar", "data/effect/Roar.efkefc", 30.0f);
    LoadEffect("Attack_Warning", "data/effect/AttackWarning.efkefc", 5.0f);
    LoadEffect("Boss_ShockWave", "data/effect/ShockWave_Enemy.efkefc", 50.0f);
    LoadEffect("Boss_JumpWave", "data/effect/JumpWave_Enemy.efkefc", 20.0f);
    LoadEffect("Player_JumpWave", "data/effect/ShockWave_Player.efkefc", 10.0f);
    LoadEffect("DodgeJust", "data/effect/DodgeJust.efkefc", 10.0f);
    LoadEffect("Test", "data/effect/Test.efkefc", 8.0f);
}

/// <summary>
/// 初期化
/// </summary>
void EffectManager::LoadEffect(const std::string& name, const std::string& path, float magnification)
{
    if (effectHandles.find(name) == effectHandles.end()) {
        int handle = LoadEffekseerEffect(path.c_str(), magnification);
        effectHandles[name] = handle;
    }
}

void EffectManager::PositionUpdate(const VECTOR& objectPosition)
{
    position = VGet(objectPosition.x, objectPosition.y, objectPosition.z);


    // 再生中のエフェクトを移動する。
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, position.x, position.y, position.z);

}

/// <summary>
/// 更新
/// </summary>
void EffectManager::Update()
{
    // Effekseerにより再生中のエフェクトを更新する。
    UpdateEffekseer3D();
}

/// <summary>
/// 描画
/// </summary>
void EffectManager::Draw()
{
    // Effekseerにより再生中のエフェクトを描画する。
    //DrawEffekseer3D_Draw(playingEffectHandle);
    DrawEffekseer3D();

}

/// <summary>
/// ポジションを保存
/// </summary>
/// <param name="setPosition"></param>
void EffectManager::SetPosition(const std::string& name, const VECTOR setPosition)
{
    // エフェクトの位置を更新
    for (auto& e : activeEffects) {
        if (e.name == name && e.isActive) {
            SetPosPlayingEffekseer3DEffect(e.handle,
                setPosition.x,
                setPosition.y,
                setPosition.z);
            e.position = setPosition;
        }
    }
}

/// <summary>
/// 拡大率
/// </summary>
/// <param name="scale"></param>
void EffectManager::SetScale(VECTOR scale)
{
    SetScalePlayingEffekseer3DEffect(playingEffectHandle, scale.x, scale.y, scale.z);
}

/// <summary>
///  エフェクトを再生
/// </summary>
void EffectManager::PlayEffect(const std::string& name, const VECTOR& position)
{
    // エフェクトを再生する。
    auto it = effectHandles.find(name);
    if (it == effectHandles.end()) return;

    int handle = PlayEffekseer3DEffect(it->second);
    SetPosPlayingEffekseer3DEffect(handle, position.x, position.y, position.z);

    activeEffects.push_back(EffectInstance{ name,handle, position, true });
}

/// <summary>
/// 再生中のモーションを停止する
/// </summary>
void EffectManager::StopEffect()
{
    StopEffekseer3DEffect(playingEffectHandle);
}

void EffectManager::SetSpeed(float speed)
{
    SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, speed);
}

/// <summary>
/// 角度
/// </summary>
/// <param name="setPosition"></param>
void EffectManager::SetRotation(VECTOR setPosition)
{
    SetRotationPlayingEffekseer3DEffect(playingEffectHandle, setPosition.x, setPosition.y, setPosition.z);
}