#pragma once

#include "cocos2d.h"
#include "HeroLayer3.h"
#include "SplashLayer.h"
#include "BulletLayer3.h"
#include "MenuScene.h"

using namespace cocos2d;

class GameScene3 : public cocos2d::Scene 
{
public:
	CREATE_FUNC(GameScene3);

	static cocos2d::Scene* createScene();
	HeroLayer3* getHeroLayer();

private:
	virtual bool init() override;

	HeroLayer3* hero_layer;

	
};