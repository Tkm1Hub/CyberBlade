#pragma once
#include "GameObject.h"

class VirtualCameraBase : public IGameObject
{
public:
	VirtualCameraBase(const std::string& name): IGameObject(name){}


	const VECTOR& GetTarget() const { return target; }

protected:

	VECTOR target = VGet(0.0f, 0.0f, 0.0f);		// íçéãì_

};