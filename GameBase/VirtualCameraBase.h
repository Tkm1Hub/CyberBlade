#pragma once
#include "GameObject.h"

class VirtualCameraBase : public IGameObject
{
public:
	VirtualCameraBase(const std::string& name): IGameObject(name){}


	const VECTOR& GetTarget() const { return target; }
	const bool GetIsActive() const { return isActive; }
	void SetIsActive(bool flag) { isActive = flag; }

protected:

	VECTOR target = VGet(0.0f, 0.0f, 0.0f);		// ’‹“_
	bool isActive = false;						// —LŒøó‘Ô‚©
};