#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <functional>
#include "cocos2d.h"
#include "MachineDisplay.h"
#include "ButtonSpin.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene)

private:
    MachineDisplay *_machineDisplay = nullptr;
    cocos2d::Sprite *_backgroundSprite = nullptr;
    ButtonSpin *_buttonSpin = nullptr;

private:
    void initMachineDisplay();
    void initBackground();
    void initButtonSpin();

private:
    std::function<void(cocos2d::Ref*)> getCallbackClickButtonSpin();

};

#endif // __GAME_SCENE_H__
