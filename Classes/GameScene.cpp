#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static constexpr auto PATH_TO_BUTTON_SPIN = "button_spin.png";
static constexpr auto PATH_TO_DISPLAY     = "display_machine.png";
static constexpr auto PATH_TO_BACKGROUND  = "background.png";

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
        return false;

    return true;
}
