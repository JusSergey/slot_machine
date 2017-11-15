#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Paths.h"
#include "Helper.h"

USING_NS_CC;

static const Vec2 POSITION_DISPLAY(0.5f, 0.56f);
static const Vec2 POSITION_BACKGROUND(0.5f, 0.5f);
static const Vec2 POSITION_BUTTON_SPIN(0.5f, 0.15f);

enum ZOrder : int { MACHINE_DISPLAY, BACKGROUND, BUTTON_SPIN };


Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::init())
        return false;

    initBackground();
    initMachineDisplay();
    initButtonSpin();

    return true;
}

void GameScene::initMachineDisplay()
{
    _machineDisplay = MachineDisplay::create();
    _machineDisplay->setPosition(getPoint(POSITION_DISPLAY));

    addChild(_machineDisplay, ZOrder::MACHINE_DISPLAY);
}

void GameScene::initBackground()
{
    _backgroundSprite = Sprite::create(PATH_TO_BACKGROUND);
    _backgroundSprite->setPosition(getPoint(POSITION_BACKGROUND));

    addChild(_backgroundSprite, ZOrder::BACKGROUND);
}

void GameScene::initButtonSpin()
{
    _buttonSpin = ButtonSpin::create();
    _buttonSpin->setPosition(getPoint(POSITION_BUTTON_SPIN));

    _buttonSpin->addClickEventListener(getCallbackClickButtonSpin());

    addChild(_buttonSpin, ZOrder::BUTTON_SPIN);
}

std::function<void (Ref *)> GameScene::getCallbackClickButtonSpin()
{
    return [this] (Ref *) -> void {
        cocos2d::log("click event...");
        if (_machineDisplay)
            _machineDisplay->spinIcons();
    };
}
