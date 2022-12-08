#pragma once
#include <memory>


class BaseScene
{
private:
	
public:
	BaseScene() {}
	virtual ~BaseScene() {}
	
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
};

