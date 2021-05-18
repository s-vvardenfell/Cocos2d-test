#pragma once


#include <vector>
#include "cocos2d.h"


using namespace cocos2d;

class SplashLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(SplashLayer);

private:
	virtual bool init() override;
	virtual void update(float delta) override;
	void spawnRadiation();

	Sprite* radiationSprite;
};