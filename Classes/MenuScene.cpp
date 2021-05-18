
#include "MenuScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();

}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Μενώ
    auto menu_item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(MenuScene::Play, this));
    auto menu_item_2 = MenuItemFont::create("Exit", CC_CALLBACK_1(MenuScene::Exit, this));
    
    menu = Menu::create(menu_item_1, menu_item_2, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);

    return true;
}

void MenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void MenuScene::Play(Ref* pSender)
{
    auto scene = GameScene3::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}

void MenuScene::Exit(Ref* pSender)
{
    Director::getInstance()->end();
}
