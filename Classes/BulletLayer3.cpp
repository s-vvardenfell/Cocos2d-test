#include "BulletLayer3.h"

using namespace cocos2d;


bool BulletLayer3::init() 
{
	if (!Layer::init()) 
	{
		return false;
	}

	auto mouse_listener = EventListenerMouse::create();
	mouse_listener->onMouseDown = CC_CALLBACK_1(BulletLayer3::shootToCursor, this);
	_eventDispatcher->addEventListenerWithFixedPriority(mouse_listener, 1);

	return true;
}


void BulletLayer3::shootToCursor(cocos2d::Event* event)
{
	EventMouse* mouseEvent = (EventMouse*)event;

	float bullet_speed = 600.0f;

	if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		//Получаем позицию спрайта персонажа
		auto hero_position = HeroLayer3::getHeroInstance()->getPosition();

		//Стрельба
		Sprite* bullet_sprite = Sprite::create("hero_2.png", Rect(170, 77, 18, 10));
		this->addChild(bullet_sprite);
		bullet_sprite->setPosition(hero_position.x-60, hero_position.y-8);

		auto length = sqrtf(pow((mouseEvent->getCursorX() - hero_position.x), 2) + pow((mouseEvent->getCursorY() - hero_position.y), 2));
		auto bullet_flight_duration = length / bullet_speed;

		auto target = Point(mouseEvent->getCursorX(), mouseEvent->getCursorY());
		MoveBy* p_move = MoveTo::create(bullet_flight_duration, target);
		CallFunc* p_callfunc = CallFunc::create([this, bullet_sprite]() {this->removeChild(bullet_sprite, true);});
		Sequence* p_sequence = Sequence::create(p_move, p_callfunc, nullptr);
		bullet_sprite->runAction(p_sequence);
	}
}


void BulletLayer3::unscheduleAll(Ref* shit) 
{
	this->unscheduleAllCallbacks();
}
