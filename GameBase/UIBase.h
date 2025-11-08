#pragma once
#include "DxLib.h"
#include <iostream>

class UIBase
{
public:
	virtual ~UIBase(){}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	const bool GetIsActive()const { return m_isActive; }

protected:
	bool m_isActive = false;
	VECTOR m_pos;				// À•W
	int m_handle = -1;			// ‰æ‘œƒnƒ“ƒhƒ‹
};