#pragma once
#include "UIBase.h"

class IGameObject;
class Marker :public UIBase
{
public:
    void Init() override;
    void Update() override;
    void Draw() override;

private:

    static constexpr float MARKER_VISIBLE_DISTANCE = 300.0f;

};
