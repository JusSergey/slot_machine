#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Paths.h"
#include "Helper.h"

USING_NS_CC;

static const Vec2 POSITION_DISPLAY(0.5f, 0.56f);
static const Vec2 POSITION_BACKGROUND(0.5f, 0.5f);
static const Vec2 POSITION_BUTTON_SPIN(0.5f, 0.15f);

static const GLubyte AUTOSPIN_OFF(0xff * 1.f);
static const GLubyte AUTOSPIN_ON(0xff * 0.7f);

enum ZOrder : int { MACHINE_DISPLAY, BACKGROUND, BUTTON_SPIN, CHOOSE_AUTOSPIN = BUTTON_SPIN };


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
    initChooseAutospin();

    _machineDisplay->setCallbackDidSpinFinish(getCallbackDidSpinFinish());

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

void GameScene::initChooseAutospin()
{
    auto label = Label::createWithTTF("autospin", "fonts/arial.ttf", 36);

    auto item = MenuItemLabel::create(label);
    auto menu = Menu::createWithItem(item);

    menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    menu->setPosition(getPoint(0.80, POSITION_BUTTON_SPIN.y));

    addChild(menu, CHOOSE_AUTOSPIN);

    label->setOpacity(AUTOSPIN_ON);
    _turnOnAutospin = (label->getOpacity() == AUTOSPIN_ON);

    item->setCallback([=](Ref *ptr) {

        auto label = (static_cast<Label *>(ptr));
        _turnOnAutospin = label->getOpacity() == AUTOSPIN_ON;
        label->setOpacity(_turnOnAutospin ? AUTOSPIN_OFF : AUTOSPIN_ON);

        if (_turnOnAutospin)
            _machineDisplay->spinIcons();
    });
}

std::function<void (Ref *)> GameScene::getCallbackClickButtonSpin()
{
    return [this] (Ref *) -> void {
        cocos2d::log("click event...");
        if (_machineDisplay)
            _machineDisplay->spinIcons();
    };
}

std::function<void ()> GameScene::getCallbackDidSpinFinish()
{
    return [this] {
        if (_turnOnAutospin) {
            scheduleOnce([this](float){
                _machineDisplay->spinIcons();
            }, 1, "autostart");
        }
    };
}
