#pragma once

#include <vector>
#include "cocos2d.h"
#include "SplashLayer.h"
#include "BulletLayer3.h"



using namespace cocos2d;

class HeroLayer3 : public cocos2d::Layer 
{
public:
	friend class BulletLayer3;

	CREATE_FUNC(HeroLayer3);

	static Sprite* getHeroInstance();

	BulletLayer3* getBulletLayer();
	BulletLayer3* bullet_layer;

private:
	virtual bool init() override;
	virtual void update(float delta) override;

	void moveHeroByKeyboard(int i);
	void moveHeroByMouse(cocos2d::Event* event);
	void shootFire();
	void heroExploded();
	void gameOver();

	std::vector<int> keyboard_status = { 0, 0, 0, 0 };

	Action* move_action;
	Sprite* splashSprite;
	Sprite* fireSprite;

	cocos2d::Vector<cocos2d::SpriteFrame*> animFramesExplosion;
	cocos2d::Vector<cocos2d::SpriteFrame*> animFramesFire;
	


	
};