#pragma once
#include "DxLib.h"
#include <iostream>

class Player;
class UIBase
{
public:
	virtual ~UIBase(){}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	const bool GetIsActive()const { return m_isActive; }

	void SetPlayer(const std::weak_ptr<Player>& player) { m_pPlayer = player; }

protected:
	bool m_isActive = false;
	VECTOR m_pos;				// À•W
	int m_handle = -1;			// ‰æ‘œƒnƒ“ƒhƒ‹

	std::weak_ptr<Player> m_pPlayer;
};