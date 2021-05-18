#pragma once


#include "cocos2d.h"
#include "HeroLayer3.h"


using namespace cocos2d;

class BulletLayer3 : public cocos2d::Layer 
{
public:
	CREATE_FUNC(BulletLayer3);

protected:
	virtual bool init() override;

	void shootToCursor(cocos2d::Event* event);
	void unscheduleAll(Ref*);
	void removeFireSprite();
	
};