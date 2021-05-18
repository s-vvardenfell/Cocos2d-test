#include "HeroLayer3.h"

//static ����� �������� ���������� ������� � BulletLayer
static Sprite* heroSprite = nullptr;

Sprite* HeroLayer3::getHeroInstance()
{
	if (!heroSprite)
	{
		heroSprite = Sprite::create("hero_2.png", Rect(1, 29, 35, 30));
		CCASSERT(heroSprite, "FATAL: Not enough memory");
	}
	return heroSprite;
}

BulletLayer3* HeroLayer3::getBulletLayer()
{
	return this->bullet_layer;
}


bool HeroLayer3::init() 
{
	if (!Layer::init()) 
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//�������������� ������ ���������
	if(!heroSprite)
		heroSprite = Sprite::create("hero_2.png", Rect(1, 29, 35, 30));
	this->addChild(heroSprite);
	heroSprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2);

	//�������������� ������ ���� ��� ��������
	if (!fireSprite)
		fireSprite = Sprite::create("hero_2.png", Rect(170, 77, 10, 10));
	fireSprite->setPosition(heroSprite->getPositionX() - 18, heroSprite->getPositionY() - 7);
	this->addChild(fireSprite);
	

	//��������� ������� ����
	auto mouse_listener = EventListenerMouse::create();
	mouse_listener->onMouseDown = CC_CALLBACK_1(HeroLayer3::moveHeroByMouse, this);
	_eventDispatcher->addEventListenerWithFixedPriority(mouse_listener, 1);

	//��������� ���� � ������
	this->bullet_layer = BulletLayer3::create();
	this->addChild(bullet_layer, 1);
	this->bullet_layer->setPosition(origin.x, origin.y);


	//��������� ������� ����������
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&listener,this](EventKeyboard::KeyCode key_code, Event*) 
	{
		switch (key_code) 
		{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			gameOver();
			break;		
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			keyboard_status[2] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			keyboard_status[3] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			keyboard_status[0] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			keyboard_status[1] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			keyboard_status[0] = 0;
			keyboard_status[1] = 0;
			keyboard_status[2] = 0;
			keyboard_status[3] = 0;
			heroSprite->stopAction(move_action);
			break;
		default:
			break;
		}
	};

	listener->onKeyReleased = [this](EventKeyboard::KeyCode key_code, Event*) 
	{
		switch (key_code) 
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			keyboard_status[2] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			keyboard_status[3] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			keyboard_status[0] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			keyboard_status[1] = 0;
			break;
		default:
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();
	return true;
}

void HeroLayer3::update(float delta) 
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (heroSprite->getPositionX() > visibleSize.width + origin.x)
	{
		heroSprite->setPositionX(visibleSize.width + origin.x);
	}
	else if (heroSprite->getPositionX() < origin.x)
	{
		heroSprite->setPositionX(origin.x);
	}

	if (heroSprite->getPositionY() > visibleSize.height + origin.y)
	{
		heroSprite->setPositionY(visibleSize.height + origin.y);
	}
	else if (heroSprite->getPositionY() < origin.y) 
	{
		heroSprite->setPositionY(origin.y);
	}

	for (int i = 0; i < keyboard_status.size(); i++) 
	{
		if (keyboard_status[i] == 1) {
			moveHeroByKeyboard(i);
			//break;
		}
	}

	//���������� ������ ���� �� �������� ������ � ����������
	fireSprite->setPosition(heroSprite->getPositionX() - 18, heroSprite->getPositionY() - 7);
}

void HeroLayer3::moveHeroByKeyboard(int i) 
{

	float offsetx = 0;
	float offsety = 0;
	switch (i) 
	{
	case 0:
		offsety = 3;
		break;
	case 1:
		offsety = -3;
		break;
	case 2:
		offsetx = -3;
		break;
	case 3:
		offsetx = 3;
		break;
	default:
		break;
	}

	auto* p_move = MoveTo::create(0.02f, Point(heroSprite->getPositionX() + offsetx, heroSprite->getPositionY() + offsety));
	heroSprite->runAction(p_move);
}

//������������ ������� ������� ������ ����
void HeroLayer3::moveHeroByMouse(cocos2d::Event* event)
{
	EventMouse* mouseEvent = (EventMouse*)event;
	
	//����
	if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
	{
		float speed = 60.0f;

		//���� �������� ����� �������, ������ ���������� (�� ���������� ����������)
		if ((mouseEvent->getPreviousLocation().x != mouseEvent->getLocation().x) || (mouseEvent->getPreviousLocation().y != mouseEvent->getLocation().y));
		heroSprite->stopAction(move_action);

		//������� ����������������� ������ ������� �� ����������� � ��������
		auto length = sqrtf(pow((mouseEvent->getCursorX() - heroSprite->getPositionX()), 2) + pow((mouseEvent->getCursorY() - heroSprite->getPositionY()), 2));
		auto duration = length / speed;

		move_action = cocos2d::MoveTo::create(duration, Point(mouseEvent->getCursorX(), mouseEvent->getCursorY()));

		heroSprite->runAction(move_action);
	}//�������� (���� �� BulletLayer)
	if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)
	{
		shootFire();
	}
	
}

//��������� ����� � �������������
void HeroLayer3::gameOver()
{
	heroExploded();
	heroSprite->stopAction(move_action);
}

//�������� ������
void HeroLayer3::heroExploded()
{
	heroSprite->setOpacity(1);
	fireSprite->setOpacity(1);

	splashSprite = Sprite::create("hero_2.png");
	this->addChild(splashSprite);
	splashSprite->setPosition(heroSprite->getPositionX(), heroSprite->getPositionY()-10);

	animFramesExplosion.reserve(6);
	animFramesExplosion.pushBack(SpriteFrame::create("hero_2.png", Rect(61, 87, 35, 50)));
	animFramesExplosion.pushBack(SpriteFrame::create("hero_2.png", Rect(96, 87, 27, 50)));
	animFramesExplosion.pushBack(SpriteFrame::create("hero_2.png", Rect(123, 87, 27, 47)));
	animFramesExplosion.pushBack(SpriteFrame::create("hero_2.png", Rect(150, 90, 27, 47)));
	animFramesExplosion.pushBack(SpriteFrame::create("hero_2.png", Rect(177, 93, 27, 47)));
	animFramesExplosion.pushBack(SpriteFrame::create("hero_2.png", Rect(35, 40, 25, 18)));

	Animation* animation = Animation::createWithSpriteFrames(animFramesExplosion, 0.2f);
	Animate* animate = Animate::create(animation);

	splashSprite->runAction(animate);
}

//�������� ���� �� ��������
void HeroLayer3::shootFire()
{
	animFramesFire.reserve(3);
	animFramesFire.pushBack(SpriteFrame::create("hero_2.png", Rect(147, 75, 27, 12)));
	animFramesFire.pushBack(SpriteFrame::create("hero_2.png", Rect(170, 77, 18, 10)));
	animFramesFire.pushBack(SpriteFrame::create("hero_2.png", Rect(170, 77, 10, 10)));
	Animation* animation = Animation::createWithSpriteFrames(animFramesFire, 0.1f);
	Animate* animate = Animate::create(animation);
	fireSprite->runAction(animate);
}
