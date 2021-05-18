#include "GameScene3.h"

using namespace cocos2d;

Scene* GameScene3::createScene()
{
	return GameScene3::create();
}

bool GameScene3::init() 
{
	if (!Scene::init()) 
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->hero_layer = HeroLayer3::create();
	this->addChild(hero_layer, 1);
	this->hero_layer->setPosition(origin.x, origin.y);

	return true;
}

HeroLayer3* GameScene3::getHeroLayer()
{
	return this->hero_layer;
}


