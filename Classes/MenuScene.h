#pragma once

#include "cocos2d.h"
#include "GameScene3.h"


class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(MenuScene);

    cocos2d::Menu *menu;

    void Play(Ref* pSender);
    void Exit(Ref* pSender);


};


