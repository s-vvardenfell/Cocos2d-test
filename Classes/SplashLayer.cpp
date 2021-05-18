#include "SplashLayer.h"



bool SplashLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	////Спрайт радиации
	//radiationSprite = Sprite::create("hero_2.png", Rect(1, 59, 60, 60));

	//this->addChild(radiationSprite);

	//auto random = CCRANDOM_0_1();

	//if (random < 0.35)
	//{
	//	random = 0.35;
	//}
	//else if (random > 0.65)
	//{
	//	random = 0.65;
	//}

	//auto radiationPositionX = (random * visibleSize.height) + (radiationSprite->getContentSize().height / 2);
	//auto radiationPositionY = (random * visibleSize.width) + (radiationSprite->getContentSize().width / 2);
	//radiationSprite->setPosition(Point(radiationPositionX, radiationPositionY));

	////radiationSprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	//auto increaseScale = ScaleTo::create(3.0f, 5.0f);
	//auto decreaseScale = ScaleTo::create(3.0f, -5.0f);
	//auto seq = Sequence::create(increaseScale, decreaseScale, nullptr);
	//radiationSprite->runAction(RepeatForever::create(seq));


	return true;
}

